#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <netinet/in.h>

#include <unistd.h>


int main (void)
{
	char server_data[100];
	int connection_status;
	int input;

	///////CREAR SOCKET/////
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);


	///////ESPECIFICAR DIRECCION///////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	///////CONECTAR AL SERVIDOR//////
	connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	if (connection_status == -1)
	{
		printf("ERROR\n");
	}


	///////SI EL SERVIDOR ACEPTA NUESTRA CONEXION PROCEDEMOS A ENVIAR/RECIBIR DATA///////

	////////RECIBIMOS INSTRUCCIONES DEL SERVIDOR////////
	recv(network_socket, &server_data, sizeof(server_data), 0);

	printf("%s\n",server_data);

	while(1)
	{
		scanf("%d",&input);
		send(network_socket, &input, sizeof(input), 0);
		if (input == 1)
		{
			recv(network_socket, &server_data, sizeof(server_data), 0);
			printf("%s\n",server_data);
		}
		if (input == 0)
		{
			break;
		}
	}

	return 0;
}
