#define _USE_MATH_DEFINES
#include "DataCollector.h"

<<<<<<< HEAD
    // protected: 

};
=======
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
>>>>>>> b0542e64e44dafd70b35d3613ce8867f26f055e1
