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
    void IndependentRoutePlanning();
    pair<int,int> getSource_Destination();
    void execDriveMode();
    RoutePlanner routePlanner;
};


#endif // MENU_H

