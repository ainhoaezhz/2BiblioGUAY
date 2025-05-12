#ifndef SOCKETCLIENTE_H_
#define SOCKETCLIENTE_H_

#include <string>

class SocketCliente {
public:
    SocketCliente(const std::string& ip, int puerto);
    ~SocketCliente();

    bool conectar();
    void enviarComando(const std::string& comando);
    std::string recibirRespuesta();

private:
    int sockfd;
    std::string servidorIP;
    int servidorPuerto;
};

#endif
