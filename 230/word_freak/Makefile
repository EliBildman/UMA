CC = gcc

all: main.o words.o freaker.o
	${CC} -o freak main.o words.o freaker.o
	make clean

main.o: main.c
	${CC} -c main.c

words.o: words.c words.h
	${CC} -c words.c

freaker.o: freaker.c freaker.h
	${CC} -c freaker.c

clean:
	rm *.o