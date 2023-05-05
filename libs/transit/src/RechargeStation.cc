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
  radius = obj["radius"];

  available = true;
}

RechargeStation::~RechargeStation() {}

void RechargeStation::Update(double dt, std::vector<IEntity*> scheduler) {
    for (int i = 0; i < entityList->size(); i++) {
        if (dynamic_cast<BatteryDecorator*>(entityList->at(i)) != nullptr) {
          BatteryDecorator* batt =
            dynamic_cast<BatteryDecorator*>(entityList->at(i));
          if (BatteryInRange(batt)) {
            batt->recharge(rechargeRate * dt);
          }
        }
    }
}

bool RechargeStation::BatteryInRange(IEntity* entity) {
  double x = position.x - entity->GetPosition().x;
  double z = position.z - entity->GetPosition().z;
  return x * x + z * z <= radius * radius;
}
