#ifndef DATACOLLECTOR_H_
#define DATACOLLECTOR_H_

#include <csv>
#include <vector>
#include <ctime>

#include "math/vector3.h"

/**
 * @class DataCollector
 * @brief Represents a singleton class that collect drone pertaining
 * the drone and its surroundings. It then stores this data into a csv.
 */

Class DataCollector :
    public:
        /**
         * @brief DataCollector class constructor
        */
        DataCollector();

        /**
         * @brief DataCollector desconstructor
        */
        ~DataCollector();

        /**
         * @brief This method takes a drone object to calculate and store certain data points into to the singleton class
         * @param drone The input is a refrence to a Drone object which we will read the data of
        */
       void collectData(const Drone& drone);

       /**
        * @brief This method uses data stored in this class to write the data into a csv file
       */
      void logData();
    
    private:
        Time eta;
        int numTrips;
        double distanceToDest;
        double batteryLevel;        

