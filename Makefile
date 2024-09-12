dependencies = lib/*.c 

target: main.o

%.o: %.c $(dependencies)
	gcc -o $@ $^