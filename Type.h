#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#ifndef Type_H
#define Type_H

// flightRec struct
struct flightRec{
	string origin;		// flight origin city
	int flightNum;		// flight number
	string destination;	// flight destination city
	int price;			// flight price

	bool operator < (const flightRec & rhs) const;
	//overloaded < operator for flightRec
	//this function compares the destinations between two flightRec

	bool operator == (const flightRec & rhs) const;
	//overloaded == operator for flightRec
	//this function compares the origins and destinations between two flightRec

	friend ostream& operator << (ostream & os, const flightRec & f);
	//overloaded output operator for flightRec struct
};

// pathStruct struct
struct pathStruct{
	vector<flightRec> flights;	// Stores the flightRecs for all flights in flight path
	int total;					// Total price of the flight path
};

// flightRequest struct
struct flightRequest{
	string origin;				// origin city requested
	string destination;			// destination city requested
};

#endif