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

int main() {
    cout << "Hello" << endl;
    Data data = Data();
    auto graph = data.get_graph();
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

