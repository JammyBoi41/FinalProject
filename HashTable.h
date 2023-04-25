#include "Flight.h"
#include <list>
#include <fstream>
#include <sstream>

class HashTable {

    private:

    vector<list<Flight>> table; // vector of lists of Flights, each list with a common origin

    int maxSize = 1000; // max size of the hash table

    float maxLoadFactor = 0.7; // max load factor before resizing

    float currentLoadFactor = float(table.size()) / float(maxSize);

    vector<string> weekdays = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    int hashFunction(string key) { // custom hash function to determine index
    
        int hashVal = 0;

        for (char c : key) {

            hashVal += c;

        }

        return hashVal % maxSize;

    }

    public:

    HashTable() {

        table.resize(maxSize);

    }

    void insert(Flight& f) {

        int index = hashFunction(f.origin);

        table[index].push_back(f);

        if (currentLoadFactor > maxLoadFactor) {
            // if load factor is too high, double table size

            maxSize *= 2;

            table.resize(maxSize);

        }

    }

    int numOfFlights(string origin, string destination, int day) {
        // finds number of flights for a certain flight path on a certain day

        int count = 0;

        int index = hashFunction(origin);

        for (Flight& f : table[index]) {

            if (f.origin == origin && f.destination == destination && f.day == day) {

                count++;

            }

        }

        return count;

    }

    float findAvgDelay(string origin, string destination, int day) {
        // finds average delay time for a certain flight path on a certain day

        if (numOfFlights(origin, destination, day) < 1) {

            return -1;

        }

        int time = 0;

        int count = 0;

        int index = hashFunction(origin);

        for (Flight& f : table[index]) {

            if (f.origin == origin && f.destination == destination && f.day == day && f.delayed == 1) {

                time += f.delayDuration;

                count++;

            }

        }

        return float(time) / float(count);

    }

    int findDelays(string origin, string destination, int day) {
        // finds number of flight delays for a certain flight path on a certain day

        if (numOfFlights(origin, destination, day) < 1) {

            return -1;

        }

        int count = 0;

        int index = hashFunction(origin);

        for (Flight& f : table[index]) {

            if (f.origin == origin && f.destination == destination && f.day == day && f.delayed == 1) {

                count++;

            }

        }

        return count;

    }

    void printAvgDelay(string origin, string destination, int day) {

        float avgDelay = findAvgDelay(origin, destination, day);

        if (avgDelay == -1) {

            cout << "A flight from " << origin << " to " << destination << " does not exist" << endl;

        } 
        
        else {

            cout << "Flights from " << origin << " to " << destination << " on " << weekdays.at(day - 1) 
            << " have an average flight delay of " << avgDelay << " minutes" << endl;
            
        }

    }

    void printDelays(string origin, string destination, int day) {

        int delays = findDelays(origin, destination, day);

        if (delays == -1) {

            cout << "A flight from " << origin << " to " << destination << " does not exist" << endl;

        } 
        
        else {

            cout << "Flights from " << origin << " to " << destination << " on " << weekdays.at(day - 1) 
            << " were delayed " << delays << " out of " << numOfFlights(origin, destination, day) << " times" << endl;
            
        }

    }

    void clearHashTable() {

        table.clear();

    }

};
