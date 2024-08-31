#Ejecutar el server

	sudo ./main.o

#En otra terminal hacer la conexion

	telnet localhost 13

#Listar los puertos abiertos

	sudo lsof -i -P -n | grep LISTEN
