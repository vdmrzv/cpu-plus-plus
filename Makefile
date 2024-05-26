CC = g++
CFLAGS = -ggdb3 -O0 -Wall -std=c++11

vcpu: main.o
	$(CC) $(CFLAGS) main.o -o bin/vcpu

main.o: main.cpp cpu.hpp memory.hpp global.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o *.gch bin/vcpu

