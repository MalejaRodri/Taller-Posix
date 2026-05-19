/*Variable globales*/
#ifndef POSIX_H
#define POSIX_H

/* Librerias generales */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Librerias POSIX */
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

/* Constantes */
#define BUFFER 5
#define MAX_BUFFERS 5

/* Estructura para memoria compartida de productor-consumidor */
typedef struct {
    int bus[BUFFER];
    int entrada;
    int salida;
} compartir_datos;

#endif
