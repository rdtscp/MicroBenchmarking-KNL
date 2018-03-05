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
#include <thread>
#include <time.h>
#include <thread>




#ifdef __linux__    // Linux only
    #include <sched.h>  // sched_setaffinity
    cpu_set_t mask;
#endif
/*
 *  Put your Definitions Below
 */
#define L1_SIZE_B           262144
#define L2_SIZE_B           1048576
#define LINE_SIZE_B         64

#define NUM_CORES           64

/* ---- DONT TOUCH BELOW ---- */

#define STRIDE   LINE_SIZE_B / 4
const unsigned long long L1_START_IDX = 0;
const unsigned long long L2_START_IDX = L1_SIZE_B / LINE_SIZE_B;

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

/*
 *      https://stackoverflow.com/a/43778921
 * 
 */
short CorePin(int coreID) {
    #ifdef __linux__
    short status=0;
    int nThreads = std::thread::hardware_concurrency();
    //std::cout<<nThreads;
    cpu_set_t set;
    // std::cout<<"\nPinning to Core:"<<coreID;
    CPU_ZERO(&set);

    if(coreID == -1) {
        status=-1;
        std::cout<<"CoreID is -1"<<"\n";
        return status;
    }

    if(coreID > nThreads) {
        std::cout<<"Invalid CORE ID"<<"\n";
        return status;
    }

    CPU_SET(coreID,&set);
    if(sched_setaffinity(0, sizeof(cpu_set_t), &set) < 0) {
        std::cout<<"Unable to Set Affinity"<<"\n";
        return -1;
    }
    return 1;
    #endif
    return -1;
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

unsigned long tacc_rdtscp(int *chip, int *core) {
    unsigned long a,d,c;
    __asm__ volatile("rdtscp" : "=a" (a), "=d" (d), "=c" (c));
    *chip = (c & 0xFFF000)>>12;
    *core = c & 0xFFF;
    return ((unsigned long)a) | (((unsigned long)d) << 32);;
}

// ------ Latencies ------ \\

int latencyOverhead() {
    int output = 0;
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
        asm volatile("#Overhead Latency");
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

//******** DATA ********
bool verbose = 0;
int currTask = 0;
int latencies[500];

int l2_data[L2_SIZE_B/4];                               // Allocate enough space to fill up L2 Cache.

/*
 *      Benchmark Stages:
 *      0   -   Set up Threads using Cores 0 and 15
 *      1   -   Time 1000 Accesses to L2 Data from Core 0.
 *      2   -   Overwrite all the values in L2 Data from Core 0.
 *      3   -   Time the read of the L2 Data from Core 15.
 * 
 */

void readLocalOverwrite(int coreToPin, int overhead) {
    CorePin(coreToPin);
    int core, chip;
    tacc_rdtscp(&chip, &core);
    if (verbose) printf("\nTask 1 Waiting on Core %d", core);

    while (currTask < 1) { /* Pass */ }
    // sleep(1000);

    if (verbose) printf("\nTask 1 Running on Core %d", core);

    /* Perform Task */
        // Overwrite the same Cache lines.
        for (int i = (L2_START_IDX + 0 * STRIDE); i < (L2_START_IDX + 20 * STRIDE); i++) {
            l2_data[i] = 1234;
        }
    /*              */
    
    if (verbose) printf("\nTask 1 Complete on Core %d", core);
    currTask = 2;
    while (currTask < 3) { /* spin */ }    
}

void readRemoteModified(int coreToPin, int overhead) {
    CorePin(coreToPin);
    int core, chip;
    tacc_rdtscp(&chip, &core);
    if (verbose) printf("\nTask 2 Waiting on Core %d", core);

    while (currTask < 2) { /* Pass */ }
    // sleep(1000);
    
    if (verbose) printf("\nTask 2 Running on Core %d", core);

    /* Perform Task */ 
        // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

        start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
        end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

        // Take a starting measurement of the TSC.
        start_timestamp(&start_hi, &start_lo);

        // Perform 6 Loads to L1 Data from different Cache Lines.
            asm volatile (
            "\n\t#1 L1 Load Inst"
            "\n\tmov %1, %0"
            "\n\tmov %3, %2"
            "\n\tmov %5, %4"
            :
            "=r"(l2_data[L2_START_IDX + 0 * STRIDE]),
            "=r"(l2_data[L2_START_IDX + 1 * STRIDE]),
            "=r"(l2_data[L2_START_IDX + 2 * STRIDE])
            
            :
            "r"(l2_data[L2_START_IDX + 0 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 1 * STRIDE]),
            "r"(l2_data[L2_START_IDX + 2 * STRIDE])
            
            :
        );

         // Take an ending measurement of the TSC.
        end_timestamp(&end_hi, &end_lo); 

        // Convert the 4 x 32bit values into 2 x 64bit values.
             start   = ( ((uint64_t)start_hi << 32) | start_lo );
             end     = ( ((uint64_t)end_hi << 32) | end_lo );
        latency = (end - start);

        if (latency < 500) latencies[latency]++;
    /*              */

    if (verbose) printf("\nTask 2 Complete on Core %d", core);
    currTask = 3;
    while (currTask < 3) { /* spin */ }     
}

void deadFunc(int coreToPin) {
    CorePin(coreToPin);
    int core, chip;
    tacc_rdtscp(&chip, &core);
    
    /* Perform Task */
        if (verbose) printf("\nDead Thread Waiting on Core %d", core);
    /*              */

    while (currTask < 3) { /* spin */ }
}

/* Performs Cache Coherence Miss Latencies Benchmarks */
void coherence(int overhead) {
    
    printf("\n\n --- Starting Coherence Benchmarks ---");
    memset(latencies, 0, sizeof(latencies));

    for (int i = 0; i < 1000; i++) {
        currTask = 0;
        if (verbose) printf("\nScheduling tasks");

        /* Create a Thread for each Core */
        std::thread tasks[NUM_CORES];
        for (int i = 0; i < NUM_CORES; i++) {
            if (i == 0)
                tasks[i] = std::thread(readLocalOverwrite, i, overhead);
            else if (i == 1)
                tasks[i] = std::thread(readRemoteModified, 0, overhead);
            else
                tasks[i] = std::thread(deadFunc, i);
        }

        currTask = 1;

        while (currTask < 3) { /* spin */ }
        if (verbose) printf("\n All Tasks Complete");
        for (int i = 0; i < NUM_CORES; i++)
            tasks[i].join();
        if (verbose) printf("\n Wrapped Up");
    }

    /* Produce Output Table */
    printf("\n\tLAT\t|\t3 x L2 Miss");
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
            if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/3.0);
        }
    }

}

int main(int argc, char *argv[]) {
    int overhead = latencyOverhead();
    coherence(overhead);

    printf("\n");
}






// /* Measures the time to load from L1 Cache, prints findings in ASCII Table */
// void foo(int overhead) {
//     // Threads = 256;
//     // Core = 256 % 64

//     CorePin(0);
//     int latencies[500];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
//     memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.
//     int latencies2[500];                                     // i'th element of array indicates how many times an L1 Load took i cycles.
//     memset(latencies2, 0, sizeof(latencies2));                // Initialise count of overhead latencies to 0.

//     // Timing variables.
//         uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
//         uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
//         uint64_t latency;

//     // Do 1000 test runs of timing an L2 Load.
//     printf("\n\n\nTesting L2\n");
//     latency = 0;
//     // volatile int *l2_data = (int*)malloc(L2_SIZE_B);
//     for (int i=0; i < 1000; i++) {
//         asm volatile("CPUID");        
//         CorePin(0);
//         asm volatile("CPUID");
        
//         int l2_data[L2_SIZE_B/4];                               // Allocate enough space to fill up L2 Cache.
//         memset(l2_data, 0, sizeof(l2_data));        
//         warmup();                                           // Warmup timestamping instructions.

//         start_hi = 0; start_lo = 0;                         // Initialise values of start_hi/start_lo so the values are already in L1 Cache.
//         end_hi   = 0; end_lo   = 0;                         // Initialise values of end_hi/end_lo so the values are already in L1 Cache.

//         /*
//          *  L1 Cache: [ | | | ]
//          *                    ^
//          *  L2 Cache: [ | | | | | | | | | | | | | | | ]
//          *                    ^
//          *            Try flush Cache Lines up to here, then read from above
//          *          only so we read from L2 exclusively.
//          * 
//          */
//         // Load all our Data into L1 & L2 Caches.
//         for (int i=L1_START_IDX; i < (L1_SIZE_B/4); i++)             // Access required data beforehand, so that it is in L1 Cache.
//             l2_data[i] = i + 1;
        

//         // Take a starting measurement of the TSC.
//         start_timestamp(&start_hi, &start_lo);

//         // Perform 6 Loads to L1 Data from different Cache Lines.
//         asm volatile (
//             "\n\t#1 L1 Load Inst"
//             "\n\tmov %1, %0"
//             "\n\tmov %3, %2"
//             "\n\tmov %5, %4"
//             :
//             "=r"(l2_data[L2_START_IDX + 0 * STRIDE]),
//             "=r"(l2_data[L2_START_IDX + 1 * STRIDE]),
//             "=r"(l2_data[L2_START_IDX + 2 * STRIDE])
//             :
//             "r"(l2_data[L2_START_IDX + 0 * STRIDE]),
//             "r"(l2_data[L2_START_IDX + 1 * STRIDE]),
//             "r"(l2_data[L2_START_IDX + 2 * STRIDE])
//             :
//         );

//         // Take an ending measurement of the TSC.
//         end_timestamp(&end_hi, &end_lo);   

//         // Convert the 4 x 32bit values into 2 x 64bit values.
//          start   = ( ((uint64_t)start_hi << 32) | start_lo );
//          end     = ( ((uint64_t)end_hi << 32) | end_lo );
//         latency = (end - start);

//         // Increment the appropriate indexes of our latency tracking arrays.
//         if (latency < 500) latencies[latency]++;        // Only increment the latency if its within an acceptable range, otherwise this latency was most likely a random error.
//     }

//     /* Produce Output Table */
//     printf("\n\tLAT\t|\t3 x L2 Hit");
//     printf("\n\t--------+-----------------------");
//     for (int i=0; i < 500; i++) {
//         double perc = (double)latencies[i] / (double)10;
//         if (perc > 1) {
//             int temp, digits;
//             std::cout << "\n";

//             // Latency Column
//             std::cout << "\t" << i << "\t|";

//             // L1 Load Count Column
//             std::cout << "\t" << latencies[i];
//             temp = latencies[i];
//             digits = 0; while (temp != 0) { temp /= 10; digits++; }
//             for (int i=digits; i < 5; i++) {
//                 std::cout << " ";
//             }
//             if (perc > 1) printf("(%.2f%%)", perc);
//             else printf("      ");
//             std::cout << "\t";
//             if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/3.0);
//         }
//     }

//     /* Produce Output Table */
//     printf("\n\tLAT\t|\t3 x L2 Hit");
//     printf("\n\t--------+-----------------------");
//     for (int i=0; i < 500; i++) {
//         double perc = (double)latencies2[i] / (double)10;
//         if (perc > 1) {
//             int temp, digits;
//             std::cout << "\n";

//             // Latency Column
//             std::cout << "\t" << i << "\t|";

//             // L1 Load Count Column
//             std::cout << "\t" << latencies2[i];
//             temp = latencies2[i];
//             digits = 0; while (temp != 0) { temp /= 10; digits++; }
//             for (int i=digits; i < 5; i++) {
//                 std::cout << " ";
//             }
//             if (perc > 1) printf("(%.2f%%)", perc);
//             else printf("      ");
//             std::cout << "\t";
//             if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/3.0);
//         }
//     }

// }