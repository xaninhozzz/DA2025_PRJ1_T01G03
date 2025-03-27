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
