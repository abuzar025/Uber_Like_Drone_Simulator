#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityDecorator.h"

/**
 * @brief this class inhertis from the IEntityDecorator class. The purpose of this class is to 
 * modify the behavior of an IEntity object by adding a battery to it.
 */
clas
class BatteryDecorator: public IEntityDecorator {
  public:
    /**
     * @brief Constructor that assigns a unique ID to the battery.
     */
    BatteryDecorator(IEntity* wrapped, double maxCharge): IEntityDecorator(wrapped), maxCharge(maxCharge), charge(maxCharge) {}

     /**
     * @brief What to override to modify the behaviour of the surrounding IEntity
     * @param dt The time step of the update.
     * @param scheduler The list of all entities in the system.
     */
    virtual void OverridedUpdate(double dt, std::vector<IEntity*> scheduler);

    void recharge(double amount);

    double getCharge() {return charge;}

    const double maxCharge;

  private:
    double charge;

};

#endif