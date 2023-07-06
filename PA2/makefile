.PHONY: run clean

mps: src/mps.cpp
	g++  -std=c++11 -O2 -o ./bin/mps ./src/mps.cpp
run:
	./bin/mps inputs/12.in outputs/12.out
	./bin/mps inputs/1000.in outputs/1000.out
	./bin/mps inputs/10000.in outputs/10000.out
clean:
	rm -rf  bin/* outputs/*