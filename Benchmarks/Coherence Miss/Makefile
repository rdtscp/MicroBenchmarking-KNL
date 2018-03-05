CC = g++

all: coherence_latencies.o


coherence_latencies.o: prog.cpp
	$(CC) prog.cpp -pthread -o coherence_latencies.o -std=c++14

clean:
	rm -f coherence_latencies.o