OUTPUT1 = ipc_producer2
OUTPUT2 = ipc_consumer2

OPTS = -g -ggdb -Wall

$(OUTPUT1) : ipc_producer2.o
	gcc -o $(OUTPUT1) ipc_producer2.o
$(OUTPUT2) : ipc_consumer2.o
	gcc -o $(OUTPUT2) ipc_consumer2.o

ipc_producer2.o : ipc_producer2.c
	gcc -c ipc_producer2.c
ipc_consumer2.o : ipc_consumer2.c
	gcc -c ipc_consumer2.c
