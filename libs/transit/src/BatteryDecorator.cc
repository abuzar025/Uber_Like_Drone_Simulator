#include "BatteryDecorator.h"
#include "Drone.h"
#include "BeelineStrategy.h"
#include "RechargeStation.h"

// This breaks SOLID.
// No matter what, O will have to be broken because we will have to modify SimulationModel
// to add our new behavior
// But even if we ignore that, SetGraph had to be changed to virtual
// D of solid will have to be broken
// In order to know how much charge it takes to perform a trip,
// we need to know the strategey.
// While we could do some super jank, inefficient, and unnecessarily complicated
// method to calculate how much distance the trip covers, why couldn't we just...
// do things with the strategy variable in Drone, specifically Drone
// It is not a guarentee for an entity to have a strategy.
// We HAVE to break O even more than we already have, or break D to
// determine how much charge it takes to perform a trip?

// Why do we have to use a Decorator when just simply inheriting off of Drone
// Would be much simpler, readable, stable, efficient... Pretty much everything
// "But what if we wanted other entites to have batteries?"
// Why not just tailor each battery for the entity. They have their own individual
// challenges with implementing batteries. But what this Decorator is doing
// is that it is trying to be a "1 size fits all." What should happen when a
// RechargeStation runs out of battery? Start moving towards the nearest recharge?
// That's silly. Each type of entity needs their own logic to handle the battery;
// a one size fits all doesn't work here.

// I cannot find a worse use of Decorator. Whenever I try to think ahead for 10
// seconds, I find a problem that would not have happened if Decorator was not used.
// This is TERRIBLE.
void BatteryDecorator::OverridedUpdate(double dt, std::vector<IEntity*> scheduler) {
    double amount = dt * drainRate;
    bool withinChargingStation = false;
    for (auto iter = scheduler.begin(); iter != scheduler.end(); iter++) {
        RechargeStation* rechargeStation = dynamic_cast<RechargeStation*>(*iter);
        if (rechargeStation != nullptr && rechargeStation->BatteryInRange(this)) {
            withinChargingStation = true;
            break;
        }
    }
    if (!withinChargingStation) {
        if (charge <= 0 || IsOrWillBeMarooned()) {
            return; //Stop moving drone, repair drones will be sent out
        } else if (amount > charge) {
            amount = charge;
            charge = 0;
        } else {
            charge -= amount;
        }
    }

    if (recharging) {
        if (!withinChargingStation) {
            if (toRechargeStation == nullptr) {
                IEntity* closestRechargeStation = nullptr;
                double closestRechargeStationDistance = INFINITY;
                for (auto iter = scheduler.begin(); iter != scheduler.end(); iter++) {
                    if (dynamic_cast<RechargeStation*>(*iter) != nullptr) {
                        double distance = (*iter)->GetPosition().Distance(GetPosition());
                        if (distance < closestRechargeStationDistance) {
                            closestRechargeStationDistance = distance;
                            closestRechargeStation = *iter;
                        }
                    }
                }
                if (closestRechargeStation != nullptr) {
                    SetDestination(closestRechargeStation->GetPosition());
                    // Why didn't we make an IStrategyFactory from the start?
                    toRechargeStation = new BeelineStrategy(GetPosition(), GetDestination());
                }
            }
            if (toRechargeStation != nullptr) {
                toRechargeStation->Move(this, amount / drainRate);
            }
        } else {
            if (getCharge() >= maxCharge) {
                delete toRechargeStation;
                toRechargeStation = nullptr;
                recharging = false;
            }
        }
    } else {
        // I hate this. This would be so much better if we could just, inherit off of Drone
        // Decorator makes this so much more complicated for absolutely 0 payoff.

        // SOLID HAS to be broken in order to get this to work, or we would have to do
        // some incredibly terrible and poorly planned
        Drone* drone = dynamic_cast<Drone*>(entity);

        if (drone != nullptr) {
            if (drone->GetCurrentNearestEntity() == nullptr) {
                drone->GetNearestEntity(scheduler);
                if (drone->GetCurrentNearestEntity() == nullptr) {
                    double chargeRequired = drone->GetToRobotStrategy()->GetDistance(GetPosition()) + drone->GetToFinalDestinationStrategy()->GetDistance(GetDestination());
                    chargeRequired *= drainRate / GetSpeed();
                    if (chargeRequired > charge) {
                        recharging = true;
                        drone->GetCurrentNearestEntity()->SetAvailability(true);
                    }
                }
            } else {
                entity->Update(amount / drainRate, scheduler);
            }
        }
    }
    
}

bool BatteryDecorator::recharge(double amount) {
    charge += amount;
    if (charge >= maxCharge) {
        charge = maxCharge;
        return true;
    }
    return false;
}

bool BatteryDecorator::IsOrWillBeMarooned() {
    if (toRechargeStation != nullptr) {
        return toRechargeStation->GetDistance(GetPosition()) * drainRate / GetSpeed() > charge;
    }
    return charge <= 0;
}
