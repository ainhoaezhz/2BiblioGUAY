#include "MenuAdmin.h"
#include <iostream>

MenuAdmin::MenuAdmin() {}
MenuAdmin::~MenuAdmin() {}

void MenuAdmin::mostrarMenu() {
    char opcion;
    do {
        std::cout << "\n--- MENÚ ADMINISTRADOR ---\n";
        std::cout << "1. Gestionar inventario de libros\n";
        std::cout << "2. Gestionar usuarios\n";
        std::cout << "3. Préstamos y devoluciones\n";
        std::cout << "4. Generar informes\n";
        std::cout << "0. Salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case '1':
                std::cout << "-> Enviar comando: gestionarLibros\n";
                break;
            case '2':
                std::cout << "-> Enviar comando: gestionarUsuarios\n";
                break;
            case '3':
                std::cout << "-> Enviar comando: gestionarPrestamos\n";
                break;
            case '4':
                std::cout << "-> Enviar comando: generarInformes\n";
                break;
        }
    } while (opcion != '0');
}
