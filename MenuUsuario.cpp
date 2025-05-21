// MenuUsuario.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

char menuUsuario() {
    char opcionMenu;
    cout << "----------" << endl;
    cout << "USUARIO: MENU" << endl;
    cout << "1. Ver perfil" << endl;
    cout << "2. Editar perfil" << endl;
    cout << "3. Buscar libros" << endl;
    cout << "4. Historial de préstamos" << endl;
    cout << "5. Devolver libros" << endl;
    cout << "6. Listado de libros disponibles" << endl;
    cout << "0. Salir" << endl;
    cout << "Elige una opción: ";
    cin >> opcionMenu;
    cin.ignore();

    return opcionMenu;
}

void mostrarMenuUsuario(int socket, const char* usuario) {
    char opcionMenu;

    while (true) {  // Bucle continuo hasta que el usuario elija salir
        opcionMenu = menuUsuario();

        string comando;

        switch (opcionMenu) {
            case '1':
                cout << "Viendo perfil...\n";
                comando = string("VER_PERFIL|") + usuario;
                break;
            case '2':
                cout << "Editando perfil...\n";
                comando = string("EDITAR_PERFIL|") + usuario;
                break;
            case '3': {
                cout << "Buscando libros...\n";
                cout << "Introduzca el título del libro: ";
                string titulo;
                cin.ignore();
                getline(cin, titulo);
                comando = "BUSCAR_LIBRO|" + titulo;
                break;
            }
            case '4':
                cout << "Historial de préstamos...\n";
                comando = string("HISTORIAL|") + usuario;
                break;
            case '5': {
                cout << "Devolviendo libros...\n";
                string idPrestamo;
                cout << "ID del préstamo a devolver: ";
                cin >> idPrestamo;
                cin.ignore();
                comando = string("DEVOLVER|") + idPrestamo;
                break;
            }
            case '6':
                cout << "Listando libros disponibles...\n";
                comando = "LISTAR_LIBROS";
                break;
            case '0':
                cout << "Saliendo...\n";
                send(socket, "SALIR", strlen("SALIR"), 0);  // Avisa al servidor que va a salir
                return;  // Termina la función para cerrar el flujo
            default:
                cout << "ERROR! Opción incorrecta\n";
                continue;  // Continúa el bucle sin salir si la opción es incorrecta
        }

        // Enviar comando
        if (send(socket, comando.c_str(), comando.length(), 0) < 0) {
            perror("Error al enviar datos al servidor");
            return;
        }

        // Recibir y mostrar respuesta
        char respuesta[1024];
        int bytes = recv(socket, respuesta, sizeof(respuesta) - 1, 0);
        if (bytes > 0) {
            respuesta[bytes] = '\0';
            cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
        } else {
            cout << "\n🔴 Error al recibir respuesta del servidor.\n";
        }
    }
}

