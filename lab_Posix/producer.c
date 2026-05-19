/******************************************
*
*	Pontificia Universidad Javeriana
*
*	 Maria Alejandra Rodriguez
*
*		19/05/2026
*
*	Descripción :
*	-Implementa concurrencia mediante hilos POSIX.
*	-Simula el modelo productor-consumidor.
*	-Usa un buffer compartido para intercambiar datos.
*	-Sincroniza el acceso al buffer usando mutex y variables de condición.
*	-Evita condiciones de carrera entre múltiples hilos.
*	-Los productores generan datos y el spooler los consume e imprime.
*
*******************************************/


#include"common.h"

int main() {

	/*Manejo de semaforos dependiendo el buffer*/
    sem_t *vacio = sem_open("/vacio", O_CREAT, 0644, BUFFER);
    sem_t *lleno = sem_open("/lleno", O_CREAT, 0644, 0);

	/*Error al uso del semaforo cuando el buffer esta lleno*/
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open"); //semaforo esperando el paso habilitado
        exit(EXIT_FAILURE);
    }
	/*semaforo abierto para la memoria compatrtida dentro del buffer*/
    int shm_fd = shm_open("/memoria_compartida", O_CREAT | O_RDWR, 0644);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
	//Alteracion de tamaño de la memoria compartida que tienen los semaforos
    ftruncate(shm_fd, sizeof(compartir_datos));
	/*Se comparten los datos por medio del direccionamiento del espacio en memoria*/
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    compartir->entrada = 0;

	/*Bucle de repeticion en para compartir la entrada del productor*/
    for (int i = 1; i <= 10; i++){
        sem_wait(vacio);
        compartir->bus[compartir->entrada] = i;
        printf("Productor: Produce%d\n", i);
        compartir->entrada = (compartir->entrada+1) % BUFFER;
        sem_post(lleno); /*realizar esto hasta que el productor del buffer esta completo*/
        sleep(1);
    }
	/*Eliminar el mapeo en memoria que se realizo al compartir los datos */
    munmap(compartir, sizeof(compartir_datos));//recolecta el tamaño que principalmente calculo
    close(shm_fd);
    sem_close(vacio);
	sem_unlink("/vacio");
    shm_unlink("/memoria_compartida"); //la memoria que se compartio entre los hilos del proceso en el semaforo 
    return 0;
}
