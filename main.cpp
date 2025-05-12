#include "SocketCliente.h"
#include "MenuAdmin.h"
#include "MenuUsuario.h"
#include <iostream>

int main() {
    std::string ip;
    int puerto;

    std::cout << "Introduce la IP del servidor: ";
    std::cin >> ip;
    std::cout << "Introduce el puerto: ";
    std::cin >> puerto;

    SocketCliente cliente(ip, puerto);
    if (!cliente.conectar()) {
        std::cerr << "No se pudo conectar al servidor.\n";
        return 1;
    }

    int tipoUsuario;
    std::cout << "¿Qué tipo de usuario eres? (1 = Admin, 2 = Usuario): ";
    std::cin >> tipoUsuario;

    if (tipoUsuario == 1) {
        MenuAdmin menu;
        menu.mostrarMenu();
    } else if (tipoUsuario == 2) {
        MenuUsuario menu;
        menu.mostrarMenu();
    } else {
        std::cout << "Tipo no válido.\n";
    }

    return 0;
}
