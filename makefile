CC = gcc
CFLAGS = -Wall -Wextra

all: T_arvore

T_arvore: main.o arvB.o
	$(CC) $(CFLAGS) -o T_arvore main.o arvB.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

arvB.o: arvB.c arvB.h
	$(CC) $(CFLAGS) -c -o arvB.o arvB.c

clean:
	rm -f T_arvore main.o list.o