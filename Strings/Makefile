CC = gcc -ggdb -std=c99 -Wall -Werror -O3
OUT = string_tests

string_tests.o: string_funcs.o
	$(CC) -c string_tests.c

string_funcs.o:
	$(CC) -c string_funcs.c

all: string_tests.o string_funcs.o
	$(CC) -o $(OUT) string_tests.o string_funcs.o

clean:
	rm -f *.o
	rm -f $(OUT)

run: clean all
	./$(OUT)
