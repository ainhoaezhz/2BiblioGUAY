#ifndef MENUADMIN_H_
#define MENUADMIN_H_

#include "Menu.h"

class MenuAdmin : public Menu {
public:
    MenuAdmin();
    virtual ~MenuAdmin();

    void mostrarMenu() override;
};

#endif
