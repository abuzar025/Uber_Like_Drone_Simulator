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
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];


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
            delete toDrone;
            toDrone = nullptr;
            //TODO - Actually recharge the battery
            GetClosestRechargeStation(scheduler);
            toRechargeStation = new BeelineStrategy(position, station->GetPosition());
        }
    } else {
        for(int i = 0; i < scheduler.size(); i++) {
            if(dynamic_cast<BatteryDecorator*>(scheduler.at(i)) != nullptr) { //Checks that the object is a Battery
            BatteryDecorator* batt = dynamic_cast<BatteryDecorator*>(scheduler.at(i));
            if(BatteryInRange(batt) && batt->IsOrWillBeMarooned()) {
                destination = batt->GetPosition();
                toDrone = new BeelineStrategy(position, destination);
                toRechargeStation = nullptr;
            }
            }
        }
    }

} 

bool RepairDrone::BatteryInRange(IEntity* entity) {
    return true;
    //TODO - Based on % and beeline strategy find effective range
}

void RepairDrone::GetClosestRechargeStation(std::vector<IEntity*> scheduler) {
    float shortestDistance = 10000000.0;
    for(auto entity : scheduler) {
        if(dynamic_cast<RechargeStation*>(entity) != nullptr) {
            RechargeStation* st = dynamic_cast<RechargeStation*>(entity);
            if(DistanceFromDrone(st) < shortestDistance) {
                station = st;
                shortestDistance = DistanceFromDrone(st);
            }
        }
    }
}

float RepairDrone::DistanceFromDrone(IEntity* entity) {
  return sqrt(pow(abs(position[0] - entity->GetPosition()[0]), 2.0) + pow(abs(position[2] - entity->GetPosition()[2]), 2.0));
}