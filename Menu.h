#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
    Menu();
    virtual ~Menu();

    virtual void mostrarMenu() = 0;
};

#endif
