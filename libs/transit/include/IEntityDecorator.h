#ifndef I_ENTITY_DECORATOR_H
#define I_ENTITY_DECORATOR_H

#include "IEntity.h"

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
     * @brief Gets the speed of the drone
     * @return The speed of the drone
     */
    float GetSpeed() const { return entity->GetSpeed(); }

    /**
     * @brief Gets the position of the drone
     * @return The position of the drone
     */
    Vector3 GetPosition() const { return entity->GetPosition(); }

    /**
     * @brief Gets the direction of the drone
     * @return The direction of the drone
     */
    Vector3 GetDirection() const { return entity->GetDirection(); }

    /**
     * @brief Gets the destination of the drone
     * @return The destination of the drone
     */
    Vector3 GetDestination() const { return entity->GetDestination(); }

    /**
     * @brief Gets the color of the drone
     * @return The color of the drone
     */
    std::string GetColor() const { return entity->GetColor(); }

    /**
     * @brief Gets the details information of the drone
     * @return The details information of the drone
     */
    JsonObject GetDetails() const { return entity->GetDetails(); }

    /**
     * @brief Gets the availability of the drone
     * @return The availability of the drone
     */
    bool GetAvailability() const { return entity->GetAvailability(); }

    /**
     * @brief Updates the drone's position
     * @param dt Delta time
     * @param scheduler Vector containing all the entities in the system
     */
    void Update(double dt, std::vector<IEntity*> scheduler) {
        if (entity != nullptr) {
            OverridedUpdate(dt, scheduler);
        }
    }

    /**
     * @brief Sets the position of the drone
     * @param pos_ The new position of the drone
     */
    void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

    /**
     * @brief Sets the direction of the drone
     * @param dir_ The new direction of the drone
     */
    void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

    /**
     * @brief Sets the destination of the drone
     * @param des_ The new destination of the drone
     */
    void SetDestination(Vector3 des_) { entity->SetDirection(des_); }

    /**
     * @brief Sets the color of the drone
     * @param col_ The new color of the drone
     */
    void SetColor(std::string col_) { entity->SetColor(col_); }

    /**
     * @brief Rotates the drone
     * @param angle The angle by which the drone should be rotated
     */
    void Rotate(double angle) { entity->Rotate(angle); }

    /**
     * @brief Makes the drone jump
     * @param height The height at which the drone should jump
     */
    void Jump(double height) { entity->Jump(height); }

    /**
     * @brief Removing the copy constructor and assignment operator
     * so that drones cannot be copied.
     */
    IEntityDecorator(const IEntityDecorator& entityDecorator) = delete;
    IEntityDecorator& operator=(const IEntityDecorator& entityDecorator) = delete;
  protected:
    IEntity* entity;

};

#endif