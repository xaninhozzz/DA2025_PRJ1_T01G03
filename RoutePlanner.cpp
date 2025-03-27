//
// Created by anacastanheiros on 3/25/25.
//


#include "RoutePlanner.h"

RoutePlanner::RoutePlanner() {

}

// Dikstra function
std::vector<int> RoutePlanner::dijkstra(Graph<Location>* g, int sourceId, int targetId,std::unordered_map<int,Vertex<Location> *> locations, bool isDriving) {

    const int inf = std::numeric_limits<int>::max();

    std::unordered_map<int, int> dist;
    std::unordered_map<int, int> prev;

    for (auto v : g->getVertexSet()) {
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
            int w = e->getWeight(isDriving);
            if (w == -1) continue; // skip inaccessible edges

            Vertex<Location>* v = e->getDest();
            int alt = u->getDist() + w;

            if (alt < v->getDist()) {
                v->setDist(alt);
                prev[v->getInfo().getId()] = u->getInfo().getId();

                pq.insert(v);
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