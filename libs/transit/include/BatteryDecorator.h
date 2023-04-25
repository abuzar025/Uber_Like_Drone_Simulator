#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityDecorator.h"
#include "IStrategy.h"

/**
 * @brief this class inhertis from the IEntityDecorator class. The purpose of this class is to 
 * modify the behavior of an IEntity object by adding a battery to it.
 */
class BatteryDecorator: public IEntityDecorator {
  public:
    /**
     * @brief Constructor that assigns a unique ID to the battery.
     */
    BatteryDecorator(IEntity* wrapped, double maxCharge, double drainRate): IEntityDecorator(wrapped), maxCharge(maxCharge), charge(maxCharge), drainRate(drainRate), recharging(false) {}

     /**
     * @brief What to override to modify the behaviour of the surrounding IEntity
     * @param dt The time step of the update.
     * @param scheduler The list of all entities in the system.
     */
    virtual void OverridedUpdate(double dt, std::vector<IEntity*> scheduler);

    bool recharge(double amount);

    double getCharge() {return charge;}

    bool IsOrWillBeMarooned();

    const double maxCharge;
    const double drainRate;

  private:
    double charge;
    bool recharging;
    IStrategy* toRechargeStation = nullptr;
};

#endif