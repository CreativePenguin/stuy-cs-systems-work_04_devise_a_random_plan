ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o prog main.o

run:
	./prog

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o prog
