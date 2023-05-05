#ifndef DECORATOR_FACTORY_H_
#define DECORATOR_FACTORY_H_

#include <vector>

#include "CompositeFactory.h"
#include "IEntityFactory.h"
#include "IEntityDecorator.h"

/**
 *@brief Decorator Factory to produce IEntityDecorator class.
 **/
class DecoratorFactory : public IEntityFactory {
 public:
  /**
   * @brief Constructor that sets a pointer to a CompositeFactory.
   * @param compositeFactory the CompositeFactory to point to
   */
  DecoratorFactory(CompositeFactory* compositeFactory):
  compositeFactory(compositeFactory) {}

  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~DecoratorFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);

  /**
   * @brief Creates the decorator around an entity using the given JSON object, if possible.
   * @param wrapped - IEntity to wrap around.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Decorated entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  virtual IEntity* CreateDecoratedEntity(IEntity* wrapped, JsonObject& entity) = 0;

  /**
   * @brief Decides if this factory should produce the new entity
   * @param entity - JsonObject to be used to create the new entity.
   * @return If this factory should make the new entity
   **/
  virtual bool ShouldMakeNewEntity(JsonObject& entity) = 0;

 private:
  CompositeFactory* compositeFactory;
};

#endif
