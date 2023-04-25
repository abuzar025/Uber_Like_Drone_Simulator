#define _USE_MATH_DEFINES
#include "RechargeStation.h"

#include <cmath>

RechargeStation::RechargeStation(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  rechargeRate = obj["rechargeRate"]; 

  speed = 0;

  available = true; 
}

RechargeStation::~RechargeStation() {

}

void RechargeStation::Update(double dt, std::vector<IEntity*> scheduler) {
    for(int i = 0; i < scheduler.size(); i++) {
        if(dynamic_cast<BatteryDecorator*>(scheduler.at(i)) != nullptr) { //Checks that the object is a Battery
          if(CheckInRange(scheduler.at(i))) {

          }
        }
    }
}

bool RechargeStation::CheckInRange(BatteryDecorator* batt) {
  
}