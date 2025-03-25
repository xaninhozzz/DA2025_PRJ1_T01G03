//
// Created by anacastanheiros on 3/25/25.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <functional>

/**
 * Runs Dijkstra's algorithm on the given graph to find the shortest path
 * from source to target, using a custom weight selector for each edge.
 *
 * @param g Pointer to the graph.
 * @param source ID of the source node.
 * @param target ID of the target node.
 * @param getWeight Function to extract the desired weight (e.g., driving or walking) from an edge.
 * @return Vector of node IDs representing the path from source to target. Empty if no path exists.
 */
std::vector<int> dijkstra(Graph<int>* g, int source, int target,
                          std::function<int(Edge<int>*)> getWeight);

#endif //DIJKSTRA_H
