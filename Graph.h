#ifndef GRAPH_CITY
#define GRAPH_CITY


#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

/*********************************** Edges == paths ************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // Destination vertex
    double drivingTime;    // Driving time in minutes
    double walkingTime;    // Walking time in minutes
public:
    Edge(Vertex<T> *d, double driveTime, double walkTime);

    Vertex<T> *getDest() const;
    double getDrivingTime() const;
    double getWalkingTime() const;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double driveTime, double walkTime)
    : dest(d), drivingTime(driveTime), walkingTime(walkTime) {}

template <class T>
Vertex<T> *Edge<T>::getDest() const { return dest; }

template <class T>
double Edge<T>::getDrivingTime() const { return drivingTime; }

template <class T>
double Edge<T>::getWalkingTime() const { return walkingTime; }


/*********************************** Vertex == Locais ************************/

template <class T>
class Vertex {
    T info;
    vector<Edge<T> > adj;  // List of outgoing edges
    bool visited;
    bool processing;        // auxiliar
    bool hasParking;       // Indicates if this location has parking

public:
    Vertex(T in, bool parking);
    void addEdge(Vertex<T> *dest, double driveTime, double walkTime);
    bool getParking() const;
};

template <class T>
Vertex<T>::Vertex(T in, bool parking) : info(in), hasParking(parking) {}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double driveTime, double walkTime) {
    adj.push_back(Edge<T>(dest, driveTime, walkTime));
}

template <class T>
bool Vertex<T>::getParking() const { return hasParking; }


/*********************************** Construção do grafo ************************/

template <class T>
class Graph {
    unordered_map<T, Vertex<T> *> vertexSet; // Map of nodes
public:
    bool addVertex(const T &in, bool hasParking);
    bool addEdge(const T &source, const T &dest, double driveTime, double walkTime);
    void loadGraphFromCSV(const string &locationsFile, const string &distancesFile);
};

template <class T>
bool Graph<T>::addVertex(const T &in, bool hasParking) {
    if (vertexSet.find(in) != vertexSet.end())
        return false;
    vertexSet[in] = new Vertex<T>(in, hasParking);
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double driveTime, double walkTime) {
    auto v1 = vertexSet[source];
    auto v2 = vertexSet[dest];
    if (!v1 || !v2)
        return false;
    v1->addEdge(v2, driveTime, walkTime);
    v2->addEdge(v1, driveTime, walkTime); // Since roads are bidirectional
    return true;
}


#endif // GRAPH_CITY