#include "Data.h"



Data::Data() : graph(Graph<Location>()) {
    loadLocations(LOCATIONS);
    loadDistances(DISTANCES);
}

void Data::loadLocations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string location, id, code, parkingstr;

        std::getline(ss, location, ',');
        std::getline(ss, id, ',');
        std::getline(ss, code, ',');
        std::getline(ss, parkingstr, ',');

        parkingstr.erase(parkingstr.find_last_not_of(" \r") + 1); //It searches from the end of the string to find the last character that is not a space or carriage return (\r).

        bool parking = (parkingstr == "1");
        const Location &loc = Location(location, code, std::stoi(id), parking);
        graph.addVertex(loc, parking);
        Vertex<Location> * newLoc = graph.findVertex(loc);
        locations_by_id[loc.getId()] = newLoc;
        location_by_code[loc.getCode()] = newLoc;
    }

    file.close();
}

void Data::loadDistances(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string code1, code2, drivingStr, walkingStr;

        std::getline(ss, code1, ',');
        std::getline(ss, code2, ',');
        std::getline(ss, drivingStr, ',');
        std::getline(ss, walkingStr, ',');

        auto loc1 = location_by_code[code1];
        auto loc2 = location_by_code[code2];

        if (drivingStr == "X") {
            drivingStr = "-1";
        }
        if (!graph.addEdge(loc1->getInfo(), loc2->getInfo(), stoi(drivingStr), stoi(walkingStr))){
            std::cerr << "Failed to add edge\n";
            return;
        }
        if (!graph.addEdge(loc2->getInfo(), loc1->getInfo(), stoi(drivingStr), stoi(walkingStr))) {
            std::cerr << "Failed to add edge\n";
            return;
        }


    }

    file.close();
}

Graph<Location> Data::get_graph(){
    return this->graph;
}