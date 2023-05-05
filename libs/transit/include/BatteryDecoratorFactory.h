#ifndef BATTERY_DECORATOR_FACTORY_H_
#define BATTERY_DECORATOR_FACTORY_H_

#include <vector>

#include "DecoratorFactory.h"
#include "BatteryDecorator.h"

/**
 *@brief Battery Decorator Factory to produce Battery Decorators.
 **/
class BatteryDecoratorFactory : public DecoratorFactory {
 public:
  /**
   * @brief Constructor that sets a pointer to a CompositeFactory.
   * @param compositeFactory the CompositeFactory to point to
   */
  BatteryDecoratorFactory(CompositeFactory* compositeFactory):
  DecoratorFactory(compositeFactory) {}

  /**
  * @brief Destructor for BatteryDecoratorFactory class.
  **/
  virtual ~BatteryDecoratorFactory() {}

  /**
   * @brief Creates the decorator around an entity using the given JSON object, if possible.
   * @param wrapped - IEntity to wrap around.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Decorated entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateDecoratedEntity(IEntity* wrapped, JsonObject& entity);

  /**
   * @brief Decides if this factory should produce the new entity
   * @param entity - JsonObject to be used to create the new entity.
   * @return If this factory should make the new entity
   **/
  bool ShouldMakeNewEntity(JsonObject& entity);
};

#endif
