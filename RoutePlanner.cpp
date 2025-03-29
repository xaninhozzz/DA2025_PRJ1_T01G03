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

//Salvo aqui caso dê molho

// unordered_map<int, Vertex<Location>*> RoutePlanner::findFirstParking(Data data, Graph<Location> g, int vertexID, unordered_map<int, Vertex<Location>*> parkingNodesMap, bool isDriving) {
//     // Vector to store reachable parking nodes from the source (vertexID)
//     unordered_map<int, Vertex<Location>*> reachableParkingNodes;
//
//     // Step 1: Run Dijkstra to find the first reachable parking nodes from the source
//     auto parkingFromSource = dijkstra(g, vertexID, -1, data.get_locations_by_id(), isDriving);
//
//     for (auto &node : parkingNodesMap) {
//         // Check if the parking node is in the shortest path
//         if (find(parkingFromSource.begin(), parkingFromSource.end(), node.first) != parkingFromSource.end()) {
//             reachableParkingNodes[node.first] = node.second;  // Insert into map (node.first = parking node id, node.second = vertex)
//         }
//     }
//     // Step 2: Now that we have the reachable parking nodes, return the first one(s)
//     return reachableParkingNodes;
// }

unordered_map<int, Vertex<Location>*> RoutePlanner::findFirstParking(Data data, Graph<Location> g, int vertexID, unordered_map<int, Vertex<Location>*> parkingNodesMap, bool isDriving, int maxWalkTime) {
    // Map to store reachable parking nodes from the source (vertexID)
    unordered_map<int, Vertex<Location>*> reachableParkingNodes;

    // Step 1: Run Dijkstra to find the first reachable parking nodes from the source
    auto parkingFromSource = dijkstra(g, vertexID, -1, data.get_locations_by_id(), isDriving);  // Pass isDriving to decide walking or driving

    for (auto &node : parkingNodesMap) {
        // Check if the parking node is in the shortest path
        if (find(parkingFromSource.begin(), parkingFromSource.end(), node.first) != parkingFromSource.end()) {
            // If the mode is walking, check the walk time on the edges leading to the parking node
            if (!isDriving) {
                int totalWalkTime = 0;
                Vertex<Location>* currentVertex = data.get_locations_by_id()[vertexID];

                // Traverse the path to calculate the total walk time to this parking node
                while (currentVertex != node.second) {
                    for (auto edge : currentVertex->getAdj()) {
                        if (edge->getDest() == node.second) {
                            totalWalkTime += edge->getWeight(false);  // Use the weight for walking time (false means walking)
                            break;
                        }
                    }
                    currentVertex = currentVertex->getAdj()[0]->getDest();  // Move to the next vertex in the path
                }

                // Add the parking node if the total walking time is within the limit
                if (totalWalkTime <= maxWalkTime) {
                    reachableParkingNodes[node.first] = node.second;  // Insert into map (node.first = parking node id, node.second = vertex)
                }
            } else {
                // If the mode is driving, add the node without checking walk time
                reachableParkingNodes[node.first] = node.second;
            }
        }
    }

    // Return the reachable parking nodes
    return reachableParkingNodes;
}


vector<int> RoutePlanner::execEnvironmentallyFriendlyRoutePlanning(Data data, int source, int target, const std::vector<int>& avoidNodes, const std::vector<std::pair<int, int>>& avoidEdges, int maxWalkTime) {
    // era pair<vector<int>, int>
    Graph<Location> g = data.get_graph();
    // pair<vector<int>, int> p;
    vector<int> v;

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

    unordered_map<int, Vertex<Location>*> targetParkingNodes = findFirstParking(data, g, target, parkingNodesMap, false, maxWalkTime);
    unordered_map<int, Vertex<Location>*> sourceParkingNodes = findFirstParking(data, g, source, parkingNodesMap, true, maxWalkTime);

    // Step 3: Find the intersection of parking nodes from the source and target
    unordered_map<int, Vertex<Location>*> commonParkingNodes;
    for (auto &node : sourceParkingNodes) {
        // If the node is also in the targetParkingNodes map, add it to commonParkingNodes
        if (targetParkingNodes.find(node.first) != targetParkingNodes.end()) {
            commonParkingNodes[node.first] = node.second;
        }
    }
    
    for (auto &node : commonParkingNodes){
        auto path = execRestrictedRoutePlanning(data, source, target, 
            avoidNodes, avoidEdges, node.first);
    }

}