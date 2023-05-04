#ifndef REPAIR_DRONE_FACTORY_H_
#define REPAIR_DRONE_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "IEntity.h"
#include "RepairDrone.h"

/**
 *@brief Repair drone factory to produce Repair drone.
 **/
class RepairDroneFactory : public IEntityFactory {
 public:
        /**
        * @brief Destructor for RepairDroneFactory class.
        **/
        virtual ~RepairDroneFactory() {}

        /**
        * @brief Creates entity using the given JSON object, if possible.
        * @param entity - JsonObject to be used to create the new entity.
        * @return Entity that was created if it was created successfully, or a
        *nullpointer if creation failed.
        **/
        IEntity* CreateEntity(JsonObject& entity);
};

#endif
