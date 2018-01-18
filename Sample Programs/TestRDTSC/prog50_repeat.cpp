#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




int L1_DATA[8192];              // 32KB Data Cache => 32768B; 32bit int => (32768 * 8) / 32 elems to fill 32KB Cache

volatile uint32_t start_lo, start_hi, end_lo, end_hi;
volatile uint64_t start, end;
volatile int temp;

int testTSC() {
    volatile uint32_t dead;
    __asm__ __volatile__ ("rdtscp" : "=a"(start_lo), "=d"(start_hi));
    __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return (end-start);
}

int testL1() {
    // Get all of L1_DATA into L1 Cache.
    for (int i=0; i < 8192; i++) {
        L1_DATA[i] = 0;
    }

    uint64_t total = 0;
    for (int i=0; i < 1000; i++) {
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
            temp = L1_DATA[10];
            temp = L1_DATA[11];
            temp = L1_DATA[12];
            temp = L1_DATA[13];
            temp = L1_DATA[14];
            temp = L1_DATA[15];
            temp = L1_DATA[16];
            temp = L1_DATA[17];
            temp = L1_DATA[18];
            temp = L1_DATA[19];
            temp = L1_DATA[20];
            temp = L1_DATA[21];
            temp = L1_DATA[22];
            temp = L1_DATA[23];
            temp = L1_DATA[24];
            temp = L1_DATA[25];
            temp = L1_DATA[26];
            temp = L1_DATA[27];
            temp = L1_DATA[28];
            temp = L1_DATA[29];
            temp = L1_DATA[30];
            temp = L1_DATA[31];
            temp = L1_DATA[32];
            temp = L1_DATA[33];
            temp = L1_DATA[34];
            temp = L1_DATA[35];
            temp = L1_DATA[36];
            temp = L1_DATA[37];
            temp = L1_DATA[38];
            temp = L1_DATA[39];
            temp = L1_DATA[40];
            temp = L1_DATA[41];
            temp = L1_DATA[42];
            temp = L1_DATA[43];
            temp = L1_DATA[44];
            temp = L1_DATA[45];
            temp = L1_DATA[46];
            temp = L1_DATA[47];
            temp = L1_DATA[48];
        temp = L1_DATA[49];
        __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
        start   =  ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
        end     =  ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
        total += (end - start)/50;
    }
    
    return total/1000;
}

int main() {
    int total = 0;
    printf(" --- L1 50 Instructions x 1000 --- ");
    printf("\n\tL1 Avg Cycles: %d", testL1());
    printf("\n\tCycles for RDTSC: %d", testTSC());

    printf("\n\n");
}