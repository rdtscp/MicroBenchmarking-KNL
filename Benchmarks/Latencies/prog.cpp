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
/*
 *  Put your Definitions Below
 */
#define L1_SIZE_B           262144
#define L2_SIZE_B           1048576
#define MEM_ARR_B           62144
#define LINE_SIZE_B         64


/* ---- DONT TOUCH BELOW ---- */

#define STRIDE   LINE_SIZE_B / 4
const unsigned long long L1_START_IDX = 0;
const unsigned long long L2_START_IDX = L1_SIZE_B / LINE_SIZE_B;
std::string mem_name = "DRAM";

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

// ------ Latencies ------ \\

int latencyL1Overhead() {
    int output = 0;
    int latencies[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of gathering the overhead.
    // printf("\n\n\nL1 Overhead\n");
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Calculating overhead, so no instruction to be timed here.
        asm volatile("#Overhead Latency");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;            // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // printf("\n\tLAT\t|\tO/Head");
    // printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc      = (double)latencies[i] / (double)10;
        std::string cycles;
        if (perc > 50) output = i;
    }
    return output;
}
/* Measures the time to load from L1 Cache, prints findings in ASCII Table */
void latencyL1(int overhead) {
    int latencies[500];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of timing an L1 Load.
    printf("\n\n\nTesting L1");
    printf("\nTiming Overhead: %d\n", overhead);
    latency = 0;
    int l1_data[L1_SIZE_B/4];                               // Allocate enough space to fill up L1 Cache.
    for (int i=0; i < 1000; i++) {
        warmup();                                           // Warmup timestamping instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        for (int i=L1_START_IDX; i < (L1_START_IDX +(32 * STRIDE)); i++)             // Access required data beforehand, so that it is in L1 Cache.
            l1_data[i] = i + 1;

        asm volatile("MFENCE");
        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);

        // Perform 13 Loads to L1 Data from different Cache Lines.
        asm volatile (
            "\n\t#1 L1 Load Inst"
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            "\n\tmov %%eax, %1"
            "\n\tMFENCE"
            "\n\tmov %%eax, %2"
            "\n\tMFENCE"
            "\n\tmov %%eax, %3"
            "\n\tMFENCE"
            "\n\tmov %%eax, %4"
            "\n\tMFENCE"
            "\n\tmov %%eax, %5"
            "\n\tMFENCE"
            "\n\tmov %%eax, %6"
            "\n\tMFENCE"
            "\n\tmov %%eax, %7"
            "\n\tMFENCE"
            "\n\tmov %%eax, %8"
            "\n\tMFENCE"
            "\n\tmov %%eax, %9"
            "\n\tMFENCE"
            "\n\tmov %%eax, %10"
            "\n\tMFENCE"
            "\n\tmov %%eax, %11"
            "\n\tMFENCE"
            "\n\tmov %%eax, %12"
            "\n\tMFENCE"
            ::
            "r"(l1_data[0 * STRIDE]),
            "r"(l1_data[1 * STRIDE]),
            "r"(l1_data[2 * STRIDE]),
            "r"(l1_data[3 * STRIDE]),
            "r"(l1_data[4 * STRIDE]),
            "r"(l1_data[5 * STRIDE]),
            "r"(l1_data[6 * STRIDE]),
            "r"(l1_data[7 * STRIDE]),
            "r"(l1_data[8 * STRIDE]),
            "r"(l1_data[9 * STRIDE]),
            "r"(l1_data[10 * STRIDE]),
            "r"(l1_data[11 * STRIDE]),
            "r"(l1_data[12 * STRIDE])
            :
        );

        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);   

        // Convert the 4 x 32bit values into 2 x 64bit values.
         start   = ( ((uint64_t)start_hi << 32) | start_lo );
         end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        latency = (int)((latency - overhead)/13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    /* Produce Output Table */
    printf("\n\tLAT\t|\tL1 Hit");
    printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc = (double)latencies[i] / (double)10;
        if (perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // Latency Column
            std::cout << "\t" << i << "\t|";

            // L1 Load Count Column
            std::cout << "\t" << latencies[i];
            temp = latencies[i];
            digits = 0; while (temp != 0) { temp /= 10; digits++; }
            for (int i=digits; i < 5; i++) {
                std::cout << " ";
            }
            if (perc > 1) printf("(%.2f%%)", perc);
            else printf("      ");
            std::cout << "\t";
            if (perc > 50) printf(" --> %d Cycle(s)", i);
        }
    }
}


int latencyL2Overhead() {
    int output = 0;
    int latencies[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of gathering the overhead.
    // printf("\n\n\nL2 Overhead\n");
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Calculating overhead, so no instruction to be timed here.
        asm volatile("#Overhead Latency");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;            // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // printf("\n\tLAT\t|\tO/Head");
    // printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc      = (double)latencies[i] / (double)10;
        std::string cycles;
        if (perc > 1) {
            int temp, digits;
            // std::cout << "\n";

            // STD::COUT
                // Latency Column
                // std::cout << "\t" << i << "\t|";

                // Overhead Column
                    // std::cout << "\t" << latencies[i];
                    temp = latencies[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    // for (int i=digits; i < 5; i++) {
                    //     std::cout << " ";
                    // }
                    // if (perc > 1) printf("(%.2f%%)", perc);
                    // else printf("      ");
                    // std::cout << "\t";
                    if (perc > 50) {
                        // printf(" --> %d Cycles", i);
                        output = i;
                    }
        }
    }
    return output;
}

/* Measures the time to load from L2 Cache, prints findings in ASCII Table */
void latencyL2(int overhead) {
    int latencies[500];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of timing an L2 Load.
    printf("\n\n\nTesting L2");
    printf("\nTiming Overhead: %d\n", overhead);
    latency = 0;
    
    for (int i=0; i < 1000; i++) {

        int l2_data[L2_SIZE_B/4];                               // Allocate enough space to fill up L2 Cache.
        memset(l2_data, 0, sizeof(l2_data));

        warmup();                                           // Warmup timestamping instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        /*
         *  L1 Cache: [ | | | ]
         *                    ^
         *  L2 Cache: [ | | | | | | | | | | | | | | | ]
         *                    ^
         *            Try flush Cache Lines up to here, then read from above
         *          only so we read from L2 exclusively.
         * 
         */
        // Load all our Data into L1 & L2 Caches.
        for (int i=L1_START_IDX; i < (L1_SIZE_B/4); i++)             // Access required data beforehand, so that it is in L1 Cache.
            l2_data[i] = i + 1;
        

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        
        // Perform 13 Loads to L2 Data from different Cache Lines.
        asm volatile (
            "\n\t#1 L1 Load Inst"
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            "\n\tmov %%eax, %1"
            "\n\tMFENCE"
            "\n\tmov %%eax, %2"
            "\n\tMFENCE"
            "\n\tmov %%eax, %3"
            "\n\tMFENCE"
            "\n\tmov %%eax, %4"
            "\n\tMFENCE"
            "\n\tmov %%eax, %5"
            "\n\tMFENCE"
            "\n\tmov %%eax, %6"
            "\n\tMFENCE"
            "\n\tmov %%eax, %7"
            "\n\tMFENCE"
            "\n\tmov %%eax, %8"
            "\n\tMFENCE"
            "\n\tmov %%eax, %9"
            "\n\tMFENCE"
            "\n\tmov %%eax, %10"
            "\n\tMFENCE"
            "\n\tmov %%eax, %11"
            "\n\tMFENCE"
            "\n\tmov %%eax, %12"
            "\n\tMFENCE"
            ::
            "r"(l2_data[L2_START_IDX + 0 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 12 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 1 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 11 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 2 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 10 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 3 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 9 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 4 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 8 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 5 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 7 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 6 * STRIDE])
            :
        );

        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);   

        // Convert the 4 x 32bit values into 2 x 64bit values.
         start   = ( ((uint64_t)start_hi << 32) | start_lo );
         end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        latency = (int)((latency - overhead)/13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    /* Produce Output Table */
    printf("\n\tLAT\t|\tLocal L2 (M) Hit");
    printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc = (double)latencies[i] / (double)10;
        if (perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // Latency Column
            std::cout << "\t" << i << "\t|";

            // L1 Load Count Column
            std::cout << "\t" << latencies[i];
            temp = latencies[i];
            digits = 0; while (temp != 0) { temp /= 10; digits++; }
            for (int i=digits; i < 5; i++) {
                std::cout << " ";
            }
            if (perc > 1) printf("(%.2f%%)", perc);
            else printf("      ");
            std::cout << "\t";
            if (perc > 50) printf(" --> %d Cycle(s)", i);
        }
    }
}



int latencyMEMOverhead() {
    int output = 0;
    int latencies[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of gathering the overhead.
    // printf("\n\n\nMEM Overhead\n");
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();
        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Calculating overhead, so no instruction to be timed here.
        asm volatile("#Overhead Latency");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        asm volatile("MFENCE");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;            // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // printf("\n\tLAT\t|\tO/Head");
    // printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc      = (double)latencies[i] / (double)10;
        std::string cycles;
        if (perc > 50) {
            output = i;
        }
    }
    return output;
}
/* Measures the time to load from L1 Cache, prints findings in ASCII Table */
void latencyMEM(int overhead) {
    int latencies[500];                                    // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of timing an L2 Load.
    printf("\n\n\nTesting %s", mem_name.c_str());
    printf("\nTiming Overhead: %d\n", overhead);
    latency = 0;
    int data[MEM_ARR_B/4];                               // Allocate enough space to fill up L2 Cache.
    for (int i=0; i < 1000; i++) {
        warmup();                                           // Warmup timestamping instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Flush Surrounding Cache Lines.
        for (int j=0; j < (200*STRIDE); j++) {
            asm volatile(
                "CLFLUSH (%0)"::
                "r"(&data[j]):
            );
        }

        asm volatile("MFENCE");

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);

        // Perform Load to Flushed Line.
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[131 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[143 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[132 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[142 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[133 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[141 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[134 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[140 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[135 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[139 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[136 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[138 * STRIDE]):
        );
        asm volatile (
            "\n\tmov %%eax, %0"
            "\n\tMFENCE"
            ::"r"(data[137 * STRIDE]):
        );

        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);   

        // Convert the 4 x 32bit values into 2 x 64bit values.
         start   = ( ((uint64_t)start_hi << 32) | start_lo );
         end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (((end - start) - overhead)/13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    /* Produce Output Table */
    printf("\n\tLAT\t|\t%s Hit", mem_name.c_str());
    printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc = (double)latencies[i] / (double)10;
        if (perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // Latency Column
            std::cout << "\t" << i << "\t|";

            // L1 Load Count Column
            std::cout << "\t" << latencies[i];
            temp = latencies[i];
            digits = 0; while (temp != 0) { temp /= 10; digits++; }
            for (int i=digits; i < 5; i++) {
                std::cout << " ";
            }
            if (perc > 1) printf("(%.2f%%)", perc);
            else printf("      ");
            std::cout << "\t";
            if (perc > 50) printf(" --> %d Cycle(s)", i);
        }
    }
}



void latencySanity() {
    double num_tests = 13.0;
    int cwde_lat[500];                                       // i'th element of array indicates how many times a CWDE took i cycles.
    memset(cwde_lat, 0, sizeof(cwde_lat));                    // Initialise count of CWDE latencies to 0.
    int pause_lat[500];                                     // i'th element of array indicates how many times a PAUSE took i cycles.
    memset(pause_lat, 0, sizeof(pause_lat));                // Initialise count of PAUSE latencies to 0.
    int cwd_lat[500];                                     // i'th element of array indicates how many times a CWD took i cycles.
    memset(cwd_lat, 0, sizeof(cwd_lat));                // Initialise count of CWD latencies to 0.

    printf("\n\n\nSanity Checks\n");
    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of timing a CWDE Inst.
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
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        asm volatile("CWDE");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        latency = (int)((latency - 39) / 13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) cwde_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
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
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        asm volatile ("PAUSE");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        latency = (int)((latency - 39) / 13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) pause_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
        // else printf("\nTiming PAUSE Anomaly: %lli Cycles", latency);
    }

    // Do 1000 test runs of timing a CWD Inst.
    latency = 0;
    for (int i=0; i < 1000; i++) {
        warmup();

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);
        // Load the data variable, which will exist in the L1 Cache.
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        asm volatile("CWD");
        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);

        // Convert the 4 x 32bit values into 2 x 64bit values.
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = end - start;

        latency = (int)((latency - 39) / 13.0);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) cwd_lat[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    // Output results
    printf("\n\tLAT\t|\tCWDE(1)\t\t|\tPAUSE(25)\t|\tCWD(7)");
    printf("\n\t--------+-----------------------+-----------------------+-----------------------");
    for (int i=0; i < 500; i++) {
        double cwde_perc    = (double)cwde_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i]  / (double)10;
        double cwd_perc     = (double)cwd_lat[i]    / (double)10;
        std::string cycles;
        if (cwde_perc > 1 || pse_perc > 1 || cwd_perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // STD::COUT
                // Latency Column
                std::cout << "\t" << i << "\t|";

                // CWDE Column
                    std::cout << "\t" << cwde_lat[i];
                    temp = cwde_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (cwde_perc > 1) printf("(%.2f%%)", cwde_perc);
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

                // CWD Column
                    std::cout << "\t" << cwd_lat[i];
                    temp = pause_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (cwd_perc > 1) printf("(%.2f%%)", cwd_perc);
                    else printf("      ");
                    std::cout << "\t";
        }
    }
}


int main(int argc, char *argv[]) {
    #ifdef __linux__
        cpu_set_t mask;
        int status;

        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        status = sched_setaffinity(0, sizeof(mask), &mask);
        if (status != 0)
        {
            perror("sched_setaffinity");
        }
        printf("\nPinning to Core %d", 0);
    #endif

    if ((std::string)argv[1] == "1")
        mem_name = "MCDRAM";

    // int overhead = latencyOverhead();
    latencyL1(latencyL1Overhead());
    printf("\n\n\t------------------------------------");
    latencyL2(latencyL2Overhead());
    printf("\n\n\t------------------------------------");    
    latencyMEM(latencyMEMOverhead());
    latencySanity();

    printf("\n");
}