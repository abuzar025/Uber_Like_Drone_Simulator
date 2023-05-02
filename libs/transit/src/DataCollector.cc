#define _USE_MATH_DEFINES
#include "DataCollector.h"

using namespace std;

DataCollector::DataCollector() {};

DataCollector& DataCollector::getInstance() {
    static DataCollector instance;
    return instance;
}

void DataCollector::collectData(const Drone& drone) {
    distanceToDest = drone.GetPosition().Distance(drone.GetDestination());
    droneX = drone.GetPosition().x;
    droneY = drone.GetPosition().y;
    droneZ = drone.GetPosition().z;

    eta = distanceToDest / drone.GetSpeed();
}

void DataCollector::collectBatteryLevel(const BatteryDecorator& battery) {
    batteryLevel = battery.getCharge();
}

void DataCollector::writeDataToCSV(string filename) const{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << '\n';
        return;
    }

    file << "Timestamp, X Coordinate, Y Coordinate, Z Coordinate, Distance to Destination, Time to Arrival, Battery Level\n";
    /* Line not functional -> clock not implemented correctly */
    // file << clock.now() << ',' << droneX << ',' << droneY << ',' << droneZ << ',' << distanceToDest << ',' << eta << ',' << batteryLevel << "\n";
    file.close();

}
