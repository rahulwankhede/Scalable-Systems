CXX=g++
CXXFLAGS=-std=c++11 -g
runner.o: MatrixImpl.cpp
	$(CXX) $(CXXFLAGS) Runner.cpp -o Runner.o

.PHONY: clean
clean:
	rm -r Runner.o
