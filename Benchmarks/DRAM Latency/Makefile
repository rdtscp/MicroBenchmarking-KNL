CC = g++
CFLAGS = -O2

all: dram_latency.o


dram_latency.o: prog.cpp
	$(CC) $(CFLAGS) prog.cpp -o dram_latency.o

clean:
	rm -f dram_latency.o