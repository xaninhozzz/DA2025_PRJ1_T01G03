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

    void getAvoidData(std::vector<int>& avoidNodes,
                            std::vector<std::pair<int, int>>& avoidSegments,
                            int& includeNode);

    void execDriveMode();
    void execRestrictedMode();
    RoutePlanner routePlanner;
};


#endif // MENU_H

