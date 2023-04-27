#ifndef DATACOLLECTOR_H_
#define DATACOLLECTOR_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include "math/vector3.h"
#include "Drone.h"
#include "BatteryDecorator.h"

using namespace std;

/**
 * @class DataCollector
 * @brief Represents a singleton class that collect drone pertaining
 * the drone and its surroundings. It then stores this data into a csv.
 */

class DataCollector {

    public:

        static DataCollector& getInstance();

       /**
        * Singletons should not be cloneable.
        */
        DataCollector(const DataCollector& other) = delete;

        /**
        * Singletons should not be assignable.
        */
        DataCollector& operator=(const DataCollector& other) = delete;

        /**
         * @brief DataCollector desconstructor
        */
        ~DataCollector();

        /**
         * @brief This method takes a drone object to calculate and store certain data points into to the singleton class
         * @param drone The input is a refrence to a Drone object which we will read the data of
        */
       void collectData(const Drone& drone);

       void collectBatteryLevel(const BatteryDecorator& battery);

       /**
        * @brief This method uses data stored in this class to write the data into a csv file
       */
        void writeDataToCSV(string filename);

        
    
    private:
        DataCollector();
        float eta;
        int numTrips;
        float distanceToDest;
        float batteryLevel;
        float droneX;
        float droneY;
        float droneZ;
};

#endif
