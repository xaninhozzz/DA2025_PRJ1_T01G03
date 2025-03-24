// #include "Menu.h"
// #include "Graph.h"
// #include "Data.h"

// int main() {
//     Menu menu;
//     menu.modeChoice();
//     Graph<std::string> graph;
//     Data data(graph);

//     data.loadLocations("Locations.csv");
//     data.loadDistances("Distances.csv");
//     //menu.getUserModeSourceDestination();
//     return 0;
// }

#include "Graph.h"
#include "Data.h"
#include "Locations.h"

int main() {
    Graph<std::string> graph;
    Data data(graph);

    if (!data.loadLocations("Data/Locations.csv")) {
        std::cerr << "Failed to load locations.\n";
        return 1;
    }

    if (!data.loadDistances("Data/Distances.csv")) {
        std::cerr << "Failed to load distances.\n";
        return 1;
    }

    std::cout << "Vertices loaded: " << graph.getNumVertex() << std::endl;
    for (auto v : graph.getVertexSet()) {
        std::cout << "Location Code: " << v->getInfo() << std::endl;
        std::cout << "Has Parking: " << (v->getParking() ? "Yes" : "No") << std::endl;
        std::cout << "Connections:\n";
        for (auto e : v->getAdj()) {
            std::cout << "  → " << e->getDest()->getInfo()
                      << " [Drive: " << e->getDriving()
                      << "]" << std::endl;
            std::cout << "  → " << e->getDest()->getInfo()
                      << " [Walk: " << e->getWalking()
                      << "]" << std::endl;
        }
        std::cout << "------------------------\n";
    }

    return 0;
}

