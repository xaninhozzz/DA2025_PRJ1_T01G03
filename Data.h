#ifndef DATA_H
#define DATA_H

#include <string>
#include "Graph.h"

class Data {
public:
    explicit Data(Graph<std::string>& graph);

    // Loaders for the CSV files
    bool loadLocations(const std::string& filename);
    bool loadDistances(const std::string& filename);

private:
    Graph<std::string>& graph;

};

#endif // DATA_H
