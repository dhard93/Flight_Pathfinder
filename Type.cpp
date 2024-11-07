// This file contains function definitions for the flightRec struct declared in type.h

#include <iomanip>
#include <string>
#include <ostream>
#include <iomanip>
#include "Type.h"

// Description:     Test to see if the calling flightRec object and parameter flightRec have equivalent
//                  origin and destination. If so, return true, else return false.
// Expected Input:  a flightRec reference object is passed in to test for equivalence.
// Expected Output: return true if the 2 objects have equivalent origin and destination, else return false.
bool flightRec::operator == (const flightRec & rhs) const
{ return origin == rhs.origin && destination == rhs.destination; }


// Description:     Compare the calling flightRec object's destination with the parameter flightRec's destination.
//                  If calling object's destination comes before the object's destination alphabetically, return true.
//                  Else return false.
// Expected Input:  a flightRec reference object is passed in to compare destinations with the calling object.
// Expected Output: Returns true if the calling object's destination comes alphabetically before the parameter object's destination and
//                  false otherwise
bool flightRec::operator < (const flightRec &rhs) const
{ return destination < rhs.destination; }



// Description:     Output the destination, flight number and price of the parameter flightRec to the parameter ostream.
// Expected Input:  Output stream and flightRec
// Expected Output: Return the updated output stream.
ostream& operator << (ostream & os, const flightRec & f)
{
    // From ORIGIN to: output each destination for each origin
    os << left << setw(20) << f.destination
       << setw(10) << f.flightNum <<setw(7) << ("$" + to_string(f.price)) << endl;
    return os;
}