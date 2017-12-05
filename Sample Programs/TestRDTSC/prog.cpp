#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

cpu_set_t mask;

static inline uint64_t test_rdtsc() {    
    uint64_t a;
    uint64_t b;
    uint64_t out;
    asm("rdtscp" : "=A"(a));
    asm("rdtscp" : "=A"(b));
    out = b - a;
    return out;
}

inline void assignToCore(int core_id) {
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

int main() {
    assignToCore(0);
    for (int i = 0; i < 100; i++) {
        printf("%" PRIu64 "\n", test_rdtsc());
    }
}

/*
    Working from Linux.

*/