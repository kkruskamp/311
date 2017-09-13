CC = g++
CFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

sspapp: sspapp.o graph.o minpriority.o
	$(CC) $(LDFLAGS) sspapp.o graph.o minpriority.o -o sspapp

sspapp.o: sspapp.cpp graph.h
	$(CC) $(CFLAGS) sspapp.cpp

graph.o: graph.cpp graph.h minpriority.h
	$(CC) $(CFLAGS) graph.cpp

minpriority.o: minpriority.cpp minpriority.h
	$(CC) $(CFLAGS) minpriority.cpp

main: main.cpp minpriority.o
	$(CC) $(LDFLAGS) main.cpp minpriority.o -o main
    
clean:
	rm *.o sspapp
