#include "SocketCliente.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

SocketCliente::SocketCliente(const std::string& ip, int puerto)
    : servidorIP(ip), servidorPuerto(puerto), sockfd(-1) {}

SocketCliente::~SocketCliente() {
    if (sockfd != -1) {
        close(sockfd);
    }
}

bool SocketCliente::conectar() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creando socket\n";
        return false;
    }

    sockaddr_in servidorAddr;
    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_port = htons(servidorPuerto);

    if (inet_pton(AF_INET, servidorIP.c_str(), &servidorAddr.sin_addr) <= 0) {
        std::cerr << "Dirección IP no válida\n";
        return false;
    }

    if (connect(sockfd, (struct sockaddr*)&servidorAddr, sizeof(servidorAddr)) < 0) {
        std::cerr << "No se pudo conectar al servidor\n";
        return false;
    }

    std::cout << "Conectado al servidor\n";
    return true;
}

void SocketCliente::enviarComando(const std::string& comando) {
    send(sockfd, comando.c_str(), comando.length(), 0);
}

std::string SocketCliente::recibirRespuesta() {
    char buffer[1024] = {0};
    int bytesRecibidos = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
        return std::string(buffer);
    }
    return "";
}
