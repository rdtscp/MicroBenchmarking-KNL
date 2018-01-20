#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int testTSC() {
    volatile uint32_t start_lo, start_hi, end_lo, end_hi;
    volatile uint64_t start, end;
    volatile int temp;
    volatile uint32_t dead;

    __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
    __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
    // Convert to 64 bit ints.
    start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start);
}

int testL1() {
    int L1_DATA[8192];              // 32KB Data Cache => 32768B; 32bit int => (32768 * 8) / 32 elems to fill 32KB Cache

    volatile uint32_t start_lo, start_hi, end_lo, end_hi;
    volatile uint64_t start, end;
    volatile int temp;

    // Get all of L1_DATA into L1 Cache.
    for (int i=0; i < 8192; i++) {
        L1_DATA[i] = 0;
    }

    uint64_t total = 0;
    for (int i=0; i < 1000; i++) {
        __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
        __asm__ __volatile__ ("mfence");
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
        __asm__ __volatile__ ("mfence");
        
        start   =  ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
        end     =  ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
        total += (end - start)/10;
    }

    return total/1000;
}

int main() {
    int total = 0;
    printf(" --- 10 Loads x 1000 --- ");
    printf("\n\tL1 Avg Cycles: %d", testL1());
    // printf("\n\tCycles for RDTSC: %d", testTSC());

    printf("\n\n");
}