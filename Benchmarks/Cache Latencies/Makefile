CC = g++
CFLAGS = -O2

all: cache_latencies.o


cache_latencies.o: prog.cpp
	$(CC) $(CFLAGS) prog.cpp -o cache_latencies.o

clean:
	rm -f cache_latencies.o