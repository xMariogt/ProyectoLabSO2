#Ejecutar el server

	sudo ./main.o

#En otra terminal hacer la conexion

	telnet localhost 13

#Listar los puertos abiertos

	sudo lsof -i -P -n | grep LISTEN

#Para probar conexion de navegador
	##Desde Terminal
	curl "http://127.0.0.1:13/?message=HolaServidor"

	##Desde FireFox
	buscar => about:config 

	Luego buscar => network.security.ports.banned.override

	Establecerlo como tipo Texto y agregar el puerto a utilizar, 13 en este caso
	


