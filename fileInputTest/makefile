CC=g++
CFLAGS=-g -Wall -std=c++11

all: fileInput

fileInput : fileInput.cpp
	$(CC) $(CFLAGS) fileInput.cpp -o fileInput
	
.PHONY : clean

clean :
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~