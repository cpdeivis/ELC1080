CXX = clang
CXXFLAGS = -g -Wall 

all: main

main.o: main.c
#header.o: header.c header.h

main: main.o
	$(CXX) $(CXXFLAGS) -o $@  $^ 

clean:
	rm -f main *.o