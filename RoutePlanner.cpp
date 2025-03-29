//
// Created by anacastanheiros on 3/25/25.
//


#include "RoutePlanner.h"

#include <climits>

RoutePlanner::RoutePlanner() {
}

// Dijkstra function
std::vector<int> RoutePlanner::dijkstra(Graph<Location> g, int sourceId, int targetId, std::unordered_map<int, Vertex<Location> *> locations, bool isDriving=true) {

    const int inf = std::numeric_limits<int>::max();

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;

    for (auto v : g.getVertexSet()) {
        dist[v->getInfo().getId()] = inf;
        prev[v->getInfo().getId()] = -1;
        v->setDist(INF);
    }

    Vertex<Location> * src = locations[sourceId];
    if (!src) return {};
    src->setDist(0);

    MutablePriorityQueue<Vertex<Location>> pq;
    pq.insert(src);

    while (!pq.empty()) {
        auto u = pq.extractMin();

        for (auto e : u->getAdj()) {
            if (!e->isSelected()) {
                int w = e->getWeight(isDriving);
                //cout << w << endl;
                if (w == -1) continue; // skip inaccessible edges

                Vertex<Location>* v = e->getDest();
                int alt = u->getDist() + w;

                if (alt < v->getDist() && !v->isVisited()) {
                    v->setDist(alt);
                    prev[v->getInfo().getId()] = u->getInfo().getId();

                    pq.insert(v);
                }
            }
        }
    }

    std::vector<int> path;
    Vertex<Location>* end = locations[targetId];
    if (!end || end->getDist() == inf) return path; // no path found

    for (int at = targetId; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

pair<vector<int>,vector<int>> RoutePlanner::execIndependentRoutePlanning(Data data, int source, int target) {
    Graph<Location> g = data.get_graph();


    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    auto bestPath = dijkstra(g,source,target,data.get_locations_by_id());

    for (int i = 1; i < bestPath.size() - 1; i++) {
        auto vertex = data.get_locations_by_id()[bestPath[i]];
        if (vertex != nullptr) {
            vertex->setVisited(true);
        }
    }

    auto secondBestPath = dijkstra(g,source,target,data.get_locations_by_id());

    return  {bestPath,secondBestPath};
}

vector<int> RoutePlanner::execRestrictedRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int includeNode) {
    Graph<Location> g = data.get_graph();

    // Reset all visited flags
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }

    // Apply avoidNodes (if any)
    for (int avoidNode : avoidNodes) {
        auto v = data.get_locations_by_id()[avoidNode];
        if (v) v->setVisited(true);
    }

    // Apply avoidEdges (if any)
    for (auto avoidEdge : avoidEdges) {
        auto src = data.get_locations_by_id()[avoidEdge.first];
        auto dest = data.get_locations_by_id()[avoidEdge.second];
        auto srcVertex = g.findVertex(src->getInfo());
        auto destVertex = g.findVertex(dest->getInfo());

        if (srcVertex && destVertex) {
            for (auto e : srcVertex->getAdj()) {
                if (e->getDest() == destVertex) {
                    e->setSelected(true);
                }
            }
        }
    }

    // --- If includeNode is not used (-1), run regular Dijkstra ---
    if (includeNode == -1 || includeNode == source || includeNode == target) {
        return dijkstra(g, source, target, data.get_locations_by_id());
    }

    // --- Otherwise, run in two parts ---
    auto path1 = dijkstra(g, source, includeNode, data.get_locations_by_id());
    if (path1.empty()) return {};


    auto path2 = dijkstra(g, includeNode, target, data.get_locations_by_id());
    if (path2.empty()) return {};

    path1.pop_back();
    path1.insert(path1.end(), path2.begin(), path2.end());


    return path1;

}

int RoutePlanner::dijkstraFriendly(Graph<Location> g, int sourceId, int targetId, std::unordered_map<int, Vertex<Location> *> locations, bool isDriving=true) {

    const int inf = std::numeric_limits<int>::max();

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;

    for (auto v : g.getVertexSet()) {
        dist[v->getInfo().getId()] = inf;
        prev[v->getInfo().getId()] = -1;
        v->setDist(INF);
    }

    Vertex<Location> * src = locations[sourceId];
    if (!src) return {};
    src->setDist(0);

    MutablePriorityQueue<Vertex<Location>> pq;
    pq.insert(src);

    while (!pq.empty()) {
        auto u = pq.extractMin();

        for (auto e : u->getAdj()) {
            if (!e->isSelected()) {
                int w = e->getWeight(isDriving);
                //cout << w << endl;
                if (w == -1) continue; // skip inaccessible edges

                Vertex<Location>* v = e->getDest();
                int alt = u->getDist() + w;

                if (alt < v->getDist() && !v->isVisited()) {
                    v->setDist(alt);
                    prev[v->getInfo().getId()] = u->getInfo().getId();

                    pq.insert(v);
                }
            }
        }
    }

    std::vector<int> path;
    Vertex<Location>* end = locations[targetId];
    if (!end || end->getDist() == inf) return path; // no path found

    for (int at = targetId; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    return path;
}


pair<vector<int>, int> RoutePlanner::execEnvironmentallyFriendlyRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int maxWalkTime) {
    Graph<Location> g = data.get_graph();

   //criar dois sets um dos parkings possiveis atraves do source e outro dos destinations 

    // Reset all visited flags
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }

    //Todos os parking nodes
    std::unordered_map<int, Vertex<Location>*> parkingNodesMap;
    for (auto &location : data.get_locations_by_id()) {
        if (location.second->getParking()) {
            parkingNodesMap[location.first] = location.second;
        }
    }

    // Apply avoidNodes (if any)
    for (int avoidNode : avoidNodes) {
        auto v = data.get_locations_by_id()[avoidNode];
        if (v) v->setVisited(true);
    }

    // Apply avoidEdges (if any)
    for (auto avoidEdge : avoidEdges) {
        auto src = data.get_locations_by_id()[avoidEdge.first];
        auto dest = data.get_locations_by_id()[avoidEdge.second];
        auto srcVertex = g.findVertex(src->getInfo());
        auto destVertex = g.findVertex(dest->getInfo());

        if (srcVertex && destVertex) {
            for (auto e : srcVertex->getAdj()) {
                if (e->getDest() == destVertex) {
                    e->setSelected(true);
                }
            }
        }
    }

    findFirstParking(data, g, target, parkingNodesMap);
    findFirstParking(data, g, source, parkingNodesMap);

    // int bestTotalTime = INT_MAX;
    // int bestWalkingTime = -1;
    // std::vector<int> bestDrivingRoute;
    // std::vector<int> bestWalkingRoute;
    // int bestParkingNode = -1;

    // for (auto& parkingNodes : parkingNodesMap) {
    //     int parkingNode = parkingNodes.first;

    //     // Skip invalid parking nodes (e.g., source or destination, or nodes in avoid list)
    //     if (parkingNode == source || parkingNode == target ||
    //         std::find(avoidNodes.begin(), avoidNodes.end(), parkingNode) != avoidNodes.end()) {
    //         continue;
    //         }

    //     // 1. Run Dijkstra (walking) from parkingNode to target
    //     auto walkingRoute = dijkstra(g, parkingNode, target, data.get_locations_by_id(), false);

    //     //3. Check conditions

    //     //if (walkingTime == -1) continue;  // No valid walking route

    //     // 3. Check if this route meets the walking time constraint
    //     //if (walkingTime > maxWalkTime) continue;  // Skip if walking time exceeds the maximum limit

    //     // 2. Run Dijkstra (driving) from source to parkingNode
    //     auto drivingRoute = dijkstra(g, source, parkingNode, data.get_locations_by_id());

    //     //if (drivingTime == -1) continue;  // No valid driving route



        // // 4. Calculate total time (driving + walking)
        // int totalTime = drivingTime + walkingTime;

        // // 5. If this route is better, update the best route
        // if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingTime > bestWalkingTime)) {
        //     bestTotalTime = totalTime;
        //     bestWalkingTime = walkingTime;
        //     bestDrivingRoute = drivingRoute;
        //     bestWalkingRoute = walkingRoute;
        //     bestParkingNode = parkingNode;
        //}

}


vector<int> findFirstParking(Data data, Graph<Location> g, int vertexID, unordered_map<int, Vertex<Location>*> parkingNodesMap){
    vector<int> v();
    for (auto &parking: parkingNodesMap){
        v.push_back(dijkstraFriendly(g, vertexID, parking, data.get_locations_by_id()));
        
    }

}
