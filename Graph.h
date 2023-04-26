#ifndef GRAPH_H
#define GRAPH_H

//#include "Flight.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class Graph {
public: //rn public for debugging purposes, change back to private later
    map<string, vector<Flight>> graph;
    void insertEdge(string from, Flight data);
    void averageTime(string from, string to, int day);
    int fractionNumerator(string from, string to, int functionDay);
    int fractionDenominator(string from, string to, int functionDay);
    float averageDelay(string from, string to, int functionDay);
    void clearGraph();

};

void Graph::insertEdge(string from, Flight data) {
    graph[from].push_back(data);
    if(graph.find(data.destination) == graph.end()) {
        graph[data.destination] = {};
    }
}

int Graph::fractionNumerator(string from, string to, int functionDay) {
    int count = 0;
    for(int i = 0; i < graph[from].size(); i++) {
        Flight thing = graph[from].at(i);
        if(thing.destination == to && thing.day == functionDay && thing.delayed == 1) {
            count++;
        }
    }
    return count;
}

int Graph::fractionDenominator(string from, string to, int functionDay) {
    int count = 0;
    for(int i = 0; i < graph[from].size(); i++) { //this works
        Flight thing = graph[from].at(i);
        if(thing.destination == to && thing.day == functionDay) {
            count++;
        }
    }
    return count;
}

float Graph::averageDelay(string from, string to, int functionDay) {
    float sum = 0;
    float numFlights = 0;
    for(int i = 0; i < graph[from].size(); i++) { //this works
        Flight thing = graph[from].at(i);
        if(thing.destination == to && thing.day == functionDay && thing.delayed == 1) {
            numFlights++;
            sum += thing.delayDuration;
        }
    }
    if(numFlights == 0) {
        return 0;
    }
    else {
        return(sum/numFlights);
    }

}

void Graph::clearGraph() {
    graph.clear();
}


#endif // GRAPH_H
