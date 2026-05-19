/******************************************
*
* 	Pontificia Universidad Javeriana
*	Maria Alejandra Rodriguez
*		19/05/2026
*
*	Descripcion:
*	-Implementa concurrencia mediante hilos POSIX (pthread).
*	-Simula el modelo productor-consumidor dentro de un mismo proceso.
*	-Crea múltiples hilos productores y un hilo consumidor (spooler).
*	-Usa un buffer compartido para almacenar mensajes temporalmente.
*	-Sincroniza el acceso al buffer usando mutex y variables de condición.
*	-Evita condiciones de carrera entre los hilos.
*	-Los productores generan mensajes y el spooler los consume e imprime.
*	-Implementa un buffer circular para reutilizar posiciones del arreglo.
*	-Controla cuando el buffer está lleno o vacío mediante sincronización.
*	-Demuestra manejo seguro de recursos compartidos en programación concurrente
*
*******************************************/
#include "common.h"

/*Datos del buffer*/
char buf[MAX_BUFFERS][100];

/*Indice donde el productor escribira el siguiente dato*/
int buffer_index;

/*Indice desde donde el spooler leera el siguiente dato*/
int buffer_print_index;


/*Variables de sincronizacion*/

/*Mutex para proteger el acceso al buffer*/
pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;

/*Condicion usada cuando el buffer esta lleno*/
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;

/*Condicion usada para avisar que hay datos disponibles*/
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;

/*Cantidad de espacios disponibles en el buffer*/
int buffers_available = MAX_BUFFERS;

/*Cantidad de lineas pendientes por imprimir*/
int lines_to_print = 0;


/*Prototipos de funciones*/
void *producer(void *arg);
void *spooler(void *unused);


int main(){

    /*Identificadores de los hilos productores y del hilo spooler*/
    pthread_t tid_producer[10], tid_spooler;

    int i, r;

    /*Inicializacion de los indices del buffer*/
    buffer_index = buffer_print_index = 0;

    /*Creacion del hilo spooler o consumidor*/
    if ((r = pthread_create(&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    /*Arreglo para identificar cada hilo productor*/
    int thread_no[10];

    /*Creacion de los hilos productores*/
    for (i = 0; i < 10; i++) {

        thread_no[i] = i;

        /*Creacion del hilo productor*/
        if ((r = pthread_create(&tid_producer[i], NULL,
                                producer, (void *)&thread_no[i])) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    /*Espera a que finalicen todos los hilos productores*/
    for (i = 0; i < 10; i++) {

        if ((r = pthread_join(tid_producer[i], NULL)) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    /*Espera hasta que el spooler termine de imprimir todo*/
    while (lines_to_print)
        sleep(1);

    /*Cancelacion del hilo spooler*/
    if ((r = pthread_cancel(tid_spooler)) != 0) {

        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    exit(0);
}


/*Funcion ejecutada por los hilos productores*/
void *producer(void *arg){

    int i, r;

    /*Obtiene el id del hilo*/
    int my_id = *((int *)arg);

    /*Contador de mensajes producidos por el hilo*/
    int count = 0;

    /*Cada hilo produce 10 mensajes*/
    for (i = 0; i < 10; i++) {

        /*Bloquea el mutex para acceder al buffer*/
        if ((r = pthread_mutex_lock(&buf_mutex)) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        /*Si no hay espacios disponibles en el buffer, espera*/
        while (!buffers_available)
            pthread_cond_wait(&buf_cond, &buf_mutex);

        /*Guarda la posicion donde se escribira el dato*/
        int j = buffer_index;

        /*Avanza el indice del buffer*/
        buffer_index++;

        /*Si llega al final del buffer vuelve al inicio*/
        if (buffer_index == MAX_BUFFERS)
            buffer_index = 0;

        /*Disminuye los espacios disponibles del buffer*/
        buffers_available--;

        /*Guarda el mensaje dentro del buffer*/
        sprintf(buf[j], "Thread %d: %d\n", my_id, ++count);

        /*Incrementa las lineas pendientes por imprimir*/
        lines_to_print++;

        /*Avisa al spooler que hay datos listos*/
        pthread_cond_signal(&spool_cond);

        /*Libera el mutex*/
        if ((r = pthread_mutex_unlock(&buf_mutex)) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        /*Pausa para simular tiempo de produccion*/
        sleep(1);
    }

    return NULL;
}


/*Funcion ejecutada por el hilo spooler o consumidor*/
void *spooler(void *unused){
	(void)unused;
    int r;

    /*El spooler queda ejecutandose constantemente*/
    while (1) {

        /*Bloquea el mutex para acceder al buffer*/
        if ((r = pthread_mutex_lock(&buf_mutex)) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

        /*Si no hay lineas pendientes, el spooler espera*/
        while (!lines_to_print)
            pthread_cond_wait(&spool_cond, &buf_mutex);

        /*Imprime el mensaje almacenado en el buffer*/
        printf("%s", buf[buffer_print_index]);

        /*Disminuye las lineas pendientes*/
        lines_to_print--;

        /*Avanza el indice de lectura*/
        buffer_print_index++;

        /*Si llega al final del buffer vuelve al inicio*/
        if (buffer_print_index == MAX_BUFFERS)
            buffer_print_index = 0;

        /*Libera un espacio del buffer*/
        buffers_available++;

        /*Avisa a los productores que ya hay espacio disponible*/
        pthread_cond_signal(&buf_cond);

        /*Libera el mutex*/
        if ((r = pthread_mutex_unlock(&buf_mutex)) != 0) {

            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }

    return NULL;
}
