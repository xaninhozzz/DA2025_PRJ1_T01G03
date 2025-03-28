//
// Created by anacastanheiros on 3/19/25.
//

#include "BatchMode.h"


BatchMode::BatchMode(){}

void BatchMode::processBatchFile(const std::string &inputFile, const std::string &outputFile) {
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

    // este metodo nao depende da ordem do input nem da quantidade de linhas
    // If we dont have [&], the lambda wont be able to access or modify the outer variables
    std::unordered_map<std::string, std::function<void(const std::string&)>> handlers = {
        {"Mode", [&](const std::string& v) {
            this->Mode = v;
        }},
        {"Source", [&](const std::string& v) {
            this->Source = std::stoi(v);
        }},
        {"Destination", [&](const std::string& v) {
            this->Destination = std::stoi(v);
        }},
        {"MaxWalkTime", [&](const std::string& v) {
            this->MaxWalkTime = std::stoi(v);
        }},
        {"AvoidNodes", [&](const std::string& v) {
            std::string s = "";
            for (char e : v) {
                if (e != ',') {
                    s.push_back(e);
                } else {
                    this->AvoidNodes.push_back(std::stoi(s));
                    s = "";
                }
            }
            if (!s.empty()) {
                this->AvoidNodes.push_back(std::stoi(s));
            }
        }},
        {"AvoidSegments", [&](const std::string& v) {
            std::string first = "", second = "";
            bool firstp = true;
            for (char e : v) {
                if (e == ',') {
                    firstp = false;
                } else if (e == ')') {
                    this->AvoidSegments.emplace_back(std::stoi(first), std::stoi(second));
                    first = "";
                    second = "";
                    firstp = true;
                } else if (e == '(') {
                    continue;
                } else {
                    if (firstp) {
                        first.push_back(e);
                    } else {
                        second.push_back(e);
                    }
                }
            }
        }},
        {"IncludeNode", [&](const std::string& v) {
            this->IncludeNode = std::stoi(v);
        }},
    };

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            auto it = handlers.find(key);
            if (it != handlers.end()) {
                try {
                    it->second(value);
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing '" << key << "': " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Warning: Unknown key '" << key << "' ignored.\n";
            }
        }
    }

    input.close();
    output.close();
}