CC=gcc
FLAGS=-ansi -pedantic -Wall -O3

all : gol.o main.o
	${CC} ${FLAGS} -o gol gol.o main.o

time : all
	time ./gol

gol.o :
	${CC} ${FLAGS} -c gol.c

main.o :
	${CC} ${FLAGS} -c main.c

clean :
	rm -f gol *.o
