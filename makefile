ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	gcc -o prog main.o

run:
	./prog

main.o: main.c
	gcc -c main.c

clean:
	rm *.o prog
