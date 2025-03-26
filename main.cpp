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
            /*
            *for (auto d = 0; d < 10 ; d++) {
            auto v = graph.getVertexSet()[d];
            std::cout << "Location Code: " << v->getInfo() << std::endl;
            std::cout << "Has Parking: " << (v->getParking() ? "Yes" : "No") << std::endl;
            std::cout << "Connections:\n";
            for (auto e : v->getAdj()) {
            std::cout << "  → " << e->getDest()->getInfo()
            << " [Drive: " << e->getWeight()
            << "]" << std::endl;
            std::cout << "  → " << e->getDest()->getInfo()
            << " [Walk: " << e->getWeight(false)
            << "]" << std::endl;
            }
            std::cout << "------------------------\n";
            }
            */
// }

#include "Graph.h"
#include "Data.h"
#include "Menu.h"

int main() {
    Menu menu = Menu();
    return 0;
}

