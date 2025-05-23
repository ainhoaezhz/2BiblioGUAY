#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include "MenuUsuario.h"
#include "MenuAdmin.h"

using namespace std;

#define MAX 100

void mostrarMenuPrincipal(int socket);
void iniciarSesion(int socket);
void registrarse(int socket);

void mostrarMenuPrincipal(int socket) {
	cout << "MOSTRANDO MENU PRINCIPAL..." << endl;
    char opcion;

    do {
        cout << "\nBIBLIOTECA\n";
        cout << "------------------\n";
        cout << "Bienvenido\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Registrarse\n";
        cout << "0. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        cin.ignore();

        switch (opcion) {
            case '1':
                iniciarSesion(socket);
                break;
            case '2':
                registrarse(socket);
                break;
            case '0':
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "ERROR! Opción incorrecta" << endl;
        }
    } while (opcion != '0');
}

void iniciarSesion(int socket) {
    char usuario[MAX], contrasena[MAX];
    int esAdmin = 0;
    char sendBuff[512], recvBuff[512];

    do {
        cout << "\nINICIO DE SESIÓN\n";
        cout << "--------------\n";
        cout << "DNI: ";
        cin >> usuario;
        cout << "Contraseña: ";
        cin >> contrasena;

        snprintf(sendBuff, sizeof(sendBuff), "LOGIN|%s|%s", usuario, contrasena);
        send(socket, sendBuff, strlen(sendBuff), 0);

        int bytes = recv(socket, recvBuff, sizeof(recvBuff) - 1, 0);
        if (bytes <= 0) {
            cout << "Error: no se recibió respuesta del servidor.\n";
            return;
        }

        recvBuff[bytes] = '\0';

        if (strncmp(recvBuff, "OK|", 3) == 0) {
            esAdmin = recvBuff[3] - '0';
            cout << "\n¡Inicio de sesión exitoso! Bienvenido, " << usuario << "." << endl;
            cout << "Rol: " << (esAdmin ? "Administrador" : "Usuario Normal") << endl;

            if (esAdmin) {
                mostrarMenuAdmin(socket, usuario);
                return;
            } else {
                mostrarMenuUsuario(socket, usuario);
                return;
            }

        } else {
            cout << "\nError: Usuario o contraseña incorrectos. Inténtelo de nuevo.\n";
        }

    } while (true);
}

void registrarse(int socket) {
    string nombre, apellidos, dni, direccion, email, telefono, contrasena;

    cout << "\nREGISTRO DE USUARIO\n";
    cout << "----------------------\n";

    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Apellidos: ";
    getline(cin, apellidos);
    cout << "DNI: ";
    getline(cin, dni);
    cout << "Direccion: ";
    getline(cin, direccion);
    cout << "Email: ";
    getline(cin, email);
    cout << "Telefono: ";
    getline(cin, telefono);
    cout << "Contraseña: ";
    getline(cin, contrasena);

    stringstream comando;
    comando << "REGISTRAR_USUARIO|" << nombre << "|" << apellidos << "|" << dni << "|"
            << direccion << "|" << email << "|" << telefono << "|" << contrasena;

    send(socket, comando.str().c_str(), comando.str().length(), 0);

    char respuesta[512];
    int bytes = recv(socket, respuesta, sizeof(respuesta) - 1, 0);
    if (bytes > 0) {
        respuesta[bytes] = '\0';
        cout << "Respuesta del servidor: " << respuesta << endl;
    } else {
        cout << "No se recibió respuesta del servidor." << endl;
    }
}
