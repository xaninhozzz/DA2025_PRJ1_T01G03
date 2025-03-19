//
// Created by Miguel Sousa on 18/03/2025.
//

#include <iostream>
#include <sstream>
#include "handler.h"

void startCLI() {
    std::string line;
    std::string mode;
    int source, destination;

    while(true) {
        std::cout << "Enter mode, source, and destination (or 'exit' to quit):" << std::endl;
        while (std::getline(std::cin, line)) {

            if (line == "exit") {
                break;
            }

            std::istringstream iss(line);
            std::string key;
            while (std::getline(iss, key, ' ')) {

            }

            /*
            if (mode == "driving") {
                //routePlanner.calculateDrivingRoute(source, destination);
                //routePlanner.calculateAlternativeDrivingRoute(source, destination);
            }
             */
        }
    }
}