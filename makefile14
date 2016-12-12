OUTPUT = elfreader

OPTS = -g -ggdb -Wall
$(OUTPUT) : elfreader.o util.o main.o
	gcc -o $(OUTPUT) main.o elfreader.o util.o

clean :
	rm *.o
	rm $(OUTPUT)

			   
main.o : main.c util.o elfreader.o
	gcc -c main.c
elfreader.o : elfreader.c elfreader.h
	gcc -c elfreader.c
util.o : util.c util.h
	gcc -c util.c


