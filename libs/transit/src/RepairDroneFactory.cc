#include "RepairDroneFactory.h"

IEntity* RepairDroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("repairdrone") == 0) {
    std::cout << "Repair Drone Created" << std::endl;
    return new RepairDrone(entity);
  }
  return nullptr;
}
