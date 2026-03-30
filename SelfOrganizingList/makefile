CXX = g++
CXXFLAGS = -Wall -std=c++17

all: module demo test

# a) build module.o from .h and .cpp
module: SelfOrganizingList.cpp SelfOrganizingList.h
	$(CXX) $(CXXFLAGS) -c SelfOrganizingList.cpp -o SelfOrganizingList.o

# b) build demo
demo: module demo.cpp
	$(CXX) $(CXXFLAGS) SelfOrganizingList.o demo.cpp -o demo

# c) run demo
run_demo: demo
	./demo

# d) build test
test: module test.cpp
	$(CXX) $(CXXFLAGS) SelfOrganizingList.o test.cpp -o test

# e) run test
run_test: test
	./test

# f) clean everything
clean:
	rm -f *.o demo test log.txt

# g) rebuild from scratch
rebuild: clean module demo test