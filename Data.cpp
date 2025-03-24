#include "Data.h"
#include <fstream>
#include <sstream>
#include <iostream>


Data::Data(Graph<std::string>& graph) : graph(graph) {}

bool Data::loadLocations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return false;
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

        graph.addVertex(code, parking);
    }

    file.close();
    return true;
}

bool Data::loadDistances(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << "\n";
        return false;
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

        if (drivingStr == "X") continue; // skip non-drivable edges

        int driving = std::stoi(drivingStr);
        int walking = std::stoi(walkingStr);

        graph.addEdge(loc1, loc2, driving, walking);
    }

    file.close();
    return true;
}




