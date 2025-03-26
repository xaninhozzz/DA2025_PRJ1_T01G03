#ifndef DATA_H
#define DATA_H


#define LOCATIONS "../Data/Locations.csv"
#define DISTANCES "../Data/Distances.csv"
#include "Graph.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Location.h"
using namespace std;

class Data {
    public:
        Data();
        void loadLocations(const string& filename);
        void loadDistances(const string& filename);
        Graph<Location> get_graph();
    private:
        Graph<Location> graph;
        unordered_map<int, Vertex<Location>*> locations_by_id;
        unordered_map<string, Vertex<Location>*> location_by_code;
};

#endif // DATA_H
