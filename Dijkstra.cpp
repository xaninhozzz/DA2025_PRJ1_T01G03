#include "Dijkstra.h"
#include "MutablePriorityQueue.h"
#include "Graph.h"
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <set>
#include <functional>

template <class T>
void dijkstra(Graph<T>* g, const T& origin, const T& destination, const std::string& mode,
              const std::set<T>& avoidNodes, const std::set<std::pair<T, T>>& avoidEdges) {

    const int inf = std::numeric_limits<int>::max(); // Define the infinity value
    std::unordered_map<T, int> dist;  // Stores the shortest distance from the origin
    std::unordered_map<T, T> prev;  // Stores the previous node for path reconstruction

    // Initialize distances
    for (auto v : g->getVertexSet()) {
        dist[v] = inf;
        prev[v] = T();  // Initialize previous node as a default value
    }
    dist[origin] = 0;  // Set the distance for the origin to 0

    // Priority queue for Dijkstra (min-heap)
    MutablePriorityQueue<T> pq;
    pq.insert(&origin);  // Insert the origin node with priority 0

    while (!pq.empty()) {
        T current = pq.extractMin();  // Get the node with the smallest distance

        // Skip nodes that have already been visited or are in the avoid list
        if (avoidNodes.find(current) != avoidNodes.end()) {
            continue;
        }

        // If we reach the destination, stop early
        if (current == destination) {
            break;
        }

        // Explore the adjacent vertices (edges)
        for (Edge<T>* edge : g->getEdges(current)) {
            // Skip edges that have already been visited or are in the avoid list
            if (avoidEdges.find({current, edge->getDest()}) != avoidEdges.end()) {
                continue;
            }

            // Get the weight based on the current mode (driving or walking)
            double weight = edge->getWeight(mode);  // Use the getWeight method

            // Relaxation step: update the distance if a shorter path is found
            if (dist[current] + weight < dist[edge->getDest()]) {
                dist[edge->getDest()] = dist[current] + weight;
                prev[edge->getDest()] = current;
                pq.decreaseKey(edge->getDest());  // Update priority in the queue
            }
        }

        // Switch to walking mode when reaching a parking location
        if (g->getVertex(current)->getParking() && mode == "driving") {
            mode = "walking";  // Change mode to walking after parking
        }
    }

    // If we need to do something with the results (like reconstruct the path)
    if (dist[destination] != inf) {
        T current = destination;
        std::vector<T> path;
        while (current != origin) {
            path.push_back(current);
            current = prev[current];
        }
        path.push_back(origin);
        std::reverse(path.begin(), path.end());

        // Here, you can return the path or process it as needed
        // For example: return path;
    }
}
