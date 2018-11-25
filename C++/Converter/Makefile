CC=g++
DEBUG=g-
CFLAGS=-std=c++0x -Wall -O3
LFLAGS=
OBJ=main.o Convert.o

all: main clean

main: main.o Convert.o  
	$(CC) $(OBJ) -o test $(CFLAGS)

main.o: ./Source/main.cpp
	$(CC) -c ./Source/main.cpp

Convert.o: ./Source/Convert.cpp
	$(CC) -c ./Source/Convert.cpp

clean: 
	rm *.o
