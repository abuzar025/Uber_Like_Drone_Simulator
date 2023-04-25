#define _USE_MATH_DEFINES
#include "RechargeStation.h"
#include "BatteryDecorator.h"

#include <cmath>
#include <cstdlib>

RechargeStation::RechargeStation(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  rechargeRate = obj["rechargeRate"]; 

  available = true; 
}

RechargeStation::~RechargeStation() {

}

void RechargeStation::Update(double dt, std::vector<IEntity*> scheduler) {
    for(int i = 0; i < scheduler.size(); i++) {
        if(dynamic_cast<BatteryDecorator*>(scheduler.at(i)) != nullptr) { //Checks that the object is a Battery
          RechargeIfInRange(scheduler.at(i));
        }
    }
}

void RechargeStation::RechargeIfInRange(IEntity* entity) {
  BatteryDecorator* batt = dynamic_cast<BatteryDecorator*>(entity);
  if(abs(position[0] - batt->GetPosition()[0]) <= 5.0 && abs(position[1] - batt->GetPosition()[1]) <= 5.0) {
    batt->recharge(rechargeRate);
  }
}