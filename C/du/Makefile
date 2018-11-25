CC = gcc
CFLAGS = -std=c99 -Wall -O3 -D _XOPEN_SOURCE

all: du

du: du.c
	$(CC) $(CFLAGS) du.c -o bin/du

clean:
	rm du
