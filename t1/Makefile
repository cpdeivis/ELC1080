CXX = clang
CXXFLAGS = -g -Wall 

all: main

main.o: main.c Frase.h
Frase.o: Frase.c Frase.h

main: main.o Frase.o
	$(CXX) $(CXXFLAGS) -o $@  $^ 

clean:
	rm -f main *.o