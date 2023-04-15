#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

class Flight {

    public:

    int id;
    int departTime;
    int flightDuration;
    string airline;
    string origin;
    string destination;
    int day;
    int delayed;
    int delayDuration;

    Flight( 
        int idTemp, 
        int departTimeTemp, 
        int flightDurationTemp, 
        string airlineTemp, 
        string originTemp, 
        string destinationTemp, 
        int dayTemp, 
        int delayedTemp, 
        int delayDurationTemp
        ) {
            // constructor

        this->id = idTemp;
        this->departTime = departTimeTemp;
        this->flightDuration = flightDurationTemp;
        this->airline = airlineTemp;
        this->origin = originTemp;
        this->destination = destinationTemp;
        this->day = dayTemp;
        this->delayed = delayedTemp;
        this->delayDuration = delayDurationTemp;

    }

};