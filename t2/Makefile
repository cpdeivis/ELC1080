CXX = clang
CXXFLAGS = -g -Wall -lcurl -pthread

all: serial thread

Sete_Cliques_threads.o: Sete_Cliques_threads.c curl_code.h
Sete_Cliques_serial.o: Sete_Cliques_serial.c curl_code.h
curl_code.o: curl_code.c curl_code.h

serial: Sete_Cliques_serial.o curl_code.o
	$(CXX) $(CXXFLAGS) -o $@  $^

thread: Sete_Cliques_threads.o curl_code.o
	$(CXX) $(CXXFLAGS) -o $@  $^

clean:
	rm -f serial *.o
	rm -f thread *.o
