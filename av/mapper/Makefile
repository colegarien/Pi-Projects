all: avmapper

avmapper: main.o wind_util.o pic_window.o tool_window.o
	g++ main.o wind_util.o pic_window.o tool_window.o -o avmap -lncurses

main.o: main.cpp
	g++ -c main.cpp

wind_util.o: wind_util.cpp
	g++ -c wind_util.cpp

pic_window.o: pic_window.cpp
	g++ -c pic_window.cpp

tool_window.o: tool_window.cpp
	g++ -c tool_window.cpp

clean:
	rm *.o avmap
