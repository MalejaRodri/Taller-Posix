all: producer consumer posixSincro concurrenciaPosix

producer: producer.c common.h
	gcc producer.c -o producer -pthread -lrt

consumer: consumer.c common.h
	gcc consumer.c -o consumer -pthread -lrt

posixSincro: posixSincro.c common.h
	gcc posixSincro.c -o posixSincro -pthread

concurrenciaPosix: concurrenciaPosix.c common.h
	gcc concurrenciaPosix.c -o concurrenciaPosix -pthread

run-producer:
	./producer

run-consumer:
	./consumer

run-sincro:
	./posixSincro

run-concurrencia:
	./concurrenciaPosix datos.txt 3

clean:
	rm -f producer consumer posixSincro concurrenciaPosix

clean-posix:
	rm -f /dev/shm/memoria_compartida
	rm -f /dev/shm/sem.vacio
	rm -f /dev/shm/sem.lleno

rebuild: clean all
