#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int testTSC() {
    volatile uint32_t start_lo, start_hi, end_lo, end_hi;
    volatile int temp;
    volatile uint32_t dead;
    __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
    __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start);
}

void confuseCache(uint64_t cache_size) {
    int num_elems = cache_size / 32;
    int dead_data[num_elems];
    for (int i=0; i < num_elems; i++) {
        dead_data[i] = rand();
    }
}

int testL1() {
    int L1_DATA[8192];              // 32KB Data Cache => (32 * 1024 * 8) / 4
    volatile uint32_t start_lo, start_hi, end_lo, end_hi;
    volatile int temp;

    // Get all of L1_DATA into L1 Cache.
    for (int i=0; i < 8192; i++) {
        L1_DATA[i] = 0;
    }

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


    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end   = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start)/10;
}

// int testL2() {
//     int L2_DATA[65536];              // 256KB Data Cache => (256 * 1024 * 8) / 4
//     volatile uint32_t start_lo, start_hi, end_lo, end_hi;
//     volatile int temp;

//     // Get all of L1_DATA into L1 Cache.
//     for (int i=0; i < 65536; i++) {
//         L2_DATA[i] = 0;
//     }

//     __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
//     temp = L2_DATA[0];
//         temp = L2_DATA[1];
//         temp = L2_DATA[2];
//         temp = L2_DATA[3];
//         temp = L2_DATA[4];
//         temp = L2_DATA[5];
//         temp = L2_DATA[6];
//         temp = L2_DATA[7];
//         temp = L2_DATA[8];
//     temp = L2_DATA[9];
//     __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));

//     // Convert to 64 bit ints.
//     volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
//     volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
//     return (end-start)/10;
// }

int main() {
    int total = 0;
    printf(" --- 10 Loads --- ");
    printf("\n\tL1 Avg Cycles: %d", testL1());
    // printf("\n\tL2 Avg Cycles: %d", testL2());
    printf("\n\tCycles for RDTSC: %d", testTSC());
    
    printf("\n\n");
}