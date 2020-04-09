/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip = "127.0.0.1";
	char* puerto = "4444";

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	//Loggear "soy un log"
	log_info(logger, "soy un log");

	config = leer_config();
	config_set_value(config, "IP", "127.0.0.1");
	config_set_value(config, "PUERTO", "4444");
	config_save(config);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	printf("crear conexion");
	//crear conexion
	conexion = crear_conexion(ip, puerto);

	printf("enviar mensaje");

	//enviar mensaje
	char* mnsj = "holaa";

	enviar_mensaje(mnsj, conexion);

	printf("mensaje enviado");

	//recibir mensaje
	char* mensaje_recibido = recibir_mensaje(conexion);

	//loguear mensaje recibido
	log_info(logger, mensaje_recibido);

	terminar_programa(conexion, logger, config);

	return 0;

}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("/home/utnso/Game-watch-client/tp0.log", "tp0", 1, LOG_LEVEL_INFO);
}

//TODO
t_config* leer_config(void)
{
	return config_create("/home/utnso/Game-watch-client/tp0.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
