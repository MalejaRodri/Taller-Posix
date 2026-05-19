/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia: Sistemas Operativos
 * Tema: POSIX para la creación de hilos concurrentes
 *
 * Descripción:
 * Este programa lee un vector de números enteros desde un archivo y utiliza varios hilos
 * POSIX para buscar el valor máximo de forma concurrente.
 *********************************************************************************************/

#include "common.h"

/* Estructura con los datos que recibe cada hilo */
struct argHilos{

    /* Posicion inicial del vector */
    int inicio;

    /* Posicion final del vector */
    int fin;

    /* Referencia al vector principal */
    int *vector;

    /* Maximo encontrado por el hilo */
    int maxparcial;
};

/* Alias de la estructura */
typedef struct argHilos param_H;


/* Funcion ejecutada por cada hilo */
void *buscarMax(void *parametro){

    /* Obtiene los argumentos enviados al hilo */
    param_H *argumentos = (param_H *)parametro;

    /* Inicializa el maximo parcial */
    argumentos->maxparcial =
        argumentos->vector[argumentos->inicio];

    /* Recorre la parte del vector asignada */
    for(int i = argumentos->inicio;
        i < argumentos->fin;
        i++){

        /* Verifica si encuentra un numero mayor */
        if(argumentos->vector[i] >
           argumentos->maxparcial)

            /* Actualiza el maximo parcial */
            argumentos->maxparcial =
                argumentos->vector[i];
    }

    /* Finaliza el hilo */
    pthread_exit(0);

    return NULL;
}


/* Funcion que crea los hilos y calcula el maximo */
int maximoValor(int *vec, int n, int nhilos){

    /* Arreglo de identificadores de hilos */
    pthread_t *hilos;

    /* Arreglo con parametros para cada hilo */
    param_H *parametros;

    /* Variable para almacenar el maximo global */
    int maximo;

    /* Cantidad de elementos por hilo */
    int bloque;

    /* Elementos sobrantes */
    int resto;

    /* Reserva memoria para los hilos */
    hilos = malloc(sizeof(pthread_t) * nhilos);

    /* Reserva memoria para los parametros */
    parametros = malloc(sizeof(param_H) * nhilos);

    /* Verifica errores de memoria */
    if(hilos == NULL || parametros == NULL){

        fprintf(stderr,
                "Error al reservar memoria\n");

        exit(EXIT_FAILURE);
    }

    /* Calcula cuantos elementos procesa cada hilo */
    bloque = n / nhilos;

    /* Calcula elementos restantes */
    resto = n % nhilos;

    /* Inicio del primer bloque */
    int inicio = 0;

    /* Creacion de los hilos */
    for(int i = 0; i < nhilos; i++){

        /* Posicion inicial del hilo */
        parametros[i].inicio = inicio;

        /* Posicion final del hilo */
        parametros[i].fin = inicio + bloque;

        /* Reparte elementos sobrantes */
        if(i < resto)
            parametros[i].fin++;

        /* Asigna el vector */
        parametros[i].vector = vec;

        /* Inicializa el maximo parcial */
        parametros[i].maxparcial =
            vec[parametros[i].inicio];

        /* Actualiza el inicio del siguiente hilo */
        inicio = parametros[i].fin;

        /* Creacion del hilo */
        if(pthread_create(&hilos[i],
                          NULL,
                          buscarMax,
                          (void *)&parametros[i]) != 0){

            fprintf(stderr,
                    "Error al crear el hilo %d\n", i);

            exit(EXIT_FAILURE);
        }
    }

    /* Espera a que todos los hilos finalicen */
    for(int i = 0; i < nhilos; i++){

        if(pthread_join(hilos[i], NULL) != 0){

            fprintf(stderr,
                    "Error al esperar el hilo %d\n", i);

            exit(EXIT_FAILURE);
        }
    }

    /* Inicializa el maximo global */
    maximo = parametros[0].maxparcial;

    /* Compara todos los maximos parciales */
    for(int i = 1; i < nhilos; i++){

        /* Verifica si encuentra un maximo mayor */
        if(parametros[i].maxparcial > maximo)

            /* Actualiza el maximo global */
            maximo = parametros[i].maxparcial;
    }

    /* Libera memoria */
    free(hilos);
    free(parametros);

    /* Retorna el maximo encontrado */
    return maximo;
}


/* Funcion principal */
int main(int argc, char *argv[]){

    FILE *fichero;

    /* Tamaño del vector */
    int n;

    /* Numero de hilos */
    int nhilos;

    int i;

    /* Vector dinamico */
    int *vec;

    int ret;

    /* Variable donde se guarda el maximo final */
    int maximo;

    /* Verifica cantidad de argumentos */
    if(argc != 3){

        fprintf(stderr,
                "Uso: %s archivo.txt numero_hilos\n",
                argv[0]);

        exit(EXIT_FAILURE);
    }

    /* Abre el archivo */
    fichero = fopen(argv[1], "r");

    /* Verifica si el archivo se abrio */
    if(fichero == NULL){

        perror("No se puede abrir fichero");

        exit(EXIT_FAILURE);
    }

    /* Lee el tamaño del vector */
    ret = fscanf(fichero, "%d", &n);

    /* Verifica lectura */
    if(ret != 1){

        fprintf(stderr,
                "No se puede leer tamaño\n");

        fclose(fichero);

        exit(EXIT_FAILURE);
    }

    /* Convierte el numero de hilos */
    nhilos = atoi(argv[2]);

    /* Verifica si el numero de hilos es valido */
    if(nhilos <= 0 || nhilos > n){

        fprintf(stderr,
                "Numero de hilos invalido\n");

        fclose(fichero);

        exit(EXIT_FAILURE);
    }

    /* Reserva memoria para el vector */
    vec = malloc(sizeof(int) * n);

    /* Verifica reserva de memoria */
    if(vec == NULL){

        fprintf(stderr,
                "Error al reservar memoria\n");

        fclose(fichero);

        exit(EXIT_FAILURE);
    }

    /* Lee todos los elementos del archivo */
    for(i = 0; i < n; i++){

        ret = fscanf(fichero, "%d", &vec[i]);

        /* Verifica lectura */
        if(ret != 1){

            fprintf(stderr,
                    "No se puede leer elemento %d\n", i);

            fclose(fichero);

            free(vec);

            exit(EXIT_FAILURE);
        }
    }

    /* Calcula el maximo concurrentemente */
    maximo = maximoValor(vec, n, nhilos);

    /* Muestra el resultado final */
    printf("Maximo: %d\n", maximo);

    /* Libera recursos */
    fclose(fichero);
    free(vec);

    return 0;
}
