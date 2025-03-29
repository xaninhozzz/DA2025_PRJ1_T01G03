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
        pair<vector<int>,vector<int>> execIndependentRoutePlanning(Data data,int source, int target);
        vector<int> execRestrictedRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int includeNode);
        vector<int> execEnvironmentallyFriendlyRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int maxWalkTime);
        // unordered_map<int, Vertex<Location>*> findFirstParking(Data data, Graph<Location> g, int vertexID, unordered_map<int, Vertex<Location>*> parkingNodesMap, bool isDriving);
        unordered_map<int, Vertex<Location>*> findFirstParking(Data data, Graph<Location> g, int vertexID, unordered_map<int, Vertex<Location>*> parkingNodesMap, bool isDriving, int maxWalkTime);

};


#endif //ROUTEPLANNER_H
