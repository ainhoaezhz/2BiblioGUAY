
#include "SocketCliente.h"
#include "MenuAdmin.h"
#include "MenuUsuario.h"
#include <iostream>
#include <string>

int main() {
    SocketCliente cliente("127.0.0.1", 6000);
    if (!cliente.conectar()) {
        std::cerr << "No se pudo conectar al servidor.\n";
        return 1;
    }

    std::string nombre, contrasena;
    std::cin.ignore(); // limpiar buffer

    std::cout << "Nombre de usuario: ";
    std::getline(std::cin, nombre);
    std::cout << "Contraseña: ";
    std::getline(std::cin, contrasena);

    std::string comando = "INICIAR_SESION|" + nombre + "|" + contrasena;
    cliente.enviarComando(comando);

    std::string respuesta = cliente.recibirRespuesta();
    std::cout << "Servidor: " << respuesta << "\n";

    if (respuesta == "LOGIN_OK|ADMIN") {
        MenuAdmin menu;
        menu.mostrarMenu();
    } else if (respuesta == "LOGIN_OK|USUARIO") {
        MenuUsuario menu;
        menu.mostrarMenu();
    } else {
        std::cout << "Inicio de sesión fallido.\n";
    }

    return 0;
}
