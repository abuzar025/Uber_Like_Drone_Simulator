#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityDecorator.h"

class BatteryDecorator: public IEntityDecorator {
  public:
    /**
     * @brief Constructor that assigns a unique ID to the battery.
     */
    BatteryDecorator(IEntity* wrapped): IEntityDecorator(wrapped) {}

     /**
     * @brief What to override to modify the baheavior of the surrounding IEntity
     * @param dt The time step of the update.
     * @param scheduler The list of all entities in the system.
     */
    virtual void OverridedUpdate(double dt, std::vector<IEntity*> scheduler);

};

#endif