#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "MenuPrincipal.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6042
using namespace std;

int main(int argc, char *argv[]) {

	int s;
	struct sockaddr_in server;
	//char sendBuff[512], recvBuff[512];

	printf("\nInitialising...\n");
	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Could not create socket");
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
		perror("Connection error");
		close(s);
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/
	mostrarMenuPrincipal(s);

	/*ACABA EL PROGRAMA DEL CLIENTE*/

	// CLOSING
	close(s);

	cin.get();


	return 0;
}
