#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main() {
    int sock;
    struct sockaddr_in server;
    char mensaje[512], respuesta[512];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "No se pudo crear el socket.\n";
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Error al conectar con el servidor.\n";
        return 1;
    }

    std::cout << "Conectado al servidor.\n";

    while (true) {
        std::cout << "\nEscribe un comando (o SALIR): ";
        std::cin.getline(mensaje, sizeof(mensaje));

        if (strcmp(mensaje, "SALIR") == 0) break;

        send(sock, mensaje, strlen(mensaje), 0);

        int len = recv(sock, respuesta, sizeof(respuesta) - 1, 0);
        if (len > 0) {
            respuesta[len] = '\0';
            std::cout << "Respuesta: " << respuesta << std::endl;
        }
    }

    close(sock);
    return 0;
}
