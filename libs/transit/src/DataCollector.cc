#define _USE_MATH_DEFINES
#include "DataCollector.h"

class DataCollector() {

    DataCollector::DataCollector() {};

    DataCollector& DataCollector::getInstance() {
        static DataCollector instance;
        return instance;
    }

    void DataCollector::collectData(const Drone& drone) {
        
    }

    void writeDataToCSV(string filename) {

    }
}
