CC = gcc -ggdb -std=c99 -Wall -Werror -O3
NO_BUG = gcc_strncpy_bypass_bug
HAS_BUG = gcc_strncpy_cause_bug

no_bug:
	$(CC) -o $(NO_BUG) gcc_strncpy_bypass_bug.c

has_bug:
	$(CC) -o $(HAS_BUG) gcc_strncpy_cause_bug.c

clean:
	rm -f *.o
	rm -f $(NO_BUG)
	rm -f $(HAS_BUG)

run: no_bug
	./$(NO_BUG) 3
	./$(NO_BUG) 10

	echo "The following will cause the bug:"

	make has_bug
	./$(HAS_BUG)

