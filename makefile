OUTPUT1 = ipc_producer
OUTPUT2 = ipc_consumer

OPTS = -g -ggdb -Wall

$(OUTPUT1) : ipc_producer.o
	gcc -o $(OUTPUT1) ipc_producer.o
$(OUTPUT2) : ipc_consumer.o
	gcc -o $(OUTPUT2) ipc_consumer.o

ipc_producer.o : ipc_producer.c
	gcc -c ipc_producer.c
ipc_consumer.o : ipc_consumer.c
	gcc -c ipc_consumer.c
