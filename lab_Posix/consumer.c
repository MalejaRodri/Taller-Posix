/***************************************************************************
*
*	Pontificia Universidad Javeriana
*	Maria Alejandra Rodriguez
*
*	19/05/2026
*
*	Definición:
*	-Implementa el proceso consumidor del modelo productor-consumidor.
*	-Lee datos desde una memoria compartida.
*	-Consume los elementos generados por el productor.
*	-Usa semáforos POSIX para sincronización.
*	-Espera cuando el buffer está vacío.
*	-Libera espacios del buffer después de consumir.
*	-Utiliza un buffer circular para leer los datos.
*	-Elimina los recursos compartidos al finalizar:
*		-semáforos
*		-memoria compartida.
*
************************************************************************/

#include"common.h"

int main() {

    /* Se abren los semaforos creados por el productor */
    sem_t *vacio = sem_open("/vacio", 0);
    sem_t *lleno = sem_open("/lleno", 0);

    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    /* Se abre la memoria compartida */
    int fd_compartido = shm_open("/memoria_compartida", O_RDWR, 0644);

    if (fd_compartido < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    /* Se mapea la memoria compartida */
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos),
                                      PROT_READ | PROT_WRITE,
                                      MAP_SHARED, fd_compartido, 0);

    /* Inicializa la posicion de salida del consumidor */
    compartir->salida = 0;

    /* El consumidor toma 10 elementos */
    for (int i = 1; i <= 10; i++) {

        /* Espera si el buffer esta vacio */
        sem_wait(lleno);

        /* Extrae el dato del buffer */
        int item = compartir->bus[compartir->salida];

        printf("Consumidor: Consume %d\n", item);

        /* Avanza circularmente la posicion de salida */
        compartir->salida = (compartir->salida + 1) % BUFFER;

        /* Avisa que hay un espacio libre */
        sem_post(vacio);

        sleep(2);
    }

    /* Libera recursos */
    munmap(compartir, sizeof(compartir_datos));
    close(fd_compartido);
    sem_close(vacio);
    sem_close(lleno);

    /* Elimina semaforos y memoria compartida */
    sem_unlink("/vacio");
    sem_unlink("/lleno");
    shm_unlink("/memoria_compartida");

    return 0;
}
