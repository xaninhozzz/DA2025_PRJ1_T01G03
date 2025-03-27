//
// Created by anacastanheiros on 3/19/25.
//

#include "BatchMode.h"


BatchMode::BatchMode(){}

void BatchMode::processBatchFile(const std::string &inputFile, const std::string &outputFile)
{
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

    std::string line, key, value, val1, val2;
    int counter = 0;
    while (std::getline(input, line)) {
        std::istringstream iss(line);

        if (std::getline(iss, key, ':') && std::getline(iss, value)) {

        switch (counter){

            case 0:
                this->Mode = value;
                break;
            case 1:
               this->Source = std::stoi(value);
                break;
            case 2:
                this->Destination = std::stoi(value);
                break;
            case 3:
                this->MaxWalkTime = std::stoi(value);
                break;
            case 4:
                std::string s = "";
                
                for (char e : value){
                    if(e != ','){
                        s.push_back(e);
                    }
                    else{
                        this->AvoidNodes.push_back(std::stoi(s));
                        std::string s = "";
                    }
                }
                this->AvoidNodes.push_back(std::stoi(key));

                break;
            case 5:

            for (char e : value){
                
                if(e != ','){
                    continue;
                }
                else{
                    this->AvoidNodes.push_back(std::stoi(s));
                    std::string s = "";
            }
            this->AvoidNodes.push_back(std::stoi(key));
            
                break;
            case 6:
                break;
            default:
                break;
            }
            counter++;
        }
    }

    input.close();
    output.close();
}
