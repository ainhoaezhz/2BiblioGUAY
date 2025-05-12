
#include "MenuAdmin.h"
#include "SocketCliente.h"
#include <iostream>

MenuAdmin::MenuAdmin() {}
MenuAdmin::~MenuAdmin() {}

void MenuAdmin::mostrarMenu() {
    SocketCliente socket("127.0.0.1", 6000);
    if (!socket.conectar()) {
        std::cerr << "No se pudo conectar al servidor\n";
        return;
    }

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
                socket.enviarComando("GESTIONAR_LIBROS");
                break;
            case '2':
                socket.enviarComando("GESTIONAR_USUARIOS");
                break;
            case '3':
                socket.enviarComando("GESTIONAR_PRESTAMOS");
                break;
            case '4':
                socket.enviarComando("GENERAR_INFORMES");
                break;
        }

        if (opcion != '0') {
            std::string respuesta = socket.recibirRespuesta();
            std::cout << "Servidor: " << respuesta << "\n";
        }

    } while (opcion != '0');
}
