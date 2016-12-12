OUTPUT1 = mproc2
OPTS = -g -ggdb -Wall
LIB = -lpthread

$(OUTPUT1) : mproc2.o
	gcc -o $(OUTPUT1) $(OPTS) mproc2.o $(LIB)

mproc2.o : mproc2.c
	gcc -c mproc2.c 

clean :
	rm *.o
