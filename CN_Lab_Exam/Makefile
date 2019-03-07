output: client.o server.o server1.o server2.o
	g++ client.o -o client -lpthread
	g++ server.o -o server -lpthread
	g++ server1.o -o server1 -lpthread
	g++ server2.o -o server2 -lpthread 

main.o: client.cpp server.cpp server1.cpp server2.cpp
	g++ -c client.cpp server.cpp server1.cpp server2.cpp

clean:
	rm *.o client server server1 server2