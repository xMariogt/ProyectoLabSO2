#Ejecutar el server

	sudo ./main.o

#En otra terminal hacer la conexion

	telnet localhost 8080

#Listar los puertos abiertos

	sudo lsof -i -P -n | grep LISTEN

#Comando para ejecutar los tests

	locust -f tests/locust_test.py --users 100 --spawn-rate 5 --headless -H http://127.0.0.1:8080 -t 1m --csv=locust_results
