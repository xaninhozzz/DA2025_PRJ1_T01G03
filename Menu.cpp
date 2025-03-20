#include "Menu.h"
#include "BatchMode.h"
#include <iostream>
#include <string>
#include <fstream>

Menu::Menu() {}

void Menu::modeChoice() {
    int choice;
    std::ofstream input("input.txt", std::ios::app);

    std::cout << "Welcome to our GPS! Please choose your mode:" << std::endl;
    std::cout << "1. Driving" << std::endl;
    std::cout << "2. Walking" << std::endl;
    std::cout << "3. Go back" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            input << "Mode: Driving" << std::endl;
        break;
        case 2:
            input << "Mode: Walking" << std::endl;
        break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        modeChoice();
        return;
    }

    std::string source, destination;

    std::cout << "What is your location, right now?" << std::endl;
    std::cout << "Enter your location: ";
    std::cin >> source;
    std::cout << "And what is your destination?" << std::endl;
    std::cout << "Enter your destination: ";
    std::cin >> destination;

    input << "Source: " << source << std::endl;
    input << "Destination: " << destination << std::endl;

    input.close();

    BatchMode batch;
    batch.processBatchFile("input.txt", "output.txt");

    std::cout << "Please check file output.txt. It should've been created and must have the choices selected." << std::endl;
}

void Menu::getBestRouteInput() {
  std::cout << "bestroute" << std::endl;
  /*
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return;
    }

    std::string line, mode, source, destination;

    try {
        // Read Mode
        std::getline(inputFile, line);
        mode = line.substr(line.find(":") + 1);

        // Read Source
        std::getline(inputFile, line);
        source = line.substr(line.find(":") + 1);

        // Read Destination
        std::getline(inputFile, line);
        destination = line.substr(line.find(":") + 1);

        inputFile.close();

        // Display the extracted data
        std::cout << "Mode: " << mode << std::endl;
        std::cout << "Source: " << source << std::endl;
        std::cout << "Destination: " << destination << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error parsing input file: " << e.what() << std::endl;
        inputFile.close();
    }

   */
}

