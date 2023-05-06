#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include "IStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class CelebrationDecorator : public IStrategy {
 protected:
   /**
   * @brief The strategy used by the object.
   *
   * This pointer represents the current strategy used by the object.
   */
  IStrategy* strategy;

  /**
   * @brief The current time of the object.
   *
   * This variable represents the current time of the object, measured in seconds.
   */
  float time;

 public:
  /**
   * @brief Construct a new Celebration Decorator object
   *
   * @param strategy the strategy to decorate onto
   */
  CelebrationDecorator(IStrategy* strategy);


  /**
   * @brief Celebration Destructor
   */
  ~CelebrationDecorator();

  /**
   * @brief Move the entity with the behavior as described for 4 seconds.
   * 
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void Move(IEntity* entity, double dt) = 0;

  /**
   * @brief Check if the movement is completed by checking the time.
   *
   * @return True if complete, false if not complete
   */
  virtual bool IsCompleted();

  /**
   * @brief Get the distance left to travel
   * 
   * @return the distance left to travel
   */
  virtual double GetDistance(Vector3 from) {
    return strategy->GetDistance(from);
  }
};

#endif  // CELEBRATION_DECORATOR_H_
