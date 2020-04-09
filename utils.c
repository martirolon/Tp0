/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"

//TODO
/*
 * Recibe un paquete a serializar, y un puntero a un int en el que dejar
 * el tamaño del stream de bytes serializados que devuelve
 */
void* serializar_paquete(t_paquete* paquete, int bytes)
 {

	void* stream = malloc(bytes);
	int offset = 0;

	memcpy(stream, &(paquete -> codigo_operacion), sizeof(paquete -> codigo_operacion));
	offset += sizeof(paquete -> codigo_operacion);
	memcpy(stream + offset, &(paquete -> buffer -> size), sizeof(paquete -> buffer -> size));
	offset += sizeof(paquete -> buffer -> size);
	memcpy(stream + offset, paquete -> buffer -> stream, paquete -> buffer -> size);

	return stream;
}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODO
void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete paquete;
	paquete -> codigo_operacion = 1;
	paquete -> buffer -> stream = mensaje;
	paquete -> buffer -> size = strlen(*mensaje) + 1;

	void* stream = serializar_paquete(paquete, paquete -> buffer -> size);

	send(socket_cliente, *stream, paquete -> buffer -> size, 0); //para tener el cuenta el centinela
}
//TODO
char* recibir_mensaje(int socket_cliente)
{
	int bytes_recibidos;
	char* buffer = malloc(10);

	bytes_recibidos = recv(socket_cliente, buffer, 9 , 0); //para tener en cuenta el centinela

	// aca habria que chequear que no de 0 porq sino significa que el server corto conexion

	buffer[bytes_recibidos] = '\0';

	free(buffer);

	return buffer;
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
