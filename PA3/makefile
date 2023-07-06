# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c -std=c++11
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O3 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: dsu.o main.o
			$(CC) $(OPTFLAGS) dsu.o main.o -o bin/cb
main.o 	: src/main.cpp src/dsu.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
dsu.o	: src/dsu.cpp src/dsu.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/* outputs/*

run: 	
	./bin/cb ./inputs/public_case_1.in ./outputs/public_case_1.out
	./bin/cb ./inputs/public_case_2.in ./outputs/public_case_2.out
	./bin/cb ./inputs/public_case_3.in ./outputs/public_case_3.out
	./bin/cb ./inputs/public_case_4.in ./outputs/public_case_4.out
	./bin/cb ./inputs/public_case_7.in ./outputs/public_case_7.out
	./bin/cb ./inputs/public_case_8.in ./outputs/public_case_8.out