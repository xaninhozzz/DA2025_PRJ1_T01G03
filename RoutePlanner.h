//
// Created by anacastanheiros on 3/25/25.
//

#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H
#include "Graph.h"
#include "MutablePriorityQueue.h"
#include "Location.h"
#include <vector>
#include <functional>
#include <unordered_map>
#include <limits>
#include <algorithm>

#include "Data.h"

using namespace std;
class RoutePlanner {
    public:
        RoutePlanner();
        std::vector<int> dijkstra(Graph<Location> g, int source, int target, std::unordered_map<int,Vertex<Location> *> locations,bool isDriving);
        pair<vector<int>,vector<int> > execIndependentRoutePlanning(Data data,int source, int target);
};


#endif //ROUTEPLANNER_H
