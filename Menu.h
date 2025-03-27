#ifndef MENU_H
#define MENU_H
#include "Data.h"
#include  "RoutePlanner.h"
class Menu {
  public:
    Menu();
    int run();
    int selectTypeOfMenu();
    void getBestRouteInput();
    void modeChoice();
    void drivingModeFunctions();
    Data data;
    RoutePlanner routePlanner;
};


#endif // MENU_H

