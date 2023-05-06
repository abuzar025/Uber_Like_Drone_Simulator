#ifndef RECHARGE_STATION_H
#define RECHARGE_STATION_H

#include "IEntity.h"


/**
 * @brief this class inherits from the IEntity class and represents 
 * the recharge stations for drone entity. 
 */

class RechargeStation: public IEntity {
 public:
    /**
     * @brief RechargeStations are created with a name
     * @param obj JSON object containing the Recharge Station's information
     */
    RechargeStation(JsonObject& obj);

    /**
     * @brief Destructor
     */
    ~RechargeStation();

    /**
     * @brief Gets the speed of the Recharge Station
     * @return The speed of the Recharge Station
     */
    float GetSpeed() const { return 0; }

    /**
     * @brief Gets the position of the Recharge Station
     * @return The position of the Recharge Station
     */
    Vector3 GetPosition() const { return position; }

    /**
     * @brief Gets the direction of the Recharge Station
     * @return The direction of the Recharge Station
     */
    Vector3 GetDirection() const { return direction; }

    /**
     * @brief Gets the destination of the Recharge Station
     * @return The destination of the Recharge Station
     */
    Vector3 GetDestination() const { return position; }

    /**
     * @brief Gets the color of the Recharge Station
     * @return The color of the Recharge Station
     */
    std::string GetColor() const { return color; }

    /**
     * @brief Gets the details information of the Recharge Station
     * @return The details information of the Recharge Station
     */
    JsonObject GetDetails() const { return details; }

    /**
     * @brief Gets the availability of the Recharge Station
     * @return The availability of the Recharge Station
     */
    bool GetAvailability() const { return available; }

    /**
    * @brief A public member function that returns the recharge rate of a RechargeStation object.
    * @return A double representing the recharge rate of a RechargeStation object.
    */ 
    double GetRechargeRate() const { return rechargeRate; }

    /**
     * @brief Updates the Recharge Station's position
     * @param dt Delta time
     * @param scheduler Vector containing all the entities in the system
     */
    void Update(double dt, std::vector<IEntity*> scheduler);

    /**
     * @brief Sets the position of the Recharge Station
     * @param pos_ The new position of the Recharge Station
     */
    void SetPosition(Vector3 pos_) { position = pos_; }

    /**
     * @brief Sets the direction of the Recharge Station
     * @param dir_ The new direction of the Recharge Station
     */
    void SetDirection(Vector3 dir_) { direction = dir_; }

    /**
     * @brief Sets the destination of the Recharge Station
     * @param des_ The new destination of the Recharge Station
     */
    void SetDestination(Vector3 des_) {}

    /**
     * @brief Sets the color of the Recharge Station
     * @param col_ The new color of the Recharge Station
     */
    void SetColor(std::string col_) { color = col_; }

    /**
     * @brief Sets the entity list of the entity
     * @param entityList_ The new entity list of the entity
     */
    void SetEntityList(std::vector<IEntity*>* entityList_) { entityList = entityList_; }
    /**
    * @brief A public member function that sets the recharge rate of a RechargeStation object.
    * @param rate A double representing the recharge rate of a RechargeStation object.
    */
    void SetRechargeRate(double rate) { rechargeRate = rate; }
    /**
    * @brief A public member function that returns the radius of a RechargeStation object.
    * @return A double representing the radius of a RechargeStation object.
    */
    double GetRadius() {return radius;}

    /**
    * @brief A public member function that checks whether an IEntity object is within the range of a RechargeStation object.
    * @param entity A pointer to the IEntity object to be checked.
    * @return A boolean indicating whether the IEntity object is within range of the RechargeStation object.
    */
    bool BatteryInRange(IEntity* entity);

    /**
     * @brief Removing the copy constructor and assignment operator
     * so that Recharge Stations cannot be copied.
     */
    RechargeStation(const RechargeStation& station) = delete;
    RechargeStation& operator=(const RechargeStation& station) = delete;

 private:
    JsonObject details;
    Vector3 position;
    Vector3 direction;
    std::string color = "None";  // None means default color
    bool available;
    double rechargeRate;
    double radius;
    std::vector<IEntity*>* entityList;
};

#endif
