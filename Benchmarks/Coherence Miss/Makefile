CC = g++

all: coherence_latencies.o


coherence_latencies.o: prog.cpp
	$(CC) prog.cpp -std=c++0x -pthread -o coherence_latencies.o

clean:
	rm -f coherence_latencies.o