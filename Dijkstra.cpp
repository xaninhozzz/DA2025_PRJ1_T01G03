//
// Created by anacastanheiros on 3/25/25.
//


#include "Dijkstra.h"
#include "MutablePriorityQueue.h"
#include "Graph.h"
#include <unordered_map>
#include <limits>
#include <algorithm>

std::vector<int> dijkstra(Graph<int>* g, int source, int target,
                          std::function<int(Edge<int>*)> getWeight) {

    const int inf = std::numeric_limits<int>::max();

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;

    for (auto v : g->getVertexSet()) {
        dist[v->getInfo()] = inf;
        prev[v->getInfo()] = -1;
        v->setDist(INF);
    }

    Vertex<int>* src = g->findVertex(source);
    if (!src) return {};
    src->setDist(0);

    MutablePriorityQueue<Vertex<int>> pq;
    pq.insert(src);

    while (!pq.empty()) {
        auto u = pq.extractMin();

        for (auto e : u->getAdj()) {
            int w = getWeight(e);
            if (w == -1) continue; // skip inaccessible edges

            Vertex<int>* v = e->getDest();
            int alt = u->getDist() + w;

            if (alt < v->getDist()) {
                v->setDist(alt);
                prev[v->getInfo()] = u->getInfo();

                pq.insert(v);
            }
        }
    }

    std::vector<int> path;
    Vertex<int>* end = g->findVertex(target);
    if (!end || end->getDist() == inf) return path; // no path found

    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
