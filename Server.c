#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <netinet/in.h>

#include <unistd.h>

int main (void)
{
	int new_socket;
	int server_socket;
	int client_input;
	char server_message[100] = "ola ke ace";

	////////CREAR SOCKET////////
	server_socket = socket(AF_INET, SOCK_STREAM, 0);


	/////////DEFINIR DIRECCION DEL SERVIDOR//////////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	////////ASOCIAR LA DIRECCION DIFINIDA, AL SOCKET//////////
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket,10);

	/////////ESPERAR CONEXIONES DE ADMINISTRADORES O CLIENTES/////////
	while(1)
	{
		////////ACEPTAR LA CONEXION/////////
 		new_socket = accept(server_socket,NULL,NULL);

 		if (!fork())
 		{
 			//////ENVIAR/RECIBIR DATA///////
 			send(new_socket, server_message, sizeof(server_message), 0);
 			recv(new_socket, &client_input, sizeof(client_input), 0);
 			while(1)
 			{
 				if (client_input == 1)
 				{
 					send(new_socket, server_message, sizeof(server_message), 0);
 				}

 				if (client_input == 0)
 				{
 					break;
 				}
 				recv(new_socket, &client_input, sizeof(client_input), 0);
 			}
 			close(new_socket);
 			exit(0);
 		}
	}

	return 0;
}
