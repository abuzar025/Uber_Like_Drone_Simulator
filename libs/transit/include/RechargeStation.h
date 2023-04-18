#ifndef RECHARGE_STATION_H
#define RECHARGE_STATION_H

#include "IEntity.h"

/**
 * @brief this class inhertis from the IEntity class and represents 
 * the recharge stations for drone entity. 
 */

class RechargeStation: public IEntity {
  public:
    /**
     * @brief Drones are created with a name
     * @param obj JSON object containing the drone's information
     */
    RechargeStation(JsonObject& obj);

    /**
     * @brief Destructor
     */
    ~RechargeStation();

    /**
     * @brief Gets the speed of the drone
     * @return The speed of the drone
     */
    float GetSpeed() const { return 0; }

    /**
     * @brief Gets the position of the drone
     * @return The position of the drone
     */
    Vector3 GetPosition() const { return position; }

    /**
     * @brief Gets the direction of the drone
     * @return The direction of the drone
     */
    Vector3 GetDirection() const { return direction; }

    /**
     * @brief Gets the destination of the drone
     * @return The destination of the drone
     */
    Vector3 GetDestination() const { return position; }

    /**
     * @brief Gets the color of the drone
     * @return The color of the drone
     */
    std::string GetColor() const { return color; }

    /**
     * @brief Gets the details information of the drone
     * @return The details information of the drone
     */
    JsonObject GetDetails() const { return details; }

    /**
     * @brief Gets the availability of the drone
     * @return The availability of the drone
     */
    bool GetAvailability() const { return available; }

    /**
     * @brief Updates the drone's position
     * @param dt Delta time
     * @param scheduler Vector containing all the entities in the system
     */
    void Update(double dt, std::vector<IEntity*> scheduler);

    /**
     * @brief Sets the position of the drone
     * @param pos_ The new position of the drone
     */
    void SetPosition(Vector3 pos_) { position = pos_; }

    /**
     * @brief Sets the direction of the drone
     * @param dir_ The new direction of the drone
     */
    void SetDirection(Vector3 dir_) { direction = dir_; }

    /**
     * @brief Sets the destination of the drone
     * @param des_ The new destination of the drone
     */
    void SetDestination(Vector3 des_) {}

    /**
     * @brief Sets the color of the drone
     * @param col_ The new color of the drone
     */
    void SetColor(std::string col_) { color = col_; }

    /**
     * @brief Removing the copy constructor and assignment operator
     * so that drones cannot be copied.
     */
    RechargeStation(const RechargeStation& drone) = delete;
    RechargeStation& operator=(const RechargeStation& drone) = delete;

private:
    JsonObject details;
    Vector3 position;
    Vector3 direction;
    std::string color = "None";  // None means default color
    bool available;
};

#endif