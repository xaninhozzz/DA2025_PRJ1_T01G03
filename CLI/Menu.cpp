#include "Menu.h"
#include "BatchMode.h"
#include <iostream>
#include <string>

Menu::Menu() {}

void Menu::displayMenu() {
    int choice;
    std::cout << "Select an option:" << std::endl;
    std::cout << "1. Interactive Mode" << std::endl;
    std::cout << "2. Batch Mode" << std::endl;
    std::cout << "3. Exit" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;
    handleMenuChoice(choice);
}

void Menu::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            displaySubMenu();
            break;
        case 2:
            runBatchMode();
            break;
        case 3:
            std::cout << "Exiting the program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            displayMenu();
            break;
    }
}

void Menu::displaySubMenu() {
    int choice;
    std::cout << "Interactive Mode Options:" << std::endl;
    std::cout << "1. Best Route" << std::endl;
    //std::cout << "2. Alternative Independent Route" << std::endl;
    std::cout << "2. Back to Main Menu" << std::endl;

    std::cout << "Enter your choice: ";
    std::cin >> choice;
    handleSubMenuChoice(choice);
}

void Menu::handleSubMenuChoice(int choice) {
    switch (choice) {
        case 1:
            getBestRouteInput();
            break;
        /*
        case 2:
            AlternativeRoute();
            break;
		*/

        case 2:
            displayMenu();
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            displaySubMenu();
            break;
    }
}

void Menu::runBatchMode() {
    BatchMode batch;
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";
    batch.processBatchFile(inputFile, outputFile);
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

