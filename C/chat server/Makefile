CC = gcc
CFLAGS = -Wall -O3
BIN_DIR = bin

all: server

server: server.c
	$(CC) $(CFLAGS) server.c -o $(BIN_DIR)/server

clean:
	rm $(BIN_DIR)/server
