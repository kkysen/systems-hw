CC = gcc -ggdb -std=c99 -Wall -Werror -O3 -pthread
CONTROL_OUT = control
CLIENT_OUT = client

util/utils.o:
	$(CC) -c util/utils.c -o util/utils.o

util/string_builder.o:
	$(CC) -c util/string_builder.c -o util/string_builder.o

util/stacktrace.o:
	$(CC) -c util/stacktrace.c -o util/stacktrace.o

util/resource_utils.o:
	$(CC) -c util/resource_utils.c -o util/resource_utils.o

util/io_utils.o:
	$(CC) -c util/stacktrace.c -o util/stacktrace.o

util/ipc_utils.o:
	$(CC) -c util/ipc_utils.c -o util/ipc_utils.o

$(CONTROL_OUT).o:
	$(CC) -c $(CONTROL_OUT).c

$(CLIENT_OUT).o:
	$(CC) -c $(CLIENT_OUT).c

DEPENDENCIES = util/stacktrace.o util/string_builder.o util/utils.o util/resource_utils.o util/io_utils.o util/ipc_utils.o

all: clean $(CONTROL_OUT).o $(CLIENT_OUT).o $(DEPENDENCIES)
	$(CC) -o $(OUT) $(OUT).o $(DEPENDENCIES)
	$(CC) -o $(OUT) $(OUT).o $(DEPENDENCIES)

clean:
	touch dummy.o
	find . -name '*.o' -delete
	rm -f $(OUT)

install: clean all

run: install
	./$(OUT)

rerun: all
	./$(OUT)

valgrind: clean all
	valgrind -v --leak-check=full ./$(OUT)

