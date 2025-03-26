#include "Data.h"



Data::Data() : graph(Graph<Location>()) {}

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
        Location loc = Location(location, code, std::stoi(id), parking);
        graph.addVertex(loc, parking);
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
        std::string loc1, loc2, drivingStr, walkingStr;

        std::getline(ss, loc1, ',');
        std::getline(ss, loc2, ',');
        std::getline(ss, drivingStr, ',');
        std::getline(ss, walkingStr, ',');


        int driving = std::stoi(drivingStr);
        int walking = std::stoi(walkingStr);
        Location loc1Obj = Location(loc1, "", 0, false);
        Location loc2Obj = Location(loc2, "", 0, false);
        graph.addBidirectionalEdge(loc1Obj, loc2Obj, driving, walking);
    }

    file.close();
}




