//
// Created by anacastanheiros on 3/19/25.
//

#ifndef BATCHMODE_H
#define BATCHMODE_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


class BatchMode {
  public:
    BatchMode();
    void processBatchFile(const std::string& inputFile, const std::string& outputFile);
    std::string Mode;
    int Source;
    int Destination;
    int MaxWalkTime;
    std::vector<int> AvoidNodes;
    std::vector<std::pair<int,int>> AvoidSegments;
    int IncludeNode;
};



#endif //BATCHMODE_H
