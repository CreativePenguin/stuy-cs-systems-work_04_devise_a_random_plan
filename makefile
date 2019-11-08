all: main.o
	gcc -o prog main.o

run:
	./prog

main.o: main.c
	gcc -c main.c

clean:
	rm *.o prog
