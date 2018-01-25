#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>

#ifdef __linux__    // Linux only
    #include <sched.h>  // sched_setaffinity
#endif

volatile int mem_data[100000];
volatile int visited[1000];

void warmupCPUID() {
    __asm__ __volatile__ (
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
        "cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;cpuid;"
    );
}

void warmupRDTSC() {
    __asm__ __volatile__ (
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
        "rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;rdtsc;"
    );
}

void warmupRDTSCP() {
    __asm__ __volatile__ (
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
        "rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;rdtscp;"
    );
}

void warmupDIVS() {
    volatile double temp = 10;
    for (int i=0; i < 1000; i++) {
        temp = i / temp;
    }
}

void warmup() {
    warmupCPUID();
    warmupRDTSC();
    warmupRDTSCP();
    warmupDIVS();
}

inline __attribute__((always_inline)) volatile void benchit_timestamp(uint32_t *time_hi, uint32_t *time_lo) {
    __asm__ __volatile__("rdtsc": "=a" (*time_lo), "=d" (*time_hi));
}

/*
    Sourced from Intel white paper by Gabriele Paoloni.
    Code used detailed on page 16.
    https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
*/

inline __attribute__((always_inline)) volatile void start_timestamp(uint32_t *time_hi, uint32_t *time_lo) {
    asm volatile (
        "CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (*time_hi), "=r" (*time_lo)::
        "%rax", "%rbx", "%rcx", "%rdx"
    );
}

inline __attribute__((always_inline)) volatile void end_timestamp(uint32_t *time_hi, uint32_t *time_lo) {
    asm volatile(
        "RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (*time_hi), "=r" (*time_lo)::
        "%rax", "%rbx", "%rcx", "%rdx"
    );
}

// Created vector to occupy memory == mem_ints ints
void flushCaches(int mem_ints) {
    std::vector<int> dead_data(mem_ints, 0);                      // Random data, used for measuring Load latencies.
    for (int i=0; i < mem_ints; i+=4) {
        dead_data[i] = i;
        dead_data[i+1] = i+1;
        dead_data[i+2] = i+2;
        dead_data[i+3] = i+3;
    }
}

int main(int argc, char *argv[]) { 
    #ifdef __linux__
        int cpuAffinity = argc > 1 ? atoi(argv[1]) : -1;

        if (cpuAffinity > -1)
        {
            cpu_set_t mask;
            int status;

            CPU_ZERO(&mask);
            CPU_SET(cpuAffinity, &mask);
            status = sched_setaffinity(0, sizeof(mask), &mask);
            if (status != 0)
            {
                perror("sched_setaffinity");
            }
            printf("\n\nSet CPU Affinity to CPU%d\n\n", cpuAffinity);
        }
    #endif

    warmup();

    int ohead_lat[50000];                                   // i'th element of array indicates how many times a NOP took i cycles.
    memset(ohead_lat, 0, sizeof(ohead_lat));                // Initialise count of overhead latencies to 0.

    int l1_lat[50000];                                      // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(l1_lat, 0, sizeof(l1_lat));                      // Initialise count of overhead latencies to 0.

    int l2_lat[50000];                                      // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(l2_lat, 0, sizeof(l2_lat));                      // Initialise count of overhead latencies to 0.

    int mem_idxs = 100000;
    int mem_lat[50000];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(mem_lat, 0, sizeof(mem_lat));                    // Initialise count of overhead latencies to 0.

    int pause_lat[50000];                                   // i'th element of array indicates how many times a PAUSE took i cycles.
    memset(pause_lat, 0, sizeof(l1_lat));                   // Initialise count of overhead latencies to 0.

    int div_lat[50000];                                     // i'th element of array indicates how many times a DIV took i cycles.
    memset(div_lat, 0, sizeof(div_lat));                    // Initialise count of overhead latencies to 0.

    int f2xm1_lat[50000];                                   // i'th element of array indicates how many times a F2XM1 took i cycles.
    memset(f2xm1_lat, 0, sizeof(f2xm1_lat));                // Initialise count of overhead latencies to 0.
    
    uint32_t start_hi, start_lo, end_hi, end_lo;            // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
    uint64_t start, end;                                    // 64bit integers to hold the start/end timestamp counter values.
    uint64_t latency;

    uint64_t l1_ints = 32  * 1024 / 4;
    uint64_t l2_ints = 256 * 1024 / 4;
    std::vector<int> l1_data(l1_ints, 0);                   // Random data, used for measuring Load latencies.
    std::vector<int> l2_data(100000, 0);                    // Random data, used for measuring Load latencies.
    volatile int temp;

    // Do 1000 test runs of gathering the overhead.
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Calculating overhead, so no instruction to be timed here.
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) ohead_lat[latency]++;            // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Do 1000 test runs of timing an L1 Load.
    latency = 0;
    int idx;
    for (int i=0; i < 1000; i++) {

        // flushCaches(l1_ints);
        warmup();
        idx = rand()%l1_ints;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("#Load Inst\n\tmov %%eax, %0": "=m"(l1_data[idx]):: "eax", "memory");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) l1_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Do 1000 test runs of timing an L2 Load.
    latency = 0;
    for (int i=0; i < 1000; i++) {

        flushCaches(l1_ints);
        warmup();
        idx = rand()%100000;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("#Load Inst\n\tmov %%eax, %0": "=m"(l2_data[idx]):: "eax", "memory");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) l2_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        else printf(" - %lli - ", latency);
    }

    // Do 1000 test runs of timing an Memory Load.
    latency = 0;
    for (int i=0; i < 1000; i++) {

        flushCaches(l2_ints);
        warmup();

        idx = rand()%100000;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("#Load Inst\n\tmov %%eax, %0": "=m"(mem_data[idx]):: "eax", "memory");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 50000) mem_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        else printf(" - %lli - ", latency);
    }

    // Do 1000 test runs of timing a DIV Inst.
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        int x;
        int y = 10;
        int z = 5;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        x = y / z;
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) div_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Do 1000 test runs of timing a PAUSE Inst.
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        int x;
        int y = 10;
        int z = 5;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile ("PAUSE");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) pause_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Do 1000 test runs of timing a F2XM1 Inst.
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        // asm volatile("mov %%eax, %0": "=m"(data[0]):: "eax", "memory");
        asm volatile("F2XM1");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) f2xm1_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Output results
    printf("\n\tLAT\t|\tO/Head\t\t|\tL1 Load\t\t|\tL2 Load\t\t|\tMem Load\t|\tDIV(29-42)\t|\tPAUSE(25)\t|\tF2XM1(100-400)");
    printf("\n\t--------+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------");
    for (int i=0; i < 50000; i++) {
        double oh_perc      = (double)ohead_lat[i] / (double)10;
        double l1_perc      = (double)l1_lat[i]    / (double)10;
        double l2_perc      = (double)l2_lat[i]    / (double)10;
        double mem_perc     = (double)mem_lat[i]   / (double)10;
        double div_perc     = (double)div_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i] / (double)10;
        double f2xm1_perc   = (double)f2xm1_lat[i] / (double)10;
        std::string cycles;
        if (oh_perc > 1 || l1_perc > 1 || l2_perc > 1 || mem_perc > 1 || div_perc > 1 || pse_perc > 1 || f2xm1_perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // STD::COUT
                // Latency Column
                std::cout << "\t" << i << "\t|";

                // Overhead Column
                    std::cout << "\t" << ohead_lat[i];
                    temp = ohead_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (oh_perc > 1) printf("(%.2f%%)", oh_perc);
                    else printf("      ");
                    std::cout << "\t|";

                // L1 Load Column
                    std::cout << "\t" << l1_lat[i];
                    temp = l1_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (l1_perc > 1) printf("(%.2f%%)", l1_perc);
                    else printf("      ");
                    std::cout << "\t|";
                
                // L2 Load Column
                    std::cout << "\t" << l2_lat[i];
                    temp = l2_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (l2_perc > 1) printf("(%.2f%%)", l2_perc);
                    else printf("      ");
                    std::cout << "\t|";
                // Mem Load Column
                    std::cout << "\t" << mem_lat[i];
                    temp = mem_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (mem_perc > 1) printf("(%.2f%%)", mem_perc);
                    else printf("      ");
                    std::cout << "\t|";
                // DIV Column
                    std::cout << "\t" << div_lat[i];
                    temp = div_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (div_perc > 1) printf("(%.2f%%)", div_perc);
                    else printf("      ");
                    std::cout << "\t|";

                // PAUSE Column
                    std::cout << "\t" << pause_lat[i];
                    temp = pause_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (pse_perc > 1) printf("(%.2f%%)", pse_perc);
                    else printf("      ");
                    std::cout << "\t|";

                // F2XM1 Column
                    std::cout << "\t" << f2xm1_lat[i];
                    temp = f2xm1_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (f2xm1_perc > 1) printf("(%.2f%%)", f2xm1_perc);
                    else printf("      ");
        }
    }
    std::cerr << "\n\n\n\n --- Markdown Table ---\n\n";
    std::cerr << "\nLAT | O/Head | L1 Load | L2 Load | Mem Load | DIV(29-42) | PAUSE(25) | F2XM1(100-400)";
    std::cerr << "\n--- | --- | --- | --- | --- | --- | --- | ---";
    for (int i=0; i < 50000; i++) {
        double oh_perc      = (double)ohead_lat[i] / (double)10;
        double l1_perc      = (double)l1_lat[i]    / (double)10;
        double l2_perc      = (double)l2_lat[i]    / (double)10;
        double mem_perc     = (double)mem_lat[i]   / (double)10;
        double div_perc     = (double)div_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i] / (double)10;
        double f2xm1_perc   = (double)f2xm1_lat[i] / (double)10;
        std::string cycles;
        if (oh_perc > 1 || l1_perc > 1 || l2_perc > 1 || mem_perc > 1 || div_perc > 1 || pse_perc > 1 || f2xm1_perc > 1) {
            int temp, digits;
            // STD::CERR
            std::cerr << "\n" << i;
            std::cerr << " | " << ohead_lat[i];
            if (oh_perc > 1) fprintf(stderr, "(%.2f%%)", oh_perc);
            std::cerr << " | " << l1_lat[i];
            if (l1_perc > 1) fprintf(stderr, "(%.2f%%)", l1_perc);
            std::cerr << " | " << l2_lat[i];
            if (l2_perc > 1) fprintf(stderr, "(%.2f%%)", l2_perc);
            std::cerr << " | " << div_lat[i];
            if (mem_perc > 1) fprintf(stderr, "(%.2f%%)", mem_perc);
            std::cerr << " | " << mem_lat[i];
            if (div_perc > 1) fprintf(stderr, "(%.2f%%)", div_perc);
            std::cerr << " | " << pause_lat[i];
            if (pse_perc > 1) fprintf(stderr, "(%.2f%%)", pse_perc);
            std::cerr << " | " << f2xm1_lat[i];
            if (f2xm1_perc > 1) fprintf(stderr, "(%.2f%%)", f2xm1_perc);
            
        }
    }
    printf("\n");
}
