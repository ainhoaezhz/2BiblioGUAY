// MenuAdmin.cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

char menuAdministrador() {
    char opcion;
    cout << "\n--- MENÚ ADMINISTRADOR ---\n";
    cout << "1. Gestionar inventario de libros\n";
    cout << "2. Gestionar usuarios\n";
    cout << "3. Registros de préstamos y devoluciones\n";
    cout << "4. Generar informes\n";
    cout << "0. Salir\n";
    cout << "Elige una opción: ";
    cin >> opcion;
    cin.ignore();
    return opcion;
}

void gestionarInventarioLibros(int s) {
    char opcion;
    do {
        cout << "\n--- GESTIÓN DE INVENTARIO DE LIBROS ---\n";
        cout << "a. Añadir nuevo libro\n";
        cout << "b. Editar información de un libro\n";
        cout << "c. Eliminar un libro\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        string comando;

        if (opcion == 'a') {
            // Pedir datos para añadir libro
            string titulo, autor, genero;
            cout << "Introduzca título: ";
            getline(cin, titulo);
            cout << "Introduzca autor: ";
            getline(cin, autor);
            cout << "Introduzca género: ";
            getline(cin, genero);

            // Construir mensaje completo
            comando = "AGREGAR_LIBRO|" + titulo + "|" + autor + "|" + genero;

            // Enviar y recibir respuesta
            send(s, comando.c_str(), comando.length(), 0);

            char respuesta[1024];
            int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
            if (bytes > 0) {
                respuesta[bytes] = '\0';
                cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
            } else {
                cout << "Error recibiendo respuesta del servidor.\n";
            }
            continue; // Volver a mostrar menú
        }
        else if (opcion == 'b') {
            // Pedir datos para editar libro
            string id, titulo, autor, genero;
            cout << "Introduzca ID del libro a editar: ";
            getline(cin, id);
            cout << "Nuevo título (dejar vacío para no cambiar): ";
            getline(cin, titulo);
            cout << "Nuevo autor (dejar vacío para no cambiar): ";
            getline(cin, autor);
            cout << "Nuevo género (dejar vacío para no cambiar): ";
            getline(cin, genero);

            comando = "EDITAR_LIBRO|" + id + "|" + titulo + "|" + autor + "|" + genero;
            send(s, comando.c_str(), comando.length(), 0);

            char respuesta[1024];
            int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
            if (bytes > 0) {
                respuesta[bytes] = '\0';
                cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
            } else {
                cout << "Error recibiendo respuesta del servidor.\n";
            }
            continue;
        }
        else if (opcion == 'c') {
            string id;
            cout << "Introduzca ID del libro a eliminar: ";
            getline(cin, id);

            comando = "ELIMINAR_LIBRO|" + id;
            send(s, comando.c_str(), comando.length(), 0);

            char respuesta[1024];
            int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
            if (bytes > 0) {
                respuesta[bytes] = '\0';
                cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
            } else {
                cout << "Error recibiendo respuesta del servidor.\n";
            }
            continue;
        }
        else if (opcion == '0') {
            return;  // salir al menú anterior
        }
        else {
            cout << "Opción no válida\n";
        }

    } while (true);
}


void gestionarUsuarios(int s) {
    char opcion;
    do {
        cout << "\n--- GESTIÓN DE USUARIOS ---\n";
        cout << "a. Registrar nuevo usuario\n";
        cout << "b. Editar datos de usuario\n";
        cout << "c. Eliminar usuarios\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        string comando;

        if (opcion == 'a') {
            string nombre, apellidos, dni, direccion, email, telefono, contrasena;
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Apellidos: ";
            getline(cin, apellidos);
            cout << "DNI: ";
            getline(cin, dni);
            cout << "Dirección: ";
            getline(cin, direccion);
            cout << "Email: ";
            getline(cin, email);
            cout << "Teléfono: ";
            getline(cin, telefono);
            cout << "Contraseña: ";
            getline(cin, contrasena);

            comando = "REGISTRAR_USUARIO|" + nombre + "|" + apellidos + "|" + dni + "|" + direccion + "|" + email + "|" + telefono + "|" + contrasena;

        } else if (opcion == 'b') {
            string dni, campo, nuevoValor;
            cout << "DNI del usuario a editar: ";
            getline(cin, dni);
            cout << "Campo a editar (nombre, apellidos, direccion, email, telefono, contrasena): ";
            getline(cin, campo);
            cout << "Nuevo valor: ";
            getline(cin, nuevoValor);

            comando = "EDITAR_USUARIO|" + dni + "|" + campo + "|" + nuevoValor;

        } else if (opcion == 'c') {
            string dni;
            cout << "DNI del usuario a eliminar: ";
            getline(cin, dni);

            comando = "ELIMINAR_USUARIO|" + dni;

        } else if (opcion == '0') {
            return;

        } else {
            cout << "Opción no válida\n";
            continue;
        }

        if (send(s, comando.c_str(), comando.length(), 0) < 0) {
            cerr << "Error enviando datos al servidor.\n";
            return;
        }

        char respuesta[1024];
        int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
        if (bytes > 0) {
            respuesta[bytes] = '\0';
            cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
        } else {
            cout << "Error recibiendo respuesta del servidor.\n";
        }

    } while (true);
}

void gestionarPrestamosDevoluciones(int s) {
    char opcion;
    do {
        cout << "\n--- REGISTROS DE PRÉSTAMOS Y DEVOLUCIONES ---\n";
        cout << "a. Registrar préstamo\n";
        cout << "b. Registrar devolución\n";
        cout << "c. Mostrar préstamos activos\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        string comando;

        if (opcion == 'a') {
            string dni, idLibro;
            cout << "DNI del usuario: ";
            getline(cin, dni);
            cout << "ID del libro a prestar: ";
            getline(cin, idLibro);

            comando = "REGISTRAR_PRESTAMO|" + dni + "|" + idLibro;

        } else if (opcion == 'b') {
            string dni, idLibro;
            cout << "DNI del usuario: ";
            getline(cin, dni);
            cout << "ID del libro a devolver: ";
            getline(cin, idLibro);

            comando = "REGISTRAR_DEVOLUCION|" + dni + "|" + idLibro;

        } else if (opcion == 'c') {
            comando = "MOSTRAR_PRESTAMOS_ACTIVOS";

        } else if (opcion == '0') {
            return;

        } else {
            cout << "Opción no válida\n";
            continue;
        }

        if (send(s, comando.c_str(), comando.length(), 0) < 0) {
            cerr << "Error enviando datos al servidor.\n";
            return;
        }

        char respuesta[4096];
        int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
        if (bytes > 0) {
            respuesta[bytes] = '\0';
            cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
        } else {
            cout << "Error recibiendo respuesta del servidor.\n";
        }

    } while (true);
}

void generarInformes(int s) {
    char opcion;
    do {
        cout << "\n--- GENERAR INFORMES ---\n";
        cout << "a. Ver estadísticas\n";
        cout << "b. Listar libros disponibles\n";
        cout << "c. Usuarios con más préstamos\n";
        cout << "d. Libro más prestado\n";
        cout << "e. Préstamos vencidos\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        string comando;

        if (opcion == 'a') {
            comando = "ESTADISTICAS";
        } else if (opcion == 'b') {
            comando = "LISTAR_LIBROS";
        } else if (opcion == 'c') {
            comando = "USUARIO_TOP";
        } else if (opcion == 'd') {
            comando = "LIBRO_TOP";
        } else if (opcion == 'e') {
            comando = "PRESTAMOS_VENCIDOS";
        } else if (opcion == '0') {
            return;
        } else {
            cout << "Opción no válida\n";
            continue;
        }

        if (send(s, comando.c_str(), comando.length(), 0) < 0) {
            cerr << "Error enviando datos al servidor.\n";
            return;
        }

        char respuesta[4096];
        int bytes = recv(s, respuesta, sizeof(respuesta) - 1, 0);
        if (bytes > 0) {
            respuesta[bytes] = '\0';
            cout << "\n🟢 Respuesta del servidor:\n" << respuesta << "\n";
        } else {
            cout << "Error recibiendo respuesta del servidor.\n";
        }

    } while (true);
}

void mostrarMenuAdmin(int s, const char* usuario) {
    char opcion;
    do {
        opcion = menuAdministrador();

        switch (opcion) {
            case '1':
                gestionarInventarioLibros(s);
                break;
            case '2':
                gestionarUsuarios(s);
                break;
            case '3':
                gestionarPrestamosDevoluciones(s);
                break;
            case '4':
                generarInformes(s);
                break;
            case '0':
                cout << "Volviendo al menú principal...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }

    } while (opcion != '0');
}
