#include "MenuUsuario.h"
#include <iostream>

MenuUsuario::MenuUsuario() {}
MenuUsuario::~MenuUsuario() {}

void MenuUsuario::mostrarMenu() {
    char opcion;
    do {
        std::cout << "\n=== Menú de Usuario ===\n";
        std::cout << "1. Ver catálogo\n";
        std::cout << "2. Solicitar préstamo\n";
        std::cout << "3. Devolver libro\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case '1':
                std::cout << "-> Enviar comando: verCatalogo\n";
                break;
            case '2':
                std::cout << "-> Enviar comando: solicitarPrestamo\n";
                break;
            case '3':
                std::cout << "-> Enviar comando: devolverLibro\n";
                break;
        }
    } while (opcion != '0');
}
