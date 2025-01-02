# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall

# Default target
all: program run

program: main.o proje.o
	$(CC) main.o proje.o -o program

main.o: main.c proje.h
	$(CC) $(CFLAGS) -c main.c

proje.o: proje.c proje.h
	$(CC) $(CFLAGS) -c proje.c

clean:
	rm -f *.o program

run:
	./program birimBilgileri.txt calisanBilgileri.txt

