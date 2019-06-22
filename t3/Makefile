CXX = clang
CXXFLAGS = -g -Wall -pthread

all: dce

dce.o: dce.c

dce: dce.o
	$(CXX) $(CXXFLAGS) -o $@  $^


clean:
	rm -f dce *.o
