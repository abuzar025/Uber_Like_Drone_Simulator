#ifndef REPAIR_DRONE_H
#define REPAIR_DRONE_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "Drone.h"

/**
 * @class RepairDrone
 * @brief Represents a RepairDrone in a physical system
 *
 * RepairDrones move using euler integration based on a specified
 * velocity and direction.
 */
class RepairDrone : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the RepairDrone's information
   */
  RepairDrone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~RepairDrone() override = default;

  /**
   * @brief Gets the RepairDrone's position
   * @return The RepairDrone's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the RepairDrone's direction
   * @return The RepairDrone's direction
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the RepairDrone's destination
   * @return The RepairDrone's destination
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the RepairDrone's availability
   * @return The RepairDrone's availability
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the RepairDrone's details
   * @return The RepairDrone's details
   */
  JsonObject GetDetails() const override;

  /**
   * @brief Gets the RepairDrone's speed
   * @return The RepairDrone's speed
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  std::string GetStrategyName() const { return strategyName; }

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  void SetStrategyName(std::string strategyName_) {
    strategyName = strategyName_;
  }

  /**
   * @brief Sets the RepairDrone's availability
   * @param choice The new availability of the RepairDrone
   */
  void SetAvailability(bool choice);

  /**
   * @brief Sets the RepairDrone's position
   * @param pos_ The new position of the RepairDrone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the RepairDrone's direction
   * @param dir_ The new direction of the RepairDrone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the RepairDrone's destination
   * @param des_ The new destination of the RepairDrone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  void RepairingDrone() *****


  /**
   * @brief Rotates the RepairDrone
   * @param angle The angle by which the RepairDrone should be rotated
   */
  void Rotate(double angle);

 private:
  
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
  std::string strategyName;
};

#endif  // REPAIR_DRONE_H
