README - Taller POSIX: Semáforos, Hilos y Concurrencia
Sistemas Operativos
Taller POSIX – Concurrencia y Sincronización en Linux

Pontificia Universidad Javeriana

Descripción General

Este taller tiene como objetivo implementar y comprender mecanismos de concurrencia y sincronización en sistemas operativos Linux utilizando programación en C bajo el estándar POSIX.

Durante el desarrollo del taller se implementaron diferentes soluciones concurrentes aplicando conceptos fundamentales como:

procesos,
hilos POSIX,
memoria compartida,
semáforos,
mutex,
variables de condición,
buffers compartidos,
y el modelo productor-consumidor.

El proyecto se desarrolló completamente sobre Linux utilizando herramientas POSIX para la gestión y sincronización de recursos concurrentes.

Estructura del Proyecto
.
├── producer.c
├── consumer.c
├── posixSincro.c
├── concurrenciaPosix.c
├── posix.h
├── Makefile
└── README.md
Actividad 1 – Productor–Consumidor con Semáforos POSIX
Descripción

En esta actividad se implementó el modelo productor-consumidor utilizando procesos independientes sincronizados mediante semáforos POSIX y memoria compartida.

El productor genera datos y los almacena en un buffer compartido, mientras que el consumidor consume dichos datos de manera sincronizada.

Archivos
producer.c

Proceso encargado de producir y almacenar datos en memoria compartida.

consumer.c

Proceso encargado de consumir los datos almacenados por el productor.

posix.h

Archivo de cabecera compartido que contiene:

librerías POSIX,
constantes globales,
estructuras compartidas.
Conceptos implementados
shm_open()
mmap()
sem_open()
sem_wait()
sem_post()
buffer circular
sincronización entre procesos
comunicación IPC
Actividad 2 – Hilos POSIX y Concurrencia
Descripción

En esta actividad se implementaron soluciones concurrentes utilizando hilos POSIX (pthread) para demostrar sincronización y procesamiento paralelo dentro de un mismo proceso.

Archivo: posixSincro.c

Implementa el modelo productor-consumidor utilizando:

múltiples hilos productores,
un hilo consumidor (spooler),
buffer compartido sincronizado.

Los productores generan mensajes concurrentemente y el spooler consume e imprime los mensajes almacenados.

Conceptos implementados
pthread_create()
pthread_join()
pthread_mutex_lock()
pthread_mutex_unlock()
pthread_cond_wait()
pthread_cond_signal()
Complemento – Procesamiento Concurrente
Archivo: concurrenciaPosix.c

Este programa implementa procesamiento paralelo utilizando múltiples hilos POSIX para buscar el valor máximo de un vector de manera concurrente.

Cada hilo procesa una parte diferente del vector y calcula un máximo parcial. Finalmente, el hilo principal reúne los resultados parciales y obtiene el máximo global.

Conceptos implementados
paralelismo de datos
división de trabajo entre hilos
procesamiento concurrente
sincronización de hilos
uso de estructuras compartidas
Archivo posix.h

El archivo posix.h centraliza:

librerías necesarias,
constantes globales,
estructuras compartidas utilizadas por todos los programas.

Esto permite mantener una arquitectura modular y reutilizable dentro del proyecto.

Makefile

El proyecto incluye un Makefile que automatiza:

compilación,
ejecución,
limpieza de ejecutables,
y reconstrucción completa del proyecto.
Compilación
Compilar todo el proyecto
make

o:

make all
Ejecución
Actividad 1

Abrir dos terminales.

Terminal 1
./producer
Terminal 2
./consumer
Actividad 2
./posixSincro
Procesamiento Concurrente
./concurrenciaPosix datos.txt 3
Limpieza
Eliminar ejecutables
make clean
Recompilar todo
make rebuild
Resultados

Con el desarrollo de este taller se logró implementar correctamente:

sincronización entre procesos,
comunicación mediante memoria compartida,
concurrencia con hilos POSIX,
exclusión mutua,
buffers compartidos,
procesamiento paralelo,
y el modelo productor-consumidor.
Conclusiones
Se aplicaron de manera práctica conceptos fundamentales de Sistemas Operativos relacionados con concurrencia y sincronización.
Se comprendió el funcionamiento de semáforos POSIX, mutex y variables de condición.
Se evidenció la importancia de proteger recursos compartidos para evitar condiciones de carrera.
Se fortalecieron habilidades en programación concurrente utilizando herramientas POSIX sobre Linux.
