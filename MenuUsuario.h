#ifndef MENUUSUARIO_H_
#define MENUUSUARIO_H_

#include "Menu.h"

class MenuUsuario : public Menu {
public:
    MenuUsuario();
    virtual ~MenuUsuario();

    void mostrarMenu() override;
};

#endif
