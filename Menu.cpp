#include "Menu.h"
#include "BatchMode.h"
#include <iostream>
#include <string>
#include <fstream>

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
    if (pair.first.empty()) {
        cout << "No valid path" << endl;
        return;
    }
    for (int i = 0; i < pair.first.size(); i++) {
        cout << pair.first[i] << " ";
    }
    cout << endl;
    if (pair.second.size() == 0) {
        cout << "No valid planB" << endl;
        return;
    }
    for (int i = 0; i < pair.second.size(); i++) {
        cout << pair.second[i] << " ";
    }
    cout << endl;
}

void Menu::execRestrictedMode() {
    auto source_dest = getSource_Destination();

    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidEdges;
    int includeNode;

    getAvoidData(avoidNodes, avoidEdges, includeNode);

    auto res = routePlanner.execRestrictedRoutePlanning(data, source_dest.first, source_dest.second, avoidNodes, avoidEdges, includeNode);



}

pair<int,int> Menu::getSource_Destination() {
    int sourceId,destId;

    std::cout << "Source Id" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> sourceId;

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        getSource_Destination();
    }

    std::cout << "Destination Id" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> destId;

    if (std::cin.fail()) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(1000, '\n');  // Ignore incorrect input
        std::cout << "Invalid choice. Please enter a number (1-3)." << std::endl;
        getSource_Destination();
    }
    return {sourceId,destId};
}

void Menu::getAvoidData(std::vector<int>& avoidNodes,
                        std::vector<std::pair<int, int>>& avoidEdges,
                        int& includeNode) {

    std::string line;

    // Read AvoidNodes
    std::cout << "Enter AvoidNodes:<id>,<id>,... (or type 'none' to skip):\n";
    std::getline(std::cin, line);
    if (line != "none" && line.find("AvoidNodes:") == 0) {
        std::string ids = line.substr(11); // skip "AvoidNodes:"
        std::stringstream ss(ids);
        std::string token;
        while (std::getline(ss, token, ',')) {
            avoidNodes.push_back(std::stoi(token));
        }
    }

    // Read AvoidEdges
    std::cout << "Enter AvoidEdges:(id,id),(id,id),... (or type 'none' to skip):\n";
    std::getline(std::cin, line);
    if (line != "none" && line.find("AvoidEdges:") == 0) {
        std::string segmentPart = line.substr(12); // skip "AvoidEdges:"
        std::stringstream ss(segmentPart);
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
    }

    // Read IncludeNode
    std::cout << "Enter IncludeNode:<id> (or type 'none' to skip):\n";
    std::getline(std::cin, line);
    if (line != "none" && line.find("IncludeNode:") == 0) {
        includeNode = std::stoi(line.substr(12));  // skip "IncludeNode:"
    } else {
        includeNode = -1;  // No specific node to include (if "none" is entered)
    }
}


