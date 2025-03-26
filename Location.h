#define __LOCATION_H__
#ifdef __LOCATION_H__

#include <string>
#include <vector>
using namespace std;


class Location {
    public:
        Location(string name, string code, int id, bool parking);
        string getName() const;
        string getCode() const;
        bool getParking() const;
        int getId() const;
    private:
        string name;
        string code;
        int id;
        bool parking;
};


#endif // __LOCATION_H__