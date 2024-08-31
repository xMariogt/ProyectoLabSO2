dependencies = lib/server_functions.c lib/log.c

target: main.o

%.o: %.c $(dependencies)
	gcc -o $@ $^