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

#define ARR_SIZE_B   62144
#define ARR_STRIDE   64/4

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

int latencyOverhead() {
    int output = 0;
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
    #endif

    int latencies[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of gathering the overhead.
    printf("\n\n\nTesting Overhead\n");
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
        if (latency < 500) latencies[latency]++;            // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    printf("\n\tLAT\t|\tO/Head");
    printf("\n\t--------+-----------------------");
    for (int i=0; i < 500; i++) {
        double perc      = (double)latencies[i] / (double)10;
        std::string cycles;
        if (perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // STD::COUT
                // Latency Column
                std::cout << "\t" << i << "\t|";

                // Overhead Column
                    std::cout << "\t" << latencies[i];
                    temp = latencies[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (perc > 1) printf("(%.2f%%)", perc);
                    else printf("      ");
                    std::cout << "\t";
                    if (perc > 50) {
                        printf(" --> %d Cycles", i);
                        output = i;
                    }
        }
    }
    return output;
}

/* Measures the time to load from L1 Cache, prints findings in ASCII Table */
void latencyMEM(int overhead) {
    int latencies[500];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of timing an L2 Load.
    printf("\n\n\nTesting DRAM\n");
    latency = 0;
    int data[ARR_SIZE_B/4];                               // Allocate enough space to fill up L2 Cache.
    for (int i=0; i < 1000; i++) {
        warmup();                                           // Warmup timestamping instructions.

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Flush Surrounding Cache Lines.
        asm volatile(
            "\n\tCLFLUSH (%0)"
            "\n\tCLFLUSH (%1)"
            "\n\tCLFLUSH (%2)"
            "\n\tCLFLUSH (%3)"
            "\n\tCLFLUSH (%4)"
            "\n\tCLFLUSH (%5)"
            "\n\tCLFLUSH (%6)"
            "\n\tCLFLUSH (%7)"
            "\n\tCLFLUSH (%8)"
            "\n\tCLFLUSH (%9)"
            ::
            "r"(&data[128 * ARR_STRIDE]),
            "r"(&data[129 * ARR_STRIDE]),
            "r"(&data[130 * ARR_STRIDE]),
            "r"(&data[131 * ARR_STRIDE]),
            "r"(&data[132 * ARR_STRIDE]),
            "r"(&data[133 * ARR_STRIDE]),
            "r"(&data[134 * ARR_STRIDE]),
            "r"(&data[135 * ARR_STRIDE]),
            "r"(&data[136 * ARR_STRIDE]),
            "r"(&data[137 * ARR_STRIDE])
            :
        );

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);

        // Perform Load to Flushed Line.
        asm volatile (
            "\n\t#1 L1 Load Inst"
            "\n\tmov %%eax, %0"
            ::
            "r"(data[133 * ARR_STRIDE])
            :
        );

        // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo);   

        // Convert the 4 x 32bit values into 2 x 64bit values.
         start   = ( ((uint64_t)start_hi << 32) | start_lo );
         end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        // Increment the appropriate indexes of our latency tracking arrays.
        if (latency < 500) latencies[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
    }

    /* Produce Output Table */
    printf("\n\tLAT\t|\tMEM Hit");
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
            if (perc > 50) printf(" --> %d Cycles => %d Cycles Per Load", i, (i - overhead));
        }
    }
}

void latencySanity() {
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
    #endif

    int div_lat[500];                                       // i'th element of array indicates how many times a DIV took i cycles.
    memset(div_lat, 0, sizeof(div_lat));                    // Initialise count of DIV latencies to 0.
    int pause_lat[500];                                     // i'th element of array indicates how many times a PAUSE took i cycles.
    memset(pause_lat, 0, sizeof(pause_lat));                // Initialise count of PAUSE latencies to 0.
    int f2xm1_lat[500];                                     // i'th element of array indicates how many times a PAUSE took i cycles.
    memset(f2xm1_lat, 0, sizeof(f2xm1_lat));                // Initialise count of PAUSE latencies to 0.

    printf("\n\n\nSanity Checks\n");
    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

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
        // else printf("\nTiming PAUSE Anomaly: %lli Cycles", latency);
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
    printf("\n\tLAT\t|\tDIV(29-42)\t|\tPAUSE(25)\t|\tF2XM1(100-400)");
    printf("\n\t--------+-----------------------+-----------------------+-----------------------");
    for (int i=0; i < 500; i++) {
        double div_perc     = (double)div_lat[i]   / (double)10;
        double pse_perc     = (double)pause_lat[i] / (double)10;
        double xm1_perc     = (double)f2xm1_lat[i] / (double)10;
        std::string cycles;
        if (div_perc > 1 || pse_perc > 1 || xm1_perc > 1) {
            int temp, digits;
            std::cout << "\n";

            // STD::COUT
                // Latency Column
                std::cout << "\t" << i << "\t|";

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
                    temp = pause_lat[i];
                    digits = 0; while (temp != 0) { temp /= 10; digits++; }
                    for (int i=digits; i < 5; i++) {
                        std::cout << " ";
                    }
                    if (xm1_perc > 1) printf("(%.2f%%)", xm1_perc);
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
    #endif

    int overhead = latencyOverhead();
    latencyMEM(overhead);
    latencySanity();

    printf("\n");
}