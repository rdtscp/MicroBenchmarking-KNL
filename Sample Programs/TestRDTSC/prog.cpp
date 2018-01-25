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

const uint64_t MEM_SIZE       = 17179869184;
const int MEM_LINE_SIZE  = 64;
const int MEM_SET_SIZE   = 16;
const int MEM_STRIDE     = 16;

const int L2_SIZE       = 262144;
const int L2_LINE_SIZE  = 64;
const int L2_SET_SIZE   = 16;
const int L2_STRIDE     = 16;

const int L1_SIZE       = 32768;
const int L1_LINE_SIZE  = 64;
const int L1_SET_SIZE   = 8;
const int L1_STRIDE     = 16;

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

void warmup() {
    warmupCPUID();
    warmupRDTSC();
    warmupRDTSCP();
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


// Attempts to full an N-way set associative cache with dead data.
void flushCache(int sizeB, int lineB, int N) {
    int num_lines = sizeB / lineB;
    int num_sets  = (num_lines / N);
    int bytes_to_fill = (N * num_sets) * lineB;
    int ints_to_fill  = bytes_to_fill / 4;
    int dead_data[ints_to_fill];
    for (int i=0; i < ints_to_fill; i++) {
        dead_data[i] = i;
    }

    volatile int temp;
    for (int i=0; i < ints_to_fill; i++) {
        temp = dead_data[i];
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

    // Misc Vars.
        volatile int temp;

    // Benchmarking result variables.
        int ohead_lat[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
        memset(ohead_lat, 0, sizeof(ohead_lat));                // Initialise count of overhead latencies to 0.

        int l1_lat[500];                                        // i'th element of array indicates how many times an L1 Load took i cycles.
        memset(l1_lat, 0, sizeof(l1_lat));                      // Initialise count of overhead latencies to 0.

        int l2_lat[500];                                        // i'th element of array indicates how many times an L1 Load took i cycles.
        memset(l2_lat, 0, sizeof(l2_lat));                      // Initialise count of overhead latencies to 0.

        int mem_lat[500];                                       // i'th element of array indicates how many times an L1 Load took i cycles.
        memset(mem_lat, 0, sizeof(mem_lat));                    // Initialise count of overhead latencies to 0.

        int pause_lat[500];                                     // i'th element of array indicates how many times a PAUSE took i cycles.
        memset(pause_lat, 0, sizeof(pause_lat));                // Initialise count of overhead latencies to 0.

        int div_lat[500];                                       // i'th element of array indicates how many times a DIV took i cycles.
        memset(div_lat, 0, sizeof(div_lat));                    // Initialise count of overhead latencies to 0.

        int f2xm1_lat[500];                                     // i'th element of array indicates how many times a F2XM1 took i cycles.
        memset(f2xm1_lat, 0, sizeof(f2xm1_lat));                // Initialise count of overhead latencies to 0.
    
    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;            // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                    // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;
    //
    //
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
        else printf("\nTiming Overhead Anomaly: %lli Cycles", latency);
    }

    // @TODO Fix; Do 1000 test runs of timing an L1 Load.
    latency = 0;
    int l1_data[L1_SIZE/4];
    memset(l1_data, 0, sizeof(l1_data));
    for (int i=0; i < 1000; i++) {
        warmup();                                           // Warmup timestamping instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
        

        l1_data[0] = 1;                                     // Access required data beforehand, so that it is in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile (
            "\n\t#1 Load Inst"
            "\n\tmov %%eax, %0":
            "=m"(l1_data[0])::
            "eax",
            "memory"
        );

        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) l1_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        else printf("\nTiming L1 Load Anomaly: %lli Cycles", latency);
    }

    // Do 1000 test runs of timing an L2 Load.
    latency = 0;
    int l2_data[L2_SIZE/4];                                 // Data to load.
    memset(l2_data, 0, sizeof(l2_data));                    // Initiliase data to load.
    int l2_idx = 0;                                         // What to load next.
    for (int i=0; i < 1000; i++) {

        flushCache(L1_SIZE, L1_LINE_SIZE, L1_SET_SIZE);     // Flush the L1 Cache.
        
        warmup();                                           // Warmup timing instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("#Load Inst\n\tmov %%eax, %0": "=m"(l2_data[l2_idx]):: "eax", "memory");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
          start   = ( ((uint64_t)start_hi << 32) | start_lo );
          end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        if (latency < 500) l2_lat[latency]++;               // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        else printf("\nTiming L2 Load Anomaly: %lli Cycles", latency);

        l2_idx += ((rand()%10) * L2_STRIDE)%(L2_SIZE/4);    // Update index to load from different cache line (unpredictably) => rand(0,10) * STRIDE
    }

    // Do 1000 test runs of timing a MEM Load.
    latency = 0;
    int mem_data[MEM_SIZE/4];                                // Data to load.
    // memset(mem_data, 0, sizeof(mem_data));                   // Initiliase data to load.
    int mem_idx = 0;                                         // What to load next.
    for (int i=0; i < 1000; i++) {

        flushCache(L1_SIZE, L1_LINE_SIZE, L1_SET_SIZE);     // Flush the L1 Cache.
        flushCache(L2_SIZE, L2_LINE_SIZE, L2_SET_SIZE);     // Flush the L2 Cache.
        
        warmup();                                           // Warmup timing instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("#Load Inst\n\tmov %%eax, %0": "=m"(mem_data[mem_idx]):: "eax", "memory");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
          start   = ( ((uint64_t)start_hi << 32) | start_lo );
          end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        if (latency < 500) mem_lat[latency]++;               // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        else printf("\nTiming MEM Load Anomaly: %lli Cycles", latency);

        mem_idx += ((rand()%10) * MEM_STRIDE)%(MEM_SIZE/4);  // Update index to load from different cache line (unpredictably) => rand(0,10) * STRIDE
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
        else printf("\nTiming DIV Anomaly: %lli Cycles", latency);
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
        else printf("\nTiming PAUSE Anomaly: %lli Cycles", latency);
    }

    // // Do 1000 test runs of timing a F2XM1 Inst.
        // latency = 0;
        // for (int i=0; i < 1000; i++) {
        //     warmup();

        //     start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        //     end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.
            
        //     // Take a starting measurement of the TSC.
        //     start_timestamp(&start_hi, &start_lo);
        //     // Load the data variable, which will exist in the L1 Cache.
        //     // asm volatile("mov %%eax, %0": "=m"(data[0]):: "eax", "memory");
        //     asm volatile("F2XM1");
        //     // Take an ending measurement of the TSC.
        //     end_timestamp(&end_hi, &end_lo);

        //     // Convert the 4 x 32bit values into 2 x 64bit values.
        //     start   = ( ((uint64_t)start_hi << 32) | start_lo );
        //     end     = ( ((uint64_t)end_hi << 32) | end_lo );
        //     latency = end - start;

        //     // Increment the appropriate indexes of our latency tracking arrays.
        //     if (latency < 500) f2xm1_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        //     else printf("\nTiming F2XM1 Anomaly: %lli Cycles", latency);
    // }

    // Output results
    printf("\n\tLAT\t|\tO/Head\t\t|\tL1 Load\t\t|\tL2 Load\t\t|\tMem Load\t|\tDIV(29-42)\t|\tPAUSE(25)\t");
    printf("\n\t--------+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------");
    for (int i=0; i < 500; i++) {
        double oh_perc      = (double)ohead_lat[i] / (double)10;
        double l1_perc      = (double)l1_lat[i]    / (double)10;
        double l2_perc      = (double)l2_lat[i]    / (double)10;
        double mem_perc     = (double)mem_lat[i]   / (double)10;
        double div_perc     = (double)div_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i] / (double)10;
        std::string cycles;
        if (oh_perc > 1 || l1_perc > 1 || l2_perc > 1 || mem_perc > 1 || div_perc > 1 || pse_perc > 1) {
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
                    std::cout << "\t";
        }
    }
    std::cerr << "\n\n\n\n --- Markdown Table ---\n\n";
    std::cerr << "\nLAT | O/Head | L1 Load | L2 Load | Mem Load | DIV(29-42) | PAUSE(25)";
    std::cerr << "\n--- | --- | --- | --- | --- | --- | ---";
    for (int i=0; i < 500; i++) {
        double oh_perc      = (double)ohead_lat[i] / (double)10;
        double l1_perc      = (double)l1_lat[i]    / (double)10;
        double l2_perc      = (double)l2_lat[i]    / (double)10;
        double mem_perc     = (double)mem_lat[i]   / (double)10;
        double div_perc     = (double)div_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i] / (double)10;
        std::string cycles;
        if (oh_perc > 1 || l1_perc > 1 || l2_perc > 1 || mem_perc > 1 || div_perc > 1 || pse_perc > 1) {
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
        }
    }
    printf("\n");
}
