#include "Menu.h"
#include "BatchMode.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "Data.h"

Menu::Menu() {
    data = Data();
    routePlanner = RoutePlanner();
}

int Menu::selectTypeOfMenu() {
    int choice;

    std::cout << "Welcome to our GPS! Please choose your mode:" << std::endl;
    std::cout << "1. Terminal" << std::endl;
    std::cout << "2. Input file" << std::endl;
    std::cout << "0. Exit" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
    }
    return choice;
}

int Menu::run() {
    int option = selectTypeOfMenu();

    while(option != 0){
        switch(option){
            case 1:
                modeChoice();
            break;
            case 2:
                //inputTxtFile();
            break;
            default:
                std::cout << "Invalid option try again" << std::endl;
        }
        option = selectTypeOfMenu();
    }
    return 0;
}

void Menu::modeChoice() {
    int choice;

    std::cout << "1. Driving" << std::endl;
    std::cout << "2. Both" << std::endl;
    std::cout << "0. Back" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        modeChoice();
    }

    switch (choice) {
        case 1:
            cout << "Mode: Driving" << std::endl;
            drivingModeFunctions();
        break;
        case 2:
            cout << "Mode: Environmentally-Friendly" << std::endl;
        break;
        case 0:
            cout << "Going Back ..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        modeChoice();
    }
}

void Menu::drivingModeFunctions() {
    int choice;

    std::cout << "1. Independent Route Planning" << std::endl;
    std::cout << "2. Restricted Route Planning" << std::endl;
    std::cout << "0. Go Back" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        drivingModeFunctions();
    }



    switch (choice) {
        case 1:
            execDriveMode();

        break;
        case 2:
            execRestrictedMode();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        drivingModeFunctions();
    }
}

void Menu::execDriveMode() {
    auto source_dest = getSource_Destination();
    auto pair = routePlanner.execIndependentRoutePlanning(data, source_dest.first,source_dest.second);

    int total = 0;
    for (int i = 0; i < pair.first.size() - 1; i++) {
        int v1 = pair.first[i];
        int v2 = pair.first[i + 1];
        for (auto edge : data.get_locations_by_id()[v1]->getAdj()) {
            if (edge->getDest()->getInfo().getId() == v2) {
                auto e = edge->getWeight();
                total += e;
                //cout << e << endl;
                //cout << total << endl;
                break;
            }
        }
    }

    int total_t = 0;
    for (int i = 0; i < pair.second.size() - 1; i++) {
        int v1 = pair.second[i];
        int v2 = pair.second[i + 1];
        for (auto edge : data.get_locations_by_id()[v1]->getAdj()) {
            if (edge->getDest()->getInfo().getId() == v2) {
                total_t += edge->getWeight();
                //cout << total << endl;
                break;
            }
        }
    }

    if (pair.first.empty()) {
        cout << "No valid path" << endl;
        return;
    }
    for (int i = 0; i < pair.first.size(); i++) {
        cout << pair.first[i];
        if (i != pair.first.size() - 1) {
            cout << ",";
        }
        else {
            std::cout << "(" << total << ")\n";
        }
    }
    cout << endl;
    if (pair.second.size() == 0) {
        cout << "No valid planB" << endl;
        return;
    }
    for (int i = 0; i < pair.second.size(); i++) {
        cout << pair.second[i];
        if (i != pair.second.size() - 1) {
            cout << ",";
        }
        else {
            std::cout << "(" << total_t << ")\n";
        }
    }

    cout << endl;

    data.resetGraph();
}

void Menu::execRestrictedMode() {
    auto source_dest = getSource_Destination();

    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidEdges;
    int includeNode;

    getAvoidData(avoidNodes, avoidEdges, includeNode);

    auto result = routePlanner.execRestrictedRoutePlanning(data, source_dest.first, source_dest.second, avoidNodes, avoidEdges, includeNode);

    int total = 0;
    for (int i = 0; i < result.size() - 1; i++) {
        int v1 = result[i];
        int v2 = result[i + 1];
        for (auto edge : data.get_locations_by_id()[v1]->getAdj()) {
            if (edge->getDest()->getInfo().getId() == v2) {
                total += edge->getWeight();
                //cout << total << endl;
                break;
            }
        }
    }

    if (!result.empty()) {
        std::cout << "RestrictedDrivingRoute:";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i != result.size() - 1) {
                std::cout << ",";  // Add commas between IDs
            }
        }
        std::cout << "(" << total << ")\n";
    } else {
        std::cout << "No restricted route found.\n";
    }

    data.resetGraph();
}

pair<int,int> Menu::getSource_Destination() {
    int sourceId,destId;

    std::cout << "Source Id" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> sourceId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        getSource_Destination();
    }

    std::cout << "Destination Id" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> destId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        getSource_Destination();
    }
    return {sourceId,destId};
}

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <utility>

void Menu::getAvoidData(std::vector<int>& avoidNodes,
                        std::vector<std::pair<int, int>>& avoidEdges,
                        int& includeNode) {
    avoidNodes.clear();
    avoidEdges.clear();
    includeNode = -1;

    std::string line;

    // Read AvoidNodes
    std::cout << "Enter AvoidNodes:<id>,<id>,... (or type 'none' to skip): ";
    std::getline(std::cin, line);  // Read input
    if (line != "none" && !line.empty()) {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty())
                avoidNodes.push_back(std::stoi(token));
        }
    } else {
        std::cout << "No nodes to avoid.\n";
    }

    // Read AvoidEdges
    std::cout << "Enter AvoidEdges:(id,id),(id,id),... (or type 'none' to skip): ";
    std::getline(std::cin, line);  // Read input
    if (line != "none" && !line.empty()) {
        std::stringstream ss(line);
        std::string segment;
        while (std::getline(ss, segment, ')')) {
            size_t open = segment.find('(');
            if (open != std::string::npos) {
                std::string pairStr = segment.substr(open + 1);  // skip '('
                size_t comma = pairStr.find(',');
                if (comma != std::string::npos) {
                    int a = std::stoi(pairStr.substr(0, comma));
                    int b = std::stoi(pairStr.substr(comma + 1));
                    avoidEdges.emplace_back(a, b);
                }
            }
            // Remove the comma at the start of the next segment (if any)
            if (ss.peek() == ',') ss.ignore();
        }
    } else {
        std::cout << "No edges to avoid.\n";
    }

    // Read IncludeNode
    std::cout << "Enter IncludeNode:<id> (or type 'none' to skip): ";
    std::getline(std::cin, line);  // Read input
    if (line != "none" && !line.empty()) {
        includeNode = std::stoi(line);  // Get the specific node to include
    } else {
        includeNode = -1;  // No specific node to include
        std::cout << "No specific include node.\n";
    }
}






