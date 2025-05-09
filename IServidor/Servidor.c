#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 6000

void procesarComando(const char *mensaje, char *respuesta) {
    if (strcmp(mensaje, "LISTAR_LIBROS") == 0) {
        strcpy(respuesta, "Aquí va la lista de libros.");
    } else {
        strcpy(respuesta, "Comando no reconocido.");
    }
}

int main() {
    int sock_servidor, sock_cliente, c;
    struct sockaddr_in servidor, cliente;
    char buffer[512], respuesta[512];

    sock_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_servidor == -1) {
        perror("No se pudo crear el socket");
        return 1;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(PUERTO);

    if (bind(sock_servidor, (struct sockaddr*)&servidor, sizeof(servidor)) < 0) {
        perror("Error en bind");
        return 1;
    }

    listen(sock_servidor, 3);
    printf("Esperando conexiones en puerto %d...\n", PUERTO);

    c = sizeof(struct sockaddr_in);
    sock_cliente = accept(sock_servidor, (struct sockaddr*)&cliente, (socklen_t*)&c);
    printf("Cliente conectado.\n");

    while (1) {
        int len = recv(sock_cliente, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0) break;
        buffer[len] = '\0';

        procesarComando(buffer, respuesta);
        send(sock_cliente, respuesta, strlen(respuesta), 0);
    }

    close(sock_cliente);
    close(sock_servidor);
    return 0;
}
