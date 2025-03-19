#ifndef MENU_H
#define MENU_H

class Menu {
  public:
    Menu();
    void displayMenu();
    void runBatchMode();
    void handleMenuChoice(int choice);
    void getBestRouteInput();
    void displaySubMenu();
    void handleSubMenuChoice(int choice);


};


#endif // MENU_H

