all: avclient

avclient: main.o
	g++ main.o -o client

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o client
