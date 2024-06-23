CC = g++
CFLAGS = -ggdb3 -O0 -Wall -std=c++11

test_cpu: test_cpu.o
	$(CC) $(CFLAGS) test_cpu.o -o bin/test_cpu

test_decoder: test_decoder.o
	$(CC) $(CFLAGS) test_decoder.o -o bin/test_decoder

test_cpu.o: test/test_cpu.cpp cpu.hpp core.hpp memory.hpp common.hpp decoder.hpp
	$(CC) $(CFLAGS) -c test/test_cpu.cpp

test_decoder.o: test/test_decoder.cpp cpu.hpp core.hpp memory.hpp common.hpp decoder.hpp
	$(CC) $(CFLAGS) -c test/test_decoder.cpp

clean:
	rm -f *.o *.gch bin/test_cpu bin/test_decoder

