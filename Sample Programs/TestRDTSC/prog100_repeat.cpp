#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>




int L1_DATA[8192];              // 32KB Data Cache => 32768B; 32bit int => (32768 * 8) / 32 elems to fill 32KB Cache

volatile uint32_t start_lo, start_hi, end_lo, end_hi;
volatile uint64_t start, end;
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

    uint64_t total;
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
            temp = L1_DATA[50];
            temp = L1_DATA[51];
            temp = L1_DATA[52];
            temp = L1_DATA[53];
            temp = L1_DATA[54];
            temp = L1_DATA[55];
            temp = L1_DATA[56];
            temp = L1_DATA[57];
            temp = L1_DATA[58];
            temp = L1_DATA[59];
            temp = L1_DATA[60];
            temp = L1_DATA[61];
            temp = L1_DATA[62];
            temp = L1_DATA[63];
            temp = L1_DATA[64];
            temp = L1_DATA[65];
            temp = L1_DATA[66];
            temp = L1_DATA[67];
            temp = L1_DATA[68];
            temp = L1_DATA[69];
            temp = L1_DATA[70];
            temp = L1_DATA[71];
            temp = L1_DATA[72];
            temp = L1_DATA[73];
            temp = L1_DATA[74];
            temp = L1_DATA[75];
            temp = L1_DATA[76];
            temp = L1_DATA[77];
            temp = L1_DATA[78];
            temp = L1_DATA[79];
            temp = L1_DATA[80];
            temp = L1_DATA[81];
            temp = L1_DATA[82];
            temp = L1_DATA[83];
            temp = L1_DATA[84];
            temp = L1_DATA[85];
            temp = L1_DATA[86];
            temp = L1_DATA[87];
            temp = L1_DATA[88];
            temp = L1_DATA[89];
            temp = L1_DATA[90];
            temp = L1_DATA[91];
            temp = L1_DATA[92];
            temp = L1_DATA[93];
            temp = L1_DATA[94];
            temp = L1_DATA[95];
            temp = L1_DATA[96];
            temp = L1_DATA[97];
            temp = L1_DATA[98];
        temp = L1_DATA[99];
        __asm__ __volatile__ ("rdtscp" : "=a"(end_lo), "=d"(end_hi));
        start   =  ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
        end     =  ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
        total += (end - start)/100;
    }

    // Convert to 64 bit ints.
    volatile uint64_t start = ( (unsigned long long)start_lo)|( ((unsigned long long)start_hi)<<32 );
    volatile uint64_t end = ( (unsigned long long)end_lo)|( ((unsigned long long)end_hi)<<32 );
    return total/1000;
}

int main() {
    int total = 0;
    printf(" --- L1 100 Instructions x 1000 --- ");
    printf("\n\tL1 Avg Cycles: %d", testL1());
    printf("\n\tCycles for RDTSC: %d", testTSC());

    printf("\n\n");
}