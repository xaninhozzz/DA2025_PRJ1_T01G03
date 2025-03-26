#include "Location.h"
#include <iostream>

// ✅ Use std::string explicitly
Location::Location(std::string name, std::string code, int id, bool parking) {
    this->name = name;
    this->code = code;
    this->id = id;
    this->parking = parking;
}

std::string Location::getName() const {
    return name;
}

std::string Location::getCode() const {
    return code;
}

bool Location::getParking() const {
    return parking;
}

int Location::getId() const {
    return id;
}

bool Location::operator==(const Location &other) const {
    return other.id == this->id;
}

// ✅ Fixed std::endl usage
std::ostream& operator<<(std::ostream& os, const Location& l) {
    os << "Location: " << l.name << " with id --" << l.id 
       << " -- with code --" << l.code 
       << "-- and " << (l.parking ? "can park" : "can't park") 
       << std::endl;
    return os;
}
