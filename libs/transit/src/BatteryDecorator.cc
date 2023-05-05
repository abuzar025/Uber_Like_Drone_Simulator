#include "BatteryDecorator.h"
#include "Drone.h"
#include "BeelineStrategy.h"
#include "RechargeStation.h"

BatteryDecorator::~BatteryDecorator() {
    if (toRechargeStation != nullptr) delete toRechargeStation;
}

void BatteryDecorator::OverridedUpdate(double dt, std::vector<IEntity*> scheduler) {
    double amount = dt * drainRate;
    bool withinChargingStation = false;
    for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
        RechargeStation* rechargeStation = dynamic_cast<RechargeStation*>(*iter);
        if (rechargeStation != nullptr && rechargeStation->BatteryInRange(this)) {
            withinChargingStation = true;
            break;
        }
    }
    if (!withinChargingStation) {
        if (amount > charge) {
            amount = charge;
            charge = 0;
        } else {
            charge -= amount;
        }
    }
    if (IsOrWillBeMarooned()) {
        completelyDrained = true;
        return;
    }
    if (recharging) {
        if (!(targetRechargeStation->BatteryInRange(this))) {
            if (toRechargeStation == nullptr) {
                if (targetRechargeStation != nullptr) {
                    SetDestination(targetRechargeStation->GetPosition());
                    toRechargeStation = new BeelineStrategy(GetPosition(), targetRechargeStation->GetPosition());
                } else {
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
            if (GetAvailability()) {
                drone->GetNearestEntity(scheduler);
                if (drone->GetCurrentNearestEntity() != nullptr) {
                    Vector3 finalDestination = drone->GetCurrentNearestEntity()->GetDestination();
                    double closestRechargeStationDistance = INFINITY;
                    RechargeStation* closestRechargeStation = nullptr;
                    for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                        RechargeStation* station = dynamic_cast<RechargeStation*>(*iter);
                        if (station != nullptr) {
                            double distance = station->GetPosition().Distance(finalDestination);
                            if (distance < closestRechargeStationDistance) {
                                closestRechargeStationDistance = distance;
                                closestRechargeStation = station;
                            }
                        }
                    }
                    double additionalDistance = 0;
                    if (closestRechargeStation != nullptr && closestRechargeStationDistance >= closestRechargeStation->GetRadius()) {
                        additionalDistance = closestRechargeStationDistance - closestRechargeStation->GetRadius();
                    }
                    double chargeRequired = drone->GetToRobotStrategy()->GetDistance(GetPosition()) + drone->GetToFinalDestinationStrategy()->GetDistance(GetDestination()) + additionalDistance;
                    chargeRequired *= drainRate / GetSpeed();
                    if (chargeRequired > charge) {
                        double testDistance = (charge * GetSpeed() / drainRate);
                        closestRechargeStationDistance = INFINITY;
                        closestRechargeStation = nullptr;
                        for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                            RechargeStation* station = dynamic_cast<RechargeStation*>(*iter);
                            if (station != nullptr) {
                                double distance = station->GetPosition().Distance(GetDestination());
                                double distanceFromBattery = station->GetPosition().Distance(GetPosition());
                                if (distance < closestRechargeStationDistance && distanceFromBattery < testDistance + station->GetRadius()) {
                                    closestRechargeStationDistance = distance;
                                    closestRechargeStation = station;
                                }
                            }
                        }
                        if (closestRechargeStation != nullptr) {
                            targetRechargeStation = closestRechargeStation;
                            recharging = true;
                        }
                        drone->CancelDelivery();
                    }
                } else {
                    double closestRechargeStationDistance = INFINITY;
                    RechargeStation* closestRechargeStation = nullptr;
                    for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                        RechargeStation* station = dynamic_cast<RechargeStation*>(*iter);
                        if (station != nullptr) {
                            double distance = (station)->GetPosition().Distance(GetPosition());
                            if (distance < closestRechargeStationDistance) {
                                closestRechargeStationDistance = distance;
                                closestRechargeStation = station;
                            }
                        }
                    }
                    if (closestRechargeStation != nullptr && (closestRechargeStationDistance - closestRechargeStation->GetRadius()) * drainRate / GetSpeed() > charge - 3) {
                        targetRechargeStation = closestRechargeStation;
                        recharging = true;
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
        completelyDrained = false;
        return true;
    }
    return false;
}

bool BatteryDecorator::IsOrWillBeMarooned() {
    if (toRechargeStation != nullptr && targetRechargeStation != nullptr) {
        return (toRechargeStation->GetDistance(GetPosition()) - targetRechargeStation->GetRadius()) * drainRate / GetSpeed() > charge;
    }
    return charge <= 0 || completelyDrained;
}
