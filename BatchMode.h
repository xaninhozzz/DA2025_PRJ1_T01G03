//
// Created by anacastanheiros on 3/19/25.
//

#ifndef BATCHMODE_H
#define BATCHMODE_H

#include <string>

class BatchMode {
public:
  BatchMode();
  void processBatchFile(const std::string& inputFile, const std::string& outputFile);
};



#endif //BATCHMODE_H
