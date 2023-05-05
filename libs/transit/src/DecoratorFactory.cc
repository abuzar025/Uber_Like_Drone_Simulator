#include "DecoratorFactory.h"

IEntity* DecoratorFactory::CreateEntity(JsonObject& entity) {
  if (ShouldMakeNewEntity(entity)) {
    JsonObject wrappedData = entity["entity"];
    IEntity* toBeWrapped = compositeFactory->CreateEntity(wrappedData);
    if (toBeWrapped != nullptr) {
        IEntity* result = CreateDecoratedEntity(toBeWrapped, entity);
        if (result != nullptr) {
            return result;
        } else {
            delete toBeWrapped;
        }
    }
  }
  return nullptr;
}
