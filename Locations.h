//
// Created by anacastanheiros on 3/24/25.
//

#ifndef LOCATIONS_H
#define LOCATIONS_H
#include <string>

class Locations {
  public:
    Locations(int id, std::string code, bool parking);
  private:
    int id;
    std::string code;
    bool parking;
    int getId();
    std::string getCode();
    bool getParking();
    void setId(int id);
    void setCode(std::string code);
    void setParking(bool parking);
};


#endif //LOCATIONS_H
