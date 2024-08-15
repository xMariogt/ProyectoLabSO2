dependencies = lib/server_functions.c

target: main.o

%.o: %.c $(dependencies)
	gcc -o $@ $^