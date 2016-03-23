CC=gcc
CPP=g++
FLAGS=-fopenmp -Wall

all: gameoflife integral mergesort pi

gameoflife: gameoflife.c
	${CC} -o gameoflife gameoflife.c ${FLAGS}

integral: integral.cpp
	${CPP} -o integral integral.cpp ${FLAGS}

mergesort: mergesort.c
	${CC} -o mergesort mergesort.c ${FLAGS}

pi: pi.c
	${CC} -o pi pi.c ${FLAGS} -lm

run: gameoflife integral mergesort pi
	./gameoflife 100 50 50
	./integral 10000
	./mergesort 100000
	./pi 1000000

clean:
	rm gameoflife integral mergesort pi
