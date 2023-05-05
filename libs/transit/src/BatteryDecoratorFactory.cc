#include "BatteryDecoratorFactory.h"

IEntity* BatteryDecoratorFactory::CreateDecoratedEntity(IEntity* toBeWrapped, JsonObject& entity) {
  std::cout << "Battery Created" << std::endl;
  return new BatteryDecorator(toBeWrapped, entity);
}

bool BatteryDecoratorFactory::ShouldMakeNewEntity(JsonObject& entity) {
  std::string type = entity["type"];
  return type.compare("battery") == 0;
}
