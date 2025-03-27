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
<<<<<<< HEAD
        pair<vector<int>,vector<int> > execIndependentRoutePlanning(Data data,int source, int target);
=======
        pair<vector<int>,vector<int>> execIndependentRoutePlanning(Data data,int source, int target);
        vector<int> execRestrictedRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int includeNode);

>>>>>>> f3910fb8968e7120d9daf47e6fdd0807569701c9
};


#endif //ROUTEPLANNER_H
