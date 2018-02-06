CC = g++
CFLAGS = -O2

all: mcdram_latency.o


mcdram_latency.o: prog.cpp
	$(CC) $(CFLAGS) prog.cpp -o mcdram_latency.o

clean:
	rm -f mcdram_latency.o