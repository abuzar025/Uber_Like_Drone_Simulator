#define _USE_MATH_DEFINES
#include "RepairDrone.h"
#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "RechargeStation.h"

#include <cmath>
#include <cstdlib>

RepairDrone::RepairDrone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  home = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  rechargeRate = obj["rechargeRate"]; 

  available = true;
}

RepairDrone::~RepairDrone() {
    delete toDrone;
    delete toRechargeStation;
}

void RepairDrone::Update(double dt, std::vector<IEntity*> scheduler) {
    // Look through the scheduler and try to find drones that are dead
    if(toRechargeStation) {
        toRechargeStation->Move(this, dt);
        if (toRechargeStation->IsCompleted()) {
            delete toRechargeStation;
            toRechargeStation = nullptr;
        }
    } else if(toDrone) {
        toDrone->Move(this, dt);
        if (toDrone->IsCompleted()) {
            if(batt->recharge(rechargeRate * dt)) {
                std::cout << "DONE" << std::endl;
                delete toDrone;
                toDrone = nullptr;
                toRechargeStation = new BeelineStrategy(position, home);
            }
        }
    } else {
        for(int i = 0; i < entityList->size(); i++) {
            if(dynamic_cast<BatteryDecorator*>(entityList->at(i)) != nullptr) { //Checks that the object is a Battery
                batt = dynamic_cast<BatteryDecorator*>(entityList->at(i));
                if(batt->IsOrWillBeMarooned()) {
                    destination = batt->GetPosition();
                    toDrone = new BeelineStrategy(position, destination);
                    toRechargeStation = nullptr;
                }
            }
        }
    }
} 