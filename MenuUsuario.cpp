
#include "MenuUsuario.h"
#include "SocketCliente.h"
#include <iostream>
#include <string>

MenuUsuario::MenuUsuario() {}
MenuUsuario::~MenuUsuario() {}

void MenuUsuario::mostrarMenu() {
    SocketCliente socket("127.0.0.1", 6000);
    if (!socket.conectar()) {
        std::cerr << "No se pudo conectar al servidor\n";
        return;
    }

    char opcion;
    do {
        std::cout << "\n=== Menú de Usuario ===\n";
        std::cout << "1. Ver catálogo\n";
        std::cout << "2. Solicitar préstamo\n";
        std::cout << "3. Devolver libro\n";
        std::cout << "4. Registrarse\n";
        std::cout << "0. Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case '1':
                socket.enviarComando("VER_CATALOGO");
                break;
            case '2': {
                std::string dni;
                int idLibro;
                std::cout << "Introduce tu DNI: ";
                std::getline(std::cin, dni);
                std::cout << "Introduce el ID del libro a solicitar: ";
                std::cin >> idLibro;
                std::cin.ignore();

                std::string comando = "SOLICITAR_PRESTAMO|" + dni + "|" + std::to_string(idLibro);
                socket.enviarComando(comando);
                break;
            }
            case '3': {
                std::string dni;
                int idPrestamo;
                std::cout << "Introduce tu DNI: ";
                std::getline(std::cin, dni);
                std::cout << "Introduce el ID del préstamo a devolver: ";
                std::cin >> idPrestamo;
                std::cin.ignore();

                std::string comando = "DEVOLVER_LIBRO|" + dni + "|" + std::to_string(idPrestamo);
                socket.enviarComando(comando);
                break;
            }
            case '4': {
                std::string nombre, apellidos, dni, direccion, email, telefono, contrasena;

                std::cout << "Nombre: ";
                std::getline(std::cin, nombre);
                std::cout << "Apellidos: ";
                std::getline(std::cin, apellidos);
                std::cout << "DNI: ";
                std::getline(std::cin, dni);
                std::cout << "Dirección: ";
                std::getline(std::cin, direccion);
                std::cout << "Email: ";
                std::getline(std::cin, email);
                std::cout << "Teléfono: ";
                std::getline(std::cin, telefono);
                std::cout << "Contraseña: ";
                std::getline(std::cin, contrasena);

                std::string comando = "REGISTRAR_USUARIO|" + nombre + "|" + apellidos + "|" + dni + "|" +
                                      direccion + "|" + email + "|" + telefono + "|" + contrasena;

                socket.enviarComando(comando);
                break;
            }
        }

        if (opcion != '0') {
            std::string respuesta = socket.recibirRespuesta();
            std::cout << "Servidor: " << respuesta << "\n";
        }

    } while (opcion != '0');
}
