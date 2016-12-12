OUTPUT1 = mproc3
OPTS = -g -ggdb -Wall
LIB = -lpthread

$(OUTPUT1) : mproc3.o
	gcc -o $(OUTPUT1) $(OPTS) mproc3.o $(LIB)

mproc3.o : mproc3.c
	gcc -c mproc3.c 

clean :
	rm *.o
