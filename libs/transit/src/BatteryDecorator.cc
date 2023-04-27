#include "BatteryDecorator.h"
#include "Drone.h"
#include "BeelineStrategy.h"
#include "RechargeStation.h"

// PLEASE REMOVE LATER
#include <iostream>

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
    std::cout << charge << std::endl;
    if (!withinChargingStation) {
        if (charge <= 0 || IsOrWillBeMarooned()) {
            std::cout << "I am ded" << std::endl;
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
        Drone* drone = dynamic_cast<Drone*>(entity);

        if (drone != nullptr) {
            if (drone->GetCurrentNearestEntity() == nullptr) {
                drone->GetNearestEntity(scheduler);
                if (drone->GetCurrentNearestEntity() != nullptr) {
                    double chargeRequired = drone->GetToRobotStrategy()->GetDistance(GetPosition()) + drone->GetToFinalDestinationStrategy()->GetDistance(GetDestination());
                    chargeRequired *= drainRate / GetSpeed();
                    if (chargeRequired > charge) {
                        recharging = true;
                        drone->GetCurrentNearestEntity()->SetAvailability(true);
                        std::cout << "I am looking to recharge, " << chargeRequired << ", " << charge << std::endl;
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
