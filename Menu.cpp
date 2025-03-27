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
        modeChoice();
    }
    auto vec = routePlanner.dijkstra(data.get_graph(),1,6,data.get_locations_by_id(),true);

    switch (choice) {
        case 1:
            for (int i = 0; i < vec.size(); i++) {
                std::cout << vec[i] << std::endl;
            }
        break;
        case 2:
            break;
        case 0:
            break;;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        drivingModeFunctions();
    }
}

