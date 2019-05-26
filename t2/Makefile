CXX = clang
CXXFLAGS = -g -Wall -lcurl

all: Sete_Cliques_serial

Sete_Cliques_serial.o: Sete_Cliques_serial.c curl_code.h
curl_code.o: curl_code.c curl_code.h

Sete_Cliques_serial: Sete_Cliques_serial.o curl_code.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f Sete_Cliques_serial *.o
