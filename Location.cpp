#include "Location.h"


Location::Location(string name, string code, int id, bool parking) {
    this->name = name;
    this->code = code;
    this->id = id;
    this->parking = parking;
}

string Location::getName() const {
    return name;
}

string Location::getCode() const {
    return code;
}

bool Location::getParking() const {
    return parking;
}

int Location::getId() const {
    return id;
}
// #endif // __LOCATION_H__