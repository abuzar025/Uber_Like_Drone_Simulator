#ifndef DATACOLLECTOR_H_
#define DATACOLLECTOR_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <unordered_map>

#include "math/vector3.h"
#include "IEntity.h"
#include "BatteryDecorator.h"

using namespace std;

/**
 * @class DataEntry
 * @brief INTERNAL DATA; DO NOT USE OUTSIDE DataCollector
 */
class DataEntry {
 public:
  /**
  * @brief A public class member variable that represents the data collection period of a DataEntry object.
  */
  double collectionPeriod;
  /**
  * @brief A public class member variable that represents the time elapsed since the last data collection of a DataEntry object.
  */
  double timeSinceLastCollection = 0;
  /**
  * @brief A public class member variable that represents the output stream of a DataEntry object.
  */
  ofstream* output;
};

/**
 * @class DataCollector
 * @brief Represents a singleton class that collect drone pertaining
 * the drone and its surroundings. It then stores this data into a csv.
 */

class DataCollector {
 public:
       /**
       * @brief Returns the instance of the `DataCollector`.
       */
       static DataCollector& getInstance();

       /**
        * @brief Singletons should not be cloneable.
        */
       DataCollector(const DataCollector& other) = delete;

       /**
        * @brief Singletons should not be assignable.
        */
       DataCollector& operator=(const DataCollector& other) = delete;

       /**
        * @brief DataCollector desconstructor
        */
       ~DataCollector();

       /**
        * @brief This method takes a entity to calculate and store certain data points into to the singleton class
        * @param entity The input is a refrence to a IEntity object which we will read the data of
        */
       void collectData(IEntity* entity);

       /**
        * @brief This method takes a entity to calculate and store certain data points into to the singleton class
        * @param entites The input is a refrence to a IEntity object which we will read the data of
        * @param dt Delta time
        */
       void OnTick(std::vector<IEntity*>& entites, double dt);

       /**
        * @brief This method opens the csv file to write to
       */
       void OpenCSV(IEntity* entity);

       /**
        * @brief This method closes the csv files
        */
       void CloseCSV();

 private:
       DataCollector();
       std::unordered_map<int, DataEntry> entries;
};

#endif
