#include "SimulationModel.h"

#include "DataCollector.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "RechargeStationFactory.h"
#include "RepairDroneFactory.h"
#include "BatteryDecoratorFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new RechargeStationFactory());
  AddFactory(new RepairDroneFactory());
  AddFactory(new BatteryDecoratorFactory(compFactory));
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  delete graph;
  delete compFactory;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  // Technically, position isn't necessary
  // Name is necessary unless you are using Decorators
  std::cout << "Created Entity of type " << type;
  if (entity.Contains("name") && entity.Contains("position")) {
    std::string name = entity["name"];
    JsonArray position = entity["position"];
    std::cout << ", name " << name << ", and position " << position;
  }
  std::cout << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  myNewEntity->SetEntityList(&entities);

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);
    controller.UpdateEntity(*entities[i]);
  }
  DataCollector::getInstance().OnTick(entities, dt);
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
