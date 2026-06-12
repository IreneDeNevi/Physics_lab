CC		= g++
CFLAGS		= --std=c++11 -g -Wall
CFLAGSROOT	= `root-config --cflags`
LIBSROOT	=`root-config --glibs`

all: main

hist.o: hist.cpp
	$(CC) $(CFLAGS) -c hist.cpp      $(CFLAGSROOT)	
main: main.cpp hist.o
	$(CC) $(CFLAGS) -o main main.cpp hist.o $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o
