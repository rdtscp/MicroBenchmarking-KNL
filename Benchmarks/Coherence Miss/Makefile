CC = g++

all: coherence_latencies.o


coherence_latencies.o: prog.cpp
	$(CC) prog.cpp -o coherence_latencies.o -pthread -std=c++11

clean:
	rm -f coherence_latencies.o
