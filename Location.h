#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>
#include <iostream>

class Location {
public:
    // Constructor
    Location(std::string name, std::string code, int id, bool parking);

    // Getter methods
    std::string getName() const;
    std::string getCode() const;
    bool getParking() const;
    int getId() const;

    // Operators
    bool operator==(const Location &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Location& d);

private:
    std::string name;
    std::string code;
    int id;
    bool parking;
};

#endif // __LOCATION_H__
