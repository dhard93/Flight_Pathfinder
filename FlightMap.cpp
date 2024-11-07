// This file includes function definitions for the FlightMapClass class declared in flightMap.h

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

#include "Type.h"
#include "FlightMap.h"

// Default Constructor
FlightMapClass::FlightMapClass()
{ size = 0; }

// Copy Constructor
FlightMapClass::FlightMapClass(const FlightMapClass &rhs) : size(rhs.size), cities(rhs.cities), visited(rhs.visited)
{
    // Allocate memory for flightList
    map = new list<flightRec>[size];

    // For each entry in parameter FlightMapClass object's flightList, create an equivalent entry in the calling object's flightList
    for (int i = 0; i < size; ++i)
    {
        for (flightRec &flight : rhs.map[i])
            map[i].push_back(flight);
    }
}

// Desctructor
FlightMapClass::~FlightMapClass()
{
    // Deallocate flightList
    delete[] map;
}

// Description:     Read cities file into the cities vector and sort them alphabetically.
// Expected Input:  Input file stream of the input file containing city names
// Expected Output: Cities vector containing all city names from input file is filled and sorted.
void FlightMapClass::ReadCities(ifstream &ifs)
{
    string input;       // Stores each line of text from the input file.

    if (getline(ifs, input))
    {
        size = stoi(input);

        while (getline(ifs, input))
        {
            cities.push_back(input);
            visited.push_back(false);
        }
    }

    // Sort cities alphabetically.
    sort(cities.begin(), cities.end());
}

// Description:     Read flights file into adjacency list where each index of the flightList array is a pointer to an alphacetically sorted list of flightRec structs
//                  corresponding to the city of the same index in the cities vector .
// Expected Input:  Input file stream of the input file containing flight records.
// Expected Output: FlightList array is populated with each index being a pointer to an alphabetically sorted list containing all flight records for the city corresponding
//                  to that same index in the cities vector.
void FlightMapClass::BuildMap(ifstream & ifs)
{
	int flightNum, price;		    //holds the flightNum and price from a data file
	string origin, destination;	    //holds the cities info from a data file
	flightRec temp;			        //holds the data temporarily

    // Allocate memory for flightMap
    map = new list<flightRec>[size];

	//Read each line from the file into a flightRec struct.
	while(ifs >> flightNum >> origin >> destination >> price)
	{
		temp.flightNum = flightNum;
		temp.origin = origin;
		temp.destination = destination;
		temp.price = price;

        // For each index of the flightList, add flightRec to its list only if the origin city is the same city as the
        // corresponding index in the cities vector.
        for (int i = 0; i < size; ++i)
        {
            if (temp.origin == cities[i])
                map[i].push_back(temp);
        }

		ifs.ignore(100, '\n');
  	}

    // Sort each list of flightRec's alphabetically.
    for (int i = 0; i < size; ++i)
        map[i].sort();
}


// Display the formatted header text with labels for each part of a flightRec.
// Pre-condition:  there are flights that need to be displayed
// Post-condition: formatted header labels for flightRec's is displayed.
void FlightMapClass::DisplayHeader()
{
	cout << endl << left << setw(25) << "      Origin" << setw(20) << "Destination"
	<< setw(10) << "Flight#" << setw(7) << "Price" << endl;
	cout << "==============================================================" << endl;
}


// Displays the flight map in a formatted table
// Pre-condition: none
// Post-condition: Flight map is displayed
void FlightMapClass::DisplayMap()
{
    bool originPrinted;     // Flag used to determine if the origin city has been printed yet or not so that
                            // it is only printed once per list
    bool isFirst = true;    // Flag used to determine if dividing line needs to be drawn or not. It is drawn before
                            // each list except for the first list to divide lists.
    string originString;    // Contains text to output for destination. If the origin of a list has not yet been printed,
                            // then it contains the origin city, otherwise it is left blank.

    //Print the entire list by using overloaded output operator for class
    DisplayHeader();

    // Iterate each origin city and output all flightRecs, with each origin city separated by a line for clarity.
	for (int i = 0; i < size; ++i)
    {
        originPrinted = false;

        for (flightRec &flight : map[i])
        {
            if (!originPrinted)
            {
                if (isFirst)
                    isFirst = false;
                else
                    cout << "--------------------------------------------------------------" << endl;

                originString = ("From " + flight.origin +" to: ");
                originPrinted = true;
            }
            else
                originString = "";
            cout << left << setw(25) << originString << flight;
        }
    }
}

// methods below this point are added new to project 4


// Check whether a city is in the cities that EastWest airline serves.
// Pre-condition: cityNumber to be checked is provided
// Post-condition: return true if the city is in the cities array
//              otherwise return false
bool FlightMapClass::CheckCity(string cityName) const
{ return binary_search(cities.begin(), cities.end(), cityName); }


// Displays all of the cities
void FlightMapClass::DisplayAllCities() const
{
    for (int i = 0; i < size; ++i)
        cout << cities[i] << endl;
}


// Marks a city as visited
// Pre-condition: city to be marked as visited is provided
// Post-condition: a city is marked as visited
void FlightMapClass::MarkVisited(int city)
{ visited[city] = true; }


// Clears marks on all cities
// Pre-condition: there are > 0 cities in a cities array
// Post-condition: all cities marked as unvisited
void FlightMapClass::UnvisitAll()
{
    for (int i = 0 ; i < size; ++i)
    {
        if (visited[i])
            visited[i] = false;
    }
}


// Determines whether a city was visited
// Pre-condition: city is provided
// Post-condition: return true if city has been visited
//              otherwise return false
bool FlightMapClass::IsVisited(int city) const
{ return visited[city]; }


// Determines the next unvisited city, if any,
// that is adjacent to a given city.
// success indicates whether an unvisited adjacent city was found
// Pre-condition: topCity and nextCity provided
// Post-condition: return true if an unvisited adjacent city was found
//              otherwise return false
bool FlightMapClass::GetNextCity(string fromCity, string &nextCity)
{
    int fromIndex = GetCityNumber(fromCity);
    int nextIndex;

    for (flightRec &flight : map[fromIndex])
    {
        nextIndex = GetCityNumber(flight.destination);

        if (!visited[nextIndex])
        {
            nextCity = flight.destination;
            return true;
        }
    }

    return false;
}


// returns the integer index corresponding to a city name
// Pre-condition: name of a city is provided
// Post-condition: returns the index number corresponding to a city name
int FlightMapClass::GetCityNumber(string cityName) const
{
    for (int i = 0; i < size; ++i)
    {
        if (cities[i] == cityName)
            return i;
    }

    return -1;
}


// returns the name of a city given its corresponding index
// Pre-condition: number of a city is provided
// Post-condition: returns the city's name
string FlightMapClass::GetCityName(int cityNumber) const
{ return cities[cityNumber]; }


// Unmark visited city
// Pre-condition:  none
// Post-condition: the specified city is set to not visited
void FlightMapClass::UnmarkVisited(const int city)
{ visited[city] = false; }


void FlightMapClass::GetPaths(int orig, int des)
{
    vector<pathStruct> paths; // Store all found paths
    int pIndex = 0;
    UnvisitAll();
    MarkVisited(orig);

    paths.push_back({vector<flightRec>(), 0});

    // Start DFS with the currentPath
    dfs(orig, des, pIndex, paths);

    if (paths.size() - 1 == 0)
    {
		cout << endl << endl << "Sorry, there is no flight path from " << GetCityName(orig) << " to " << GetCityName(des) << "." << endl << endl;
		cout << "##############################################################" << endl;
        return;
    }
    else if (paths.size() - 1 == 1)
        cout<< endl << endl <<"The flight itinerary is:" << endl << endl;
    else
    {
        cout << endl << endl << "There are " << paths.size() - 1 << " flight paths from " << GetCityName(orig) << " to " << GetCityName(des) << "."
             << endl << "All available flight paths are below sorted in \nascending order of total price:" << endl << endl;
    }

    for (int i = 0; i < paths.size(); ++i)
    {
        for (flightRec &f : paths[i].flights)
            paths[i].total += f.price;
    }

    // Sort all pathStructs in the vector by their totals in ascending order
    sort (paths.begin(), paths.end(), [](const pathStruct &cur, const pathStruct &next)
    { return cur.total < next.total; });

    // Output all the found paths
    for (int i = 1; i < paths.size(); ++i)
    {
        DisplayHeader();
        for (flightRec &f : paths[i].flights)
            cout << left << setw(25) << ("From " + f.origin +" to: ") << f;
        cout << endl << right << setw(56) << "Total: $" << paths[i].total << endl
         << "--------------------------------------------------------------" << endl;
    }

    cout << "##############################################################" << endl;

}

void FlightMapClass::dfs(int origin, int destination, int &pIndex, vector<pathStruct> &paths)
{
    if (origin == destination)
    {
        // Copy the current path to paths only if the destination is reached
        paths.push_back(paths[pIndex]);
        ++pIndex;
        return;
    }

    for (const flightRec &f : map[origin])
    {
        int nextCity = GetCityNumber(f.destination);
        if (!IsVisited(nextCity))
        {
            MarkVisited(nextCity);
            paths[pIndex].flights.push_back(f);

            dfs(nextCity, destination, pIndex, paths);

            paths[pIndex].flights.pop_back();
            UnmarkVisited(nextCity);
        }
    }
}