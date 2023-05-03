#include "BatteryDecorator.h"
#include "Drone.h"
#include "BeelineStrategy.h"
#include "RechargeStation.h"

// PLEASE REMOVE LATER
#include <iostream>

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
        std::cout << "I am looking to recharge" << std::endl;
        if (!withinChargingStation) {
            std::cout << "not within recharge station" << std::endl;
            if (toRechargeStation == nullptr) {
                std::cout << "Seeking Recharge Station" << std::endl;
                if (targetRechargeStation != nullptr) {
                    SetDestination(targetRechargeStation->GetPosition());
                    toRechargeStation = new BeelineStrategy(GetPosition(), targetRechargeStation->GetPosition());
                } else {
                    std::cout << "Did not find Recharge Station" << std::endl;
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
                    IEntity* closestRechargeStation = nullptr;
                    for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                        if (dynamic_cast<RechargeStation*>(*iter) != nullptr) {
                            double distance = (*iter)->GetPosition().Distance(finalDestination);
                            if (distance < closestRechargeStationDistance) {
                                closestRechargeStationDistance = distance;
                                closestRechargeStation = *iter;
                            }
                        }
                    }
                    double additionalDistance = 0;
                    if (closestRechargeStation != nullptr && closestRechargeStationDistance >= 5) {
                        additionalDistance = closestRechargeStationDistance - 5;
                    }
                    double chargeRequired = drone->GetToRobotStrategy()->GetDistance(GetPosition()) + drone->GetToFinalDestinationStrategy()->GetDistance(GetDestination()) + additionalDistance;
                    chargeRequired *= drainRate / GetSpeed();
                    std::cout << "additionalDistance: " << additionalDistance << std::endl;
                    if (chargeRequired > charge) {
                        double testDistance = (charge * GetSpeed() / drainRate) + 5;
                        closestRechargeStationDistance = INFINITY;
                        closestRechargeStation = nullptr;
                        for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                            if (dynamic_cast<RechargeStation*>(*iter) != nullptr) {
                                double distance = (*iter)->GetPosition().Distance(GetDestination());
                                double distanceFromBattery = (*iter)->GetPosition().Distance(GetPosition());
                                if (distance < closestRechargeStationDistance && distanceFromBattery < testDistance) {
                                    closestRechargeStationDistance = distance;
                                    closestRechargeStation = *iter;
                                }
                            }
                        }
                        if (closestRechargeStation != nullptr) {
                            targetRechargeStation = closestRechargeStation;
                            recharging = true;
                        }
                        drone->CancelDelivery();
                        drone->GetCurrentNearestEntity()->SetAvailability(true);
                        std::cout << "I am looking to recharge, " << chargeRequired << ", " << charge << std::endl;
                    }
                } else {
                    double closestRechargeStationDistance = INFINITY;
                    IEntity* closestRechargeStation = nullptr;
                    for (auto iter = entityList->begin(); iter != entityList->end(); iter++) {
                        if (dynamic_cast<RechargeStation*>(*iter) != nullptr) {
                            double distance = (*iter)->GetPosition().Distance(GetPosition());
                            if (distance < closestRechargeStationDistance) {
                                closestRechargeStationDistance = distance;
                                closestRechargeStation = *iter;
                            }
                        }
                    }
                    if ((closestRechargeStationDistance - 5) * drainRate / GetSpeed() > charge - 3) {
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
    std::cout << charge << std::endl;
    if (charge >= maxCharge) {
        charge = maxCharge;
        return true;
    }
    return false;
}

bool BatteryDecorator::IsOrWillBeMarooned() {
    if (toRechargeStation != nullptr) {
        std::cout << "Target Position: " << targetRechargeStation->GetPosition().x << ", " << targetRechargeStation->GetPosition().y << ", " << targetRechargeStation->GetPosition().z << std::endl;
        std::cout << "Charge Required: " << (toRechargeStation->GetDistance(GetPosition()) - 5) * drainRate / GetSpeed();
        return (toRechargeStation->GetDistance(GetPosition()) - 5) * drainRate / GetSpeed() > charge;
    }
    return charge <= 0;
}
