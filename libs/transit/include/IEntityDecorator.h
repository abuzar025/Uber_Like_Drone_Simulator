#ifndef I_ENTITY_DECORATOR_H
#define I_ENTITY_DECORATOR_H

#include "IEntity.h"

/** 
 * @brief The IEntityDecorator class is an abstract base class for decorators that 
 * modify the behavior of the surrounding IEntity. It inherits from the IEntity class 
 * and provides the basic functionality of an entity.
*/ 
class IEntityDecorator: public IEntity {
  public:
    /**
     * @brief Constructor that assigns a unique ID to the entity.
     */
    IEntityDecorator(IEntity* wrapped): entity(wrapped) {}

    /**
     * @brief What to override to modify the baheavior of the surrounding IEntity
     * @param dt The time step of the update.
     * @param scheduler The list of all entities in the system.
     */
    virtual void OverridedUpdate(double dt, std::vector<IEntity*> scheduler) = 0;

    /**
     * @brief Gets the speed of the wrapped entity 
     * @return The speed of the wrapped entity 
     */
    float GetSpeed() const { return entity->GetSpeed(); }

    /**
     * @brief Gets the position of the wrapped entity 
     * @return The position of the wrapped entity 
     */
    Vector3 GetPosition() const { return entity->GetPosition(); }

    /**
     * @brief Gets the direction of the wrapped entity 
     * @return The direction of the wrapped entity 
     */
    Vector3 GetDirection() const { return entity->GetDirection(); }

    /**
     * @brief Gets the destination of the wrapped entity 
     * @return The destination of the wrapped entity 
     */
    Vector3 GetDestination() const { return entity->GetDestination(); }

    /**
     * @brief Gets the color of the wrapped entity 
     * @return The color of the wrapped entity 
     */
    std::string GetColor() const { return entity->GetColor(); }

    /**
     * @brief Gets the details information of the wrapped entity 
     * @return The details information of the wrapped entity 
     */
    JsonObject GetDetails() const { return entity->GetDetails(); }

    /**
     * @brief Gets the availability of the wrapped entity 
     * @return The availability of the wrapped entity 
     */
    bool GetAvailability() const { return entity->GetAvailability(); }

    /**
     * @brief Updates the wrapped entity 's position
     * @param dt Delta time
     * @param scheduler Vector containing all the entities in the system
     */
    void Update(double dt, std::vector<IEntity*> scheduler) {
        if (entity != nullptr) {
            OverridedUpdate(dt, scheduler);
        }
    }

    /**
     * @brief Sets the position of the wrapped entity 
     * @param pos_ The new position of the wrapped entity 
     */
    void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

    /**
     * @brief Sets the direction of the wrapped entity 
     * @param dir_ The new direction of the wrapped entity 
     */
    void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

    /**
     * @brief Sets the destination of the wrapped entity 
     * @param des_ The new destination of the wrapped entity 
     */
    void SetDestination(Vector3 des_) { entity->SetDirection(des_); }

    /**
     * @brief Sets the color of the wrapped entity 
     * @param col_ The new color of the wrapped entity 
     */
    void SetColor(std::string col_) { entity->SetColor(col_); }

    /**
     * @brief Rotates the wrapped entity 
     * @param angle The angle by which the wrapped entity  should be rotated
     */
    void Rotate(double angle) { entity->Rotate(angle); }

    /**
     * @brief Makes the wrapped entity  jump
     * @param height The height at which the wrapped entity  should jump
     */
    void Jump(double height) { entity->Jump(height); }

    /**
     * @brief Removing the copy constructor and assignment operator
     * so that wrapped entity s cannot be copied.
     */
    IEntityDecorator(const IEntityDecorator& entityDecorator) = delete;
    IEntityDecorator& operator=(const IEntityDecorator& entityDecorator) = delete;
  protected:
    IEntity* entity;

};

#endif