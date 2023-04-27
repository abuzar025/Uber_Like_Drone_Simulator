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
        float distanceToDest = Vector3.Distance(drone.position, drone.destination);
        float droneX = drone.postion.x;
        float droneY = drone.postion.y;
        float droneZ = drone.postion.z;

        
    }

    void writeDataToCSV(string filename) {
        std::ofstream file(filename);

    }
}
