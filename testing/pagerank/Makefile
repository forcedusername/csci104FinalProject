# Name: Ani Ramchandran
# random makefile

CC = g++
CFLAGS = -g -Wall -Ilib/ -I.
LDFLAGS =

#searchAppMain.o 
all : pageRankTest.o webpageSTL.o 
	@echo "Building pageRankTest.o webpageSTL.o "
	@echo "Compiling and linking"
	$(CC) $(CFLAGS)  bin/pageRankTest.o bin/webpageSTL.o -o bin/search 
	
	#bin/searchAppMain.o
#searchAppMain.o : searchAppMain.cpp/
#	$(CC) $(CFLAGS) -c searchAppMain.cpp -o bin/searchAppMain.o
	
pageRankTest.o : pageRankTest.cpp
	$(CC) $(CFLAGS) -c pageRankTest.cpp -o bin/pageRankTest.o

webpageSTL.o : webpageSTL.cpp
	$(CC) $(CFLAGS) -c webpageSTL.cpp -o bin/webpageSTL.o


clean:
	rm -f bin/search bin/*.o *~
