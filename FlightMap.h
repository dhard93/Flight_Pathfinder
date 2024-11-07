#include <fstream>
#include <iostream>
#include <deque>
#include <stack>
#include <list>
#include <vector>
#include <unordered_map>
#include "Type.h"
using namespace std;

#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H


class FlightMapClass {
public:

    /*******************************
     * Constructors and Destructor *
     *******************************/

    // default constructor
    FlightMapClass();


    // copy constructor
    FlightMapClass(const FlightMapClass &f);


    // destructor
    ~FlightMapClass();

    /*****************************
     * FlightMapClass Operations *
     *****************************/

    void ReadCities(ifstream &myCities);
    // Read cities from a data file
    // Pre-condition: Input stream is provided
    // Post-condition: Data file is read
    //				  Cities are in ascending order


    void BuildMap(ifstream &myFlights);
    // Reads flight information and build the adjacency list
    // Pre-condition: list of the flight information is provided
    // Post-condition: Flight map is built


    void DisplayHeader();


    void DisplayMap();
    // Displays the flight map in a formatted table
    // Pre-condition: none
    // Post-condition: Flight map is displayed


    // Check whether a city is in the cities that EastWest airline serves.
    // Pre-condition: cityNumber to be checked is provided
    // Post-condition: return true if the city is in the cities array
    //              otherwise return false
    bool CheckCity(string cityName) const;


    // Displays all of the cities
    void DisplayAllCities() const;


    // Marks a city as visited
    // Pre-condition: city to be marked as visited is provided
    // Post-condition: a city is marked as visited
    void MarkVisited(int city);


    // Clears marks on all cities
    // Pre-condition: there are > 0 cities in a cities array
    // Post-condition: all cities marked as unvisited
    void UnvisitAll();


    // Determines whether a city was visited
    // Pre-condition: city is provided
    // Post-condition: return true if city has been visited
    //              otherwise return false
    bool IsVisited(int city) const;


    // Determines the next unvisited city, if any,
    // that is adjacent to a given city.
    // success indicates whether an unvisited adjacent city was found
    // Pre-condition: topCity and nextCity provided
    // Post-condition: return true if an unvisited adjacent city was found
    //              otherwise return false
    bool GetNextCity(string fromCity, string &nextCity);


    // returns the integer index corresponding to a city name
    // Pre-condition: name of a city is provided
    // Post-condition: returns the index number corresponding to a city name
    int GetCityNumber(string cityName) const;


    // returns the name of a city given its corresponding index
    // Pre-condition: number of a city is provided
    // Post-condition: returns the city's name
    string GetCityName(int cityNumber) const;


    // Determines whether a sequence of flights between two cities exists.
    // Pre-condition: originCity and destinationCity are the origin and destination city, respectively
    // Post-condition: returns true if a sequence of flights exists
    //              from origin to destination; otherwise return false.
    //              Cities visited during the search are marked as visited
    //              in the flight map.
    void FindPath(int originCity, int destinationCity);


    /*******************************
     * Initial methods added by me *
     *******************************/

    // Unmarks a city as visited
    // Pre-condition: city to be unmarked as visited is provided
    // Post-condition: a city is unmarked as visited
    void UnmarkVisited(const int city);

    void GetPaths(int orig, int des);
    void dfs(int origin, int destination, int &pIndex, vector<pathStruct> &paths);


    // Add new pathStruct to vector of pathStructs, which are used to store the flights of a path from a desired origin to destination
    // as well as the total cost of all flights in the path.
    // Pre-condition:  A new path of flights from desired origin to destination has been identified.
    // Post-condition: The new pathStruct is added to the vector
    void AddPath(list<flightRec> *fMap, stack<int> &st, deque<int> &pDeq, vector<pathStruct> &pVec, unordered_map<int, int> &oMap, int &top, int &pathInd, const int &destionation);


    // Display the least expensive path of flights in the pathStruct vector.
    // Pre-condition:  all viable paths from origin to destination have been identified
    // Post-condition: the flights in the least expensive path from origin to destination are displayed
    void DisplayPath(vector<pathStruct> &allPaths, const int &origin, const int &destination);


    // Use stack to identify paths from origin city to destination city.
    // Pre-condition:  origin city and destination city have been defined and the origin city has been pushed onto the stack
    // Post-condition: all viable paths from origin city to destination city are stored as pathStructs in the pathStruct vector
    void ConstructPaths(stack<int> &pStack, deque<int> &pDeque, vector<pathStruct> &pVec, int &pIndex, const int &oCity, const int &dCity);

private:
  int size;              // number of cities
  vector<string> cities; // list of cities
  list<flightRec> *map;  // flight map
  vector<bool> visited;  // newly added for this part: to check if a city has been visited before
};

#endif