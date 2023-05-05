#define _USE_MATH_DEFINES
#include "DataCollector.h"

using namespace std;

class DataEntry {
 public:
  double collectionPeriod;
  double timeSinceLastCollection = 0;
  ofstream* output;
};

DataCollector::~DataCollector() {
    CloseCSV();
}

DataCollector::DataCollector() {}

DataCollector& DataCollector::getInstance() {
    static DataCollector instance;
    return instance;
}

void DataCollector::collectData(IEntity* entity) {

    DataEntry& entry = entries[entity->GetId()];

    time_t clock;
    time(&clock);

    float distanceToDest = entity->GetPosition().Distance(entity->GetDestination());
    float x = entity->GetPosition().x;
    float y = entity->GetPosition().y;
    float z = entity->GetPosition().z;
    float speed = entity->GetSpeed();

    float eta = distanceToDest / speed;

    (*(entry.output)) << asctime(localtime(&clock)) << ',' << x << ',' << y << ',' << z << ',' << speed << ',' << distanceToDest << ',' << eta;

    BatteryDecorator* battery = dynamic_cast<BatteryDecorator*>(entity);
    if (battery != nullptr) {
        (*(entry.output)) << ',' << battery->getCharge();
    }
    (*(entry.output)) << std::endl;
}

void DataCollector::OnTick(std::vector<IEntity*>& entities, double dt) {
    for (auto iter = entities.begin(); iter != entities.end(); iter++) {
        JsonObject details = (*iter)->GetDetails();
        if (details.Contains("dataCollectionPeriod")) {
            int id = (*iter)->GetId();
            if (entries.count((*iter)->GetId()) <= 0) {
                OpenCSV(*iter);
            }
            DataEntry& entry = entries[id];
            entry.timeSinceLastCollection += dt;
            if (entry.timeSinceLastCollection >= entry.collectionPeriod) {
                entry.timeSinceLastCollection -= entry.collectionPeriod;
                collectData(*iter);
            }
        }
    }
}

void DataCollector::OpenCSV(IEntity* entity) {
    JsonObject details = entity->GetDetails();
    JsonObject nameDetails = details;

    while (!nameDetails.Contains("name")) {
        if (!nameDetails.Contains("entity")) {
            return;
        }
        nameDetails = nameDetails["entity"];
    }
    std::string name = nameDetails["name"];

    std::string filename = ("entity_" + entity->GetId()) + "_" + name + ".csv";

    ofstream* file = new ofstream(filename);
    if (!file->is_open()) {
        cerr << "Error opening file: " << filename << '\n';
        return;
    }

    DataEntry entry;
    entry.collectionPeriod = details["dataCollectionPeriod"];
    entry.output = file;

    (*(entry.output)) << "Timestamp, X Coordinate, Y Coordinate, Z Coordinate, Speed,  Distance to Destination, Time to Arrival";
    if (dynamic_cast<BatteryDecorator*>(entity) != nullptr) {
        (*(entry.output)) << ", Battery Level";
    }
    (*(entry.output)) << std::endl;

    entries[entity->GetId()] = entry;
}

void DataCollector::CloseCSV() {
    for (auto iter = entries.begin(); iter != entries.end(); iter++) {
        iter->second.output->close();
        delete iter->second.output;
    }
    entries.clear();
}
