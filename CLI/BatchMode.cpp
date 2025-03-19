//
// Created by anacastanheiros on 3/19/25.
//

#include "BatchMode.h"
#include <iostream>
#include <fstream>
#include <sstream>

BatchMode::BatchMode(){
  std::cout << "BatchMode initiated..." << std::endl;
}

void BatchMode::processBatchFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input.is_open()) {
        std::cerr << "Error: Could not open input file: " << inputFile << std::endl;
        return;
    }

    if (!output.is_open()) {
        std::cerr << "Error: Could not open output file: " << outputFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        // Parse each line and process it
        std::istringstream iss(line);
        std::string key, value;

        while (std::getline(iss, key, ':') && std::getline(iss, value)) {
            // Process the key-value pairs here
            output << "Key: " << key << ", Value: " << value << "\n";
        }
    }

    input.close();
    output.close();
}
