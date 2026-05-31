CC=gcc
FLAGS=-ansi -pedantic -Wall -O3

all : gol64.o main.o
	${CC} ${FLAGS} -o gol64 gol64.o main.o

time : all
	time ./gol64

gol64.o :
	${CC} ${FLAGS} -c gol64.c

main.o :
	${CC} ${FLAGS} -c main.c

clean :
	rm -f gol64 *.o
