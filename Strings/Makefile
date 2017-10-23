CC = gcc -ggdb -std=c99 -Wall -Werror -O3

all: string_tests.o string_funcs.o alias.o python.o io.o
	$(CC) -o string_tests string_tests.o string_funcs.o alias.o python.o io.o

string_tests.o: string_funcs.o
	$(CC) -c string_tests.c string_funcs.h

string_funcs.o:
	$(CC) -c string_funcs.c

alias.o: io.o fb.h
	$(CC) -c alias.c io.h fb.h

python.o: io.o fb.h
	$(CC) -c python.c io.h fb.h

io.o:
	$(CC) -c io.c

clean:
	rm *.o

run: all
	./string_tests
