#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityDecorator.h"
#include "IStrategy.h"
#include "RechargeStation.h"

/**
 * @brief this class inhertis from the IEntityDecorator class. The purpose of this class is to 
 * modify the behavior of an IEntity object by adding a battery to it.
 */
class BatteryDecorator: public IEntityDecorator {
 public:
    /**
     * @brief Constructor that assigns a unique ID to the battery.
     */
    BatteryDecorator(IEntity* wrapped, double maxCharge, double drainRate):
    IEntityDecorator(wrapped), maxCharge(maxCharge), charge(maxCharge), drainRate(drainRate), recharging(false), completelyDrained(true) {}

    /**
     * @brief Constructor that assigns a unique ID to the battery.
     * Values are taken from a JsonObject
     */
    BatteryDecorator(IEntity* wrapped, JsonObject& obj):
    BatteryDecorator(wrapped, obj["maxCharge"], obj["drainRate"]) {}

    /**
     * @brief Destructor
     */
    ~BatteryDecorator();

     /**
     * @brief What to override to modify the behaviour of the surrounding IEntity
     * @param dt The time step of the update.
     * @param scheduler The list of all entities in the system.
     */
    virtual void OverridedUpdate(double dt, std::vector<IEntity*> scheduler);

    /**
     * @brief Recharges the battery by the specified amount.
     *
     * @param amount The amount to recharge the battery by.
     * @return True if the recharge was successful, false otherwise.
     */
    bool recharge(double amount);

    /**
     * @brief Gets the current charge of the battery.
     *
     * @return The current charge of the battery.
     */
    double getCharge() const {return charge;}
    
    /**
     * @brief Determines if the battery is or will be marooned.
     *
     * @return True if the battery is or will be marooned, false otherwise.
     */
    bool IsOrWillBeMarooned();

    /**
     * @brief The maximum charge of the battery.
     */
    const double maxCharge;

    /**
     * @brief The rate at which the battery drains.
     */
    const double drainRate;

 private:
    double charge;
    bool recharging;
    bool completelyDrained;
    IStrategy* toRechargeStation = nullptr;
    RechargeStation* targetRechargeStation = nullptr;
};

#endif
