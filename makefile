OUTPUT1 = ipc_producer4
OUTPUT2 = ipc_consumer4

OPTS = -g -ggdb -Wall

$(OUTPUT1) : ipc_producer4.o
	gcc -o $(OUTPUT1) ipc_producer4.o
$(OUTPUT2) : ipc_consumer4.o
	gcc -o $(OUTPUT2) ipc_consumer4.o

ipc_producer4.o : ipc_producer4.c
	gcc -c ipc_producer4.c
ipc_consumer4.o : ipc_consumer4.c
	gcc -c ipc_consumer4.c
