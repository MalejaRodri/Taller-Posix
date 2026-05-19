# 🚀 Taller POSIX - Concurrencia y Sincronización en Linux

<div align="center">

![Linux](https://img.shields.io/badge/Linux-POSIX-black?style=for-the-badge&logo=linux)
![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Threads](https://img.shields.io/badge/Pthreads-Concurrency-green?style=for-the-badge)
![IPC](https://img.shields.io/badge/IPC-Semaphores%20%26%20Shared%20Memory-orange?style=for-the-badge)

### 🖥️ Sistemas Operativos – Pontificia Universidad Javeriana

Implementación de mecanismos de concurrencia y sincronización utilizando herramientas POSIX en Linux.

</div>

---

# 📌 Descripción General

Este proyecto tiene como objetivo implementar y comprender conceptos fundamentales de concurrencia y sincronización en sistemas operativos Linux utilizando programación en C bajo el estándar POSIX.

A lo largo del taller se desarrollaron diferentes soluciones concurrentes aplicando:

- 🔄 Productor–Consumidor
- 🧵 Hilos POSIX (`pthread`)
- 🔒 Mutex y Variables de Condición
- 📡 Comunicación entre Procesos (IPC)
- 🧠 Memoria Compartida
- 🚦 Semáforos POSIX
- ⚡ Procesamiento Paralelo

---

# 📂 Estructura del Proyecto

```bash
.
├── producer.c
├── consumer.c
├── posixSincro.c
├── concurrenciaPosix.c
├── posix.h
├── Makefile
└── README.md
```

---

# 🧩 Actividad 1 – Productor–Consumidor con Semáforos POSIX

## 📖 Descripción

Se implementó el modelo clásico **Productor–Consumidor** utilizando:

- procesos independientes,
- memoria compartida POSIX,
- semáforos con nombre,
- buffers circulares.

El productor genera datos y los almacena en memoria compartida, mientras que el consumidor consume dichos elementos de forma sincronizada.

---

## 📁 Archivos

| Archivo | Descripción |
|---|---|
| `producer.c` | Genera y almacena datos |
| `consumer.c` | Consume los datos generados |
| `posix.h` | Librerías, constantes y estructuras compartidas |

---

## ⚙️ Tecnologías Implementadas

```bash
shm_open()
mmap()
sem_open()
sem_wait()
sem_post()
```

---

## 🧠 Conceptos Aplicados

- Comunicación entre procesos (IPC)
- Memoria compartida POSIX
- Semáforos POSIX
- Exclusión mutua
- Sincronización
- Buffer circular

---

# 🧵 Actividad 2 – Hilos POSIX y Concurrencia

## 📖 Descripción

Se implementaron soluciones concurrentes utilizando hilos POSIX (`pthread`) para demostrar procesamiento paralelo y sincronización dentro de un mismo proceso.

---

# 📁 posixSincro.c

Este programa implementa nuevamente el modelo **Productor–Consumidor**, pero utilizando:

- múltiples hilos productores,
- un hilo consumidor (spooler),
- un buffer compartido sincronizado.

Los productores generan mensajes concurrentemente mientras el spooler consume e imprime los datos.

---

## ⚙️ Funciones POSIX Utilizadas

```bash
pthread_create()
pthread_join()
pthread_mutex_lock()
pthread_mutex_unlock()
pthread_cond_wait()
pthread_cond_signal()
```

---

## 🧠 Conceptos Aplicados

- Programación multihilo
- Sincronización entre hilos
- Mutex POSIX
- Variables de condición
- Condiciones de carrera
- Buffer compartido

---

# ⚡ Procesamiento Concurrente – concurrenciaPosix.c

## 📖 Descripción

Como complemento del taller se implementó un sistema de procesamiento paralelo utilizando múltiples hilos POSIX para buscar concurrentemente el valor máximo de un vector.

Cada hilo procesa una parte diferente del vector y calcula un máximo parcial. Finalmente, el hilo principal reúne los resultados y obtiene el máximo global.

---

## 🧠 Conceptos Aplicados

- Paralelismo de datos
- División de trabajo entre hilos
- Procesamiento concurrente
- Coordinación de hilos POSIX

---

# 📚 Archivo Compartido – posix.h

El archivo `posix.h` centraliza:

- librerías POSIX,
- constantes globales,
- estructuras compartidas,
- configuraciones comunes del proyecto.

Esto permite mantener una arquitectura modular y reutilizable.

---

# 🛠️ Makefile

El proyecto incluye un `Makefile` que automatiza:

- compilación,
- limpieza,
- reconstrucción,
- ejecución de programas.

---

# ⚙️ Compilación

## Compilar todo el proyecto

```bash
make
```

o:

```bash
make all
```

---

# ▶️ Ejecución

# Actividad 1

## Terminal 1

```bash
./producer
```

## Terminal 2

```bash
./consumer
```

---

# Actividad 2

```bash
./posixSincro
```

---

# Procesamiento Concurrente

```bash
./concurrenciaPosix datos.txt 3
```

---

# 🧹 Limpieza

## Eliminar ejecutables

```bash
make clean
```

---

## Reconstruir todo el proyecto

```bash
make rebuild
```

---

# 📊 Resultados Obtenidos

✅ Sincronización correcta entre procesos  
✅ Comunicación mediante memoria compartida  
✅ Implementación funcional de semáforos POSIX  
✅ Programación concurrente con hilos POSIX  
✅ Exclusión mutua mediante mutex  
✅ Procesamiento paralelo de datos  
✅ Implementación del modelo productor–consumidor  

---

# 🧠 Conclusiones

- Se aplicaron conceptos fundamentales de Sistemas Operativos relacionados con concurrencia y sincronización.
- Se comprendió el funcionamiento de mecanismos POSIX en Linux.
- Se implementaron arquitecturas concurrentes seguras y sincronizadas.
- Se reforzó el uso práctico de procesos, hilos y comunicación IPC.

---

# 👨‍💻 Autor(es)

**Pontificia Universidad Javeriana**  
Materia: Sistemas Operativos  
Taller POSIX – Concurrencia y Sincronización en Linux
