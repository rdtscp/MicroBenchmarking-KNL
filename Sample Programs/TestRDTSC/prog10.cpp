#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




int L1_DATA[8192];              // 32KB Data Cache => 32768B; 32bit int => (32768 * 8) / 32 elems to fill 32KB Cache

volatile uint32_t start_lo, start_hi, end_lo, end_hi;
volatile int temp;

int testTSC() {
    __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
    __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start)/10;
}

int testL1() {
    // Get all of L1_DATA into L1 Cache.
    for (int i=0; i < 8192; i++) {
        L1_DATA[i] = 0;
    }

    __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
    temp = L1_DATA[0];
    temp = L1_DATA[1];
    temp = L1_DATA[2];
    temp = L1_DATA[3];
    temp = L1_DATA[4];
    temp = L1_DATA[5];
    temp = L1_DATA[6];
    temp = L1_DATA[7];
    temp = L1_DATA[8];
    temp = L1_DATA[9];
    __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));

    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start)/100;
}

int main() {
    int total = 0;
    printf("\n\tL1 Avg Cycles: %d", testL1());
    printf("\n\tCycles for RDTSC: %d", testTSC());
}