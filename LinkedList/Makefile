CC = gcc -ggdb -std=c99 -Wall -Werror -O3

all: linked_list.o linked_list_test.o
	$(CC) -o linked_list_test linked_list.o linked_list_test.o

linked_list.o:
	$(CC) -c linked_list.c

linked_list_test.o: linked_list.o
	$(CC) -c linked_list_test.c

clean:
	rm *.o

run: all
	./linked_list_test