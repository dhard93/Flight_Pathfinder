/*
	Author:      Phillip Hardeman
	Description: This program reads in city names flight records, and flight requests from their corresponding data files.
				 It constructs an adjacency list consisting of an array of pointers to flightRec lists, where each index
				 corresponds to a city, and each city's list contains all flights coming from that city. Once the adjacency
				 list is constructed, it processes the requests read from the request file using a stack to find paths
				 from the origin to the destination, a deque to reverse the order of the stack values, and a vector
				 of pathStruct structs to store the flights in each path as well as the path's total cost.
				 Once all valid paths have been stored in the pathStruct vector for a request, they are sorted in
				 order of total price and the least expensive option is displayed to the user, if any path exists at all.
				 This is done for each request received.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;
#include "FlightMap.h"

// Constants
const string CITIES = "cities.dat";
const string FLIGHTS = "flights.dat";

// Function Prototype Declarations
void retrieveFlightData(ifstream &inStream, FlightMapClass &fMap, const string &filename);
const int validateCities(const FlightMapClass &fMap, flightRequest &fReq);

int main()
{
	FlightMapClass flightMap;		// flightMap containing cities vector and flightRec adjacency list
	ifstream myIn;					// input stream

	// Open cities file, read cities into the flightMap and close input file.
	retrieveFlightData(myIn, flightMap, CITIES);

	// Open flights file, read flight data into the flightMap, and close input file.
	retrieveFlightData(myIn, flightMap, FLIGHTS);

	// Prompt user to enter origin and destination cities and find all paths between the two cities.
	string o, d;
	cout << "Origin: ";
	cin >> o;
	cout << "Destination: ";
	cin >> d;

	flightMap.GetPaths(flightMap.GetCityNumber(o), flightMap.GetCityNumber(d));

	return 0;
}


// Read data from input file stream into flightMap based on the code passed in and
// then close input file stream.
// Pre-condition:  Input file stream and flightMap have been declared.
// Post-condition: flightMap is populated with cities and flights from file.
void retrieveFlightData(ifstream &inStream, FlightMapClass &fMap, const string &filename)
{
	inStream.open(filename);
	assert(inStream);

	if (filename == CITIES)
		fMap.ReadCities(inStream);
	else
		fMap.BuildMap(inStream);

	inStream.close();
}


// Validate that both cities in the given request are served by the airline.
// Pre-condition:  a flightRequests has been received
// Post-condition: the given flightRequests is validated
const int validateCities(const FlightMapClass &fMap, flightRequest &fReq)
{
	if (!fMap.CheckCity(fReq.origin))
	{
		cout << "Sorry, BlueSky airline does not serve " << fReq.origin << "." << endl << endl;
		cout << "##############################################################" << endl << endl;
		return 1;
 	}

	if (!fMap.CheckCity(fReq.destination))
	{
		cout << "Sorry, BlueSky airline does not serve " << fReq.destination << "." << endl << endl;
		cout << "##############################################################" << endl << endl;
		return 2;
	}

	return 0;
}