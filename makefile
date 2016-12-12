OUTPUT1 = ipc_producer3
OUTPUT2 = ipc_consumer3

OPTS = -g -ggdb -Wall

$(OUTPUT1) : ipc_producer3.o
	gcc -o $(OUTPUT1) ipc_producer3.o
$(OUTPUT2) : ipc_consumer3.o
	gcc -o $(OUTPUT2) ipc_consumer3.o

ipc_producer3.o : ipc_producer3.c
	gcc -c ipc_producer3.c
ipc_consumer3.o : ipc_consumer3.c
	gcc -c ipc_consumer3.c
