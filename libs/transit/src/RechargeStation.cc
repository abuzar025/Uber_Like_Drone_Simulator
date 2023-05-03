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
  std::cout << entityList->size() << std::endl;
    for(int i = 0; i < entityList->size(); i++) {
        if(dynamic_cast<BatteryDecorator*>(entityList->at(i)) != nullptr) { //Checks that the object is a Battery
          std::cout << "CAST" << std::endl;
          BatteryDecorator* batt = dynamic_cast<BatteryDecorator*>(entityList->at(i));
          if(BatteryInRange(batt)) {
            std::cout << "IN RANGE" << std::endl;
            batt->recharge(rechargeRate);
          }
        }
    }
}

bool RechargeStation::BatteryInRange(IEntity* entity) {
  std::cout << "XDIFF - " << abs(position[0] - entity->GetPosition()[0]) << ", ZDIFF - " << abs(position[2] - entity->GetPosition()[2]) << std::endl;
  return abs(position[0] - entity->GetPosition()[0]) <= 50.0 && abs(position[2] - entity->GetPosition()[2]) <= 50.0;
}