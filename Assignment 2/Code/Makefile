CXX=g++
CXXFLAGS=-std=c++11

all: bt matrix

bt: BinTreeImpl.cpp
	$(CXX) $(CXXFLAGS) BTRunner.cpp -o BTRunner.o

matrix: MatrixImpl.cpp
	$(CXX) $(CXXFLAGS) Runner.cpp -o Runner.o

.PHONY: clean
clean:
	rm -f Runner.o BTRunner.o
