CC = gcc -ggdb -std=c99 -Wall -Werror -O3
OUT = file_stats

all:
	$(CC) -o $(OUT) file_stats.c

clean:
	rm -f *.o
	rm -f $(OUT)

run: clean all
	./$(OUT)

rerun: all
	./$(OUT)

valgrind: clean all
	valgrind -v --leak-check=full ./$(OUT)