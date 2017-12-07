#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

cpu_set_t mask;

int data_arr[4096];

void init() {
    for (int i = 0; i < 4096; i++) {
        data_arr[i] = 1;
    }
}

inline void assignToCore(int core_id) {
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

uint64_t rdtscp() {
    uint64_t a;
    uint64_t b;
    asm volatile("rdtscp" : "=A"(a));
    asm volatile("rdtscp" : "=A"(b));
    return (b - a);
}

int testL1() {
    volatile int temp = 0;
    uint64_t a;
    uint64_t b;
    uint64_t out;
    for (int i = 0; i < 16; i++) {
        temp = data_arr[i];
    }
    asm volatile("rdtscp" : "=A"(a));
    temp = data_arr[0];                     // This value has already been fetched in above loop, so should exist in L1 Cache
    asm volatile("rdtscp" : "=A"(b));
    out = b - a;
    return out;
}

int main() {    
    uint64_t rdtscpOverhead = 0;
    uint64_t testL1_Avg     = 0;

    init();    

    assignToCore(0);

    // Get Average Cycle cost of RDTSCP
    int rdtscpTests = 1000000;      // 1 Million
    for (int i = 0; i < rdtscpTests; i++) {
        rdtscpOverhead += rdtscp();
    }
    rdtscpOverhead = rdtscpOverhead / rdtscpTests;

    // Test L1 Cache Hit
    int cacheL1Tests = 1000000;     // 1 Million
    for (int i = 0; i < cacheL1Tests; i++) {
        testL1_Avg += testL1();
    }
    testL1_Avg = testL1_Avg / cacheL1Tests;

    printf(" --- CYCLES ---\n");
    printf("RDTSCP Overhead:\t%d\n", rdtscpOverhead);
    printf("L1 Cache Hit:\t\t%d\n", testL1_Avg);
}