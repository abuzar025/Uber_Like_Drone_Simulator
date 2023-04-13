#include "BatteryDecorator.h"

void BatteryDecorator::OverridedUpdate(double dt, std::vector<IEntity*> scheduler) {
    double amount = 0.0f;
    if (charge >= dt) {
        amount = dt;
    } else if (charge >= 0) {
        amount = charge;
    } else {
        return;
    }
    charge -= amount;
    entity->Update(amount, scheduler);
    
}

void BatteryDecorator::recharge(double amount) {
    charge += amount;
    if (charge > maxCharge) {
        charge = maxCharge;
    }
}