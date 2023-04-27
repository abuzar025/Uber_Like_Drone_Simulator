#define _USE_MATH_DEFINES
#include "DataCollector.h"

using namespace std;

class DataCollector() {

    DataCollector::DataCollector() {};

    DataCollector& DataCollector::getInstance() {
        static DataCollector instance;
        return instance;
    }

    void DataCollector::collectData(const Drone& drone) {
        distanceToDest = Vector3.Distance(drone.GetPosition(), drone.GetDestination());
        droneX = drone.GetPosition().x;
        droneY = drone.GetPosition().y;
        droneZ = drone.GetPosition().z;

        eta = distanceToDest / drone.GetSpeed();
    }

    void DataCollector::collectBatteryLevel(const BatteryDecorator& battery) {
        batteryLevel = battery.getCharge();
    }

    void writeDataToCSV(string filename) {
        std::ofstream file(filename);

    }
}
