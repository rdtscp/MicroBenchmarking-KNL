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
#include <atomic>




#ifdef __linux__    // Linux only
    #include <sched.h>  // sched_setaffinity
    #include <omp.h>
    cpu_set_t mask;
#endif
/*
 *  Put your Definitions Below
 */
#define L1_SIZE_B           262144
#define L2_SIZE_B           1048576
#define LINE_SIZE_B         64

int NUM_CORES               = 64;
int BASE_CORE               = 0;
int TARGET_CORE             = 63;

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



//******** DATA ********
bool verbose = 0;
int currTask = 0;
int iteration = 0;
int latencies[500];

static int shared_data[L2_SIZE_B/4];                        // Allocate enough space to fill up L2 Cache.

// Timing variables.
uint32_t start_hi, start_lo, end_hi, end_lo;                // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
uint64_t start, end;                                        // 64bit integers to hold the start/end timestamp counter values.
uint64_t latency;

/*
 *      Benchmark Stages:
 *      0   -   Set up Threads using Cores 0 and 15
 *      1   -   Time 1000 Accesses to L2 Data from Core 0.
 *      2   -   Overwrite all the values in L2 Data from Core 0.
 *      3   -   Time the read of the L2 Data from Core 15.
 * 
 */

/* Measures the time to load from L1 Cache, prints findings in ASCII Table */
void setModified(int coreNum, int runState) {
    CorePin(coreNum);

    // While we are on a valid task, continue running.
    while (currTask != -1) {
        // If its this Task's turn.
        if (currTask == runState) {   

            /* Payload */
                for (int i=0; i < (6 * STRIDE); i++) {             // Access required data beforehand, so that it is in L1 Cache.
                    shared_data[i] = i + 1;
                }
            /***********/

            asm volatile("MFENCE");
            currTask++;
        }
    }

}

void setExclusive(int coreNum, int runState) {
    CorePin(coreNum);

    // While we are on a valid task, continue running.
    while (currTask != -1) {
        // If its this Task's turn.
        if (currTask == runState) {

            /* Payload */
                volatile int temp = 0;
                for (int i=0; i < (6 * STRIDE); i++) {             // Access required data beforehand, so that it is in L1 Cache.
                    temp = shared_data[i];
                    temp += 1;                                     // Use temp
                }
            /***********/

            asm volatile("MFENCE");
            currTask++;
        }
    }

}

void setShared(int coreNum, int runState) {
    CorePin(coreNum);

    // While we are on a valid task, continue running.
    while (currTask != -1) {
        // If its this Task's turn.
        if (currTask == runState) {

            /* Payload */
                volatile int temp = 0;
                for (int i=0; i < (6 * STRIDE); i++) {             // Access required data beforehand, so that it is in L1 Cache.
                    temp = shared_data[i];
                    temp += 1;                                     // Use temp
                }
            /***********/

            asm volatile("MFENCE");
            currTask++;
        }
    }

}

void timeAccess(int coreNum, int runState) {
    CorePin(coreNum);
    
    // While we are on a valid task, continue running.
    while (currTask != -1) {
        // If its this Task's turn.
        if (currTask  == runState) {
    
            /* Payload */
                start_hi = 0; end_hi = 0;
                start_lo = 0; end_lo = 0;

                asm volatile("MFENCE");
                // Take a starting measurement of the TSC.
                start_timestamp(&start_hi, &start_lo);

                // Perform 6 Loads to L1 Data from different Cache Lines.
                asm volatile (
                    "\n\t#1 L1 Load Inst"
                    "\n\tmov %1, %0"
                    "\n\t MFENCE"
                    "\n\tmov %3, %2"
                    "\n\t MFENCE"
                    "\n\tmov %5, %4"
                    "\n\t MFENCE"
                    "\n\tmov %7, %6"
                    "\n\t MFENCE"
                    :
                    "=r"(shared_data[0 * STRIDE]),
                    "=r"(shared_data[1 * STRIDE]),
                    "=r"(shared_data[2 * STRIDE]),
                    "=r"(shared_data[3 * STRIDE])
                    :
                    "r"(shared_data[0 * STRIDE]),
                    "r"(shared_data[1 * STRIDE]),
                    "r"(shared_data[2 * STRIDE]),
                    "r"(shared_data[3 * STRIDE])
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

            /***********/

            currTask++;
        }
    }

}


void deadFunc(int coreToPin) {
    CorePin(coreToPin);

    // printf("\nDead Task Running on Core %d", sched_getcpu());
    
    /* Perform Task */
        // Nothing...
    /*              */

    while (currTask != -1) { /* Spin */ }
}


int timingOverhead() {
    int output = 0;
    int latencies[500];                                     // i'th element of array indicates how many times a NOP took i cycles.
    memset(latencies, 0, sizeof(latencies));                // Initialise count of overhead latencies to 0.

    // Timing variables.
        uint32_t start_hi, start_lo, end_hi, end_lo;        // 32bit integers to hold the high/low 32 bits of start/end timestamp counter values.
        uint64_t start, end;                                // 64bit integers to hold the start/end timestamp counter values.
        uint64_t latency;

    // Do 1000 test runs of gathering the overhead.
    printf("\n\n\n  --- \tTesting Overhead\n");
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
        // asm volatile("MFENCE");
        // asm volatile("MFENCE");
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

/* Performs Remote Read to Modified Line Benchmarks */
void remoteModified(int overhead) {
    double num_loads = 4.0;
    currTask = 0;
    
    printf("\n\n\n  --- \tMeasure Remote Modified Lines\n");
    printf("\n\t => Target Core: %d\n", TARGET_CORE);
    memset(latencies, 0, sizeof(latencies));

    /* Spin Up Thread for each Core */
    std::vector<std::thread> tasks;
    for (int i = 0; i < NUM_CORES; i++) {
        bool set = false;
        if (i == BASE_CORE) {
            printf("\n\t => Pinning setModified to\tCore %d", i);
            tasks.push_back(std::thread(setModified, i, 1));
            set = true;
        }
        if (i == TARGET_CORE) {
            printf("\n\t => Pinning timeAccess  to\tCore %d", i);
            tasks.push_back(std::thread(timeAccess, i, 2));
            if (set) i++;
            set = true;
        }
        if (set) continue;
        tasks.push_back(std::thread(deadFunc, i));
    }

    /* Perform 1000 Experiments */
    for (int i = 0; i < 1000; i++) {
        currTask = 0;
        memset(shared_data, 0, sizeof(shared_data));
        currTask = 1;

        /* Threads Take Over */
        
        while (currTask != 3) { /* Wait for Threads to complete Tasks, then start again. */ }
    }

    currTask = -1;  // Mark All Threads Complete

    // Terminate safely.
    for (int i = 0; i < tasks.size(); i++)
        tasks[i].join();

    tasks.clear();
    printf("\n\n");
    /* Produce Output Table */
    printf("\n\tLAT\t|\t4 x Remote L2 Modified");
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
            if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/num_loads);
        }
    }

}

/* Performs Remote Read to Exclusive Line Benchmarks */
void remoteExclusive(int overhead) {
    double num_loads = 4.0;
    currTask = 0;
    
    printf("\n\n\n  --- \tMeasure Remote Exclusive Lines\n");
    printf("\n\t => Target Core: %d\n", TARGET_CORE);
    memset(latencies, 0, sizeof(latencies));

    /* Spin Up Thread for each Core */
    std::vector<std::thread> tasks;

    for (int i = 0; i < NUM_CORES; i++) {
        bool set = false;
        if (i == BASE_CORE) {
            printf("\n\t => Pinning setExclusive to\tCore %d", i);
            tasks.push_back(std::thread(setExclusive, i, 1));
            set = true;
        }
        if (i == TARGET_CORE) {
            printf("\n\t => Pinning timeAccess to\tCore %d", i);
            tasks.push_back(std::thread(timeAccess, i, 2));
            if (set) i++;
            set = true;
        }
        if (set) continue;
        tasks.push_back(std::thread(deadFunc, i));
    }

    /* Perform 1000 Experiments */
    for (int i = 0; i < 1000; i++) {
        currTask = 0;
        memset(shared_data, 0, sizeof(shared_data));
        currTask = 1;

        /* Threads Take Over */
        
        while (currTask != 3) { /* Wait for Threads to complete Tasks, then start again. */ }
    }

    currTask = -1;  // Mark All Threads Complete

    // Terminate safely.
    for (int i = 0; i < tasks.size(); i++)
        tasks[i].join();

    tasks.clear();
    printf("\n\n");
    /* Produce Output Table */
    printf("\n\tLAT\t|\t4 x Remote L2 Exclusive");
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
            if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/num_loads);
        }
    }

}

/* Performs Remote Read to Shared Line Benchmarks */
void remoteShared(int overhead) {
    double num_loads = 4.0;
    currTask = 0;
    
    printf("\n\n\n  --- \tMeasure Remote Shared Lines\n");
    printf("\n\t => Target Core: %d\n", TARGET_CORE);
    memset(latencies, 0, sizeof(latencies));

    /* Spin Up Thread for each Core */
    std::vector<std::thread> tasks;
    int shareCore = 1;
    if (shareCore == TARGET_CORE) shareCore++;
    for (int i = 0; i < NUM_CORES; i++) {
        bool set = false;
        if (i == BASE_CORE) {
            printf("\n\t => Pinning setExclusive to\tCore %d", i);
            tasks.push_back(std::thread(setExclusive, i, 1));
            set = true;
        }
        if (i == shareCore) {
            printf("\n\t => Pinning setShared to\tCore %d", i);
            tasks.push_back(std::thread(setShared, i, 2));
            set = true;
        }
        if (i == TARGET_CORE) {
            printf("\n\t => Pinning timeAccess to\tCore %d", i);
            tasks.push_back(std::thread(timeAccess, i, 3));
            if (set) i++;
            set = true;
        }
        if (set) continue;
        tasks.push_back(std::thread(deadFunc, i));
    }

    /* Perform 1000 Experiments */
    for (int i = 0; i < 1000; i++) {
        currTask = 0;
        memset(shared_data, 0, sizeof(shared_data));
        currTask = 1;

        /* Threads Take Over */
        
        while (currTask != 4) { /* Wait for Threads to complete Tasks, then start again. */ }
    }

    currTask = -1;  // Mark All Threads Complete

    // Terminate safely.
    for (int i = 0; i < tasks.size(); i++)
        tasks[i].join();

    tasks.clear();   
    printf("\n\n"); 
    /* Produce Output Table */
    printf("\n\tLAT\t|\t4 x Remote L2 Exclusive");
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
            if (perc > 50) printf(" --> %d Cycles => %.2f Cycles Per Load", i, (double)(i - overhead)/num_loads);
        }
    }

}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("\nIncorrect Arguments Provided:");
        printf("\n\t./run.sh READ_STATE TARGET_CORE");
        printf("\n\nWhere READ_STATE = [ M | E | S ]\n\n");
        return 0;
    }

    if (argc > 2)
        TARGET_CORE = atoi(argv[2]);   // Parse Parameters

    if (argv[1] == std::string("M")) {
        printf("\n//------ Testing Remote Modified Read ------\\\\");
        remoteModified(timingOverhead());
        printf("\n\n\\\\------------------------------------------//");
    }
    else if (argv[1] == std::string("E")) {
        printf("\n//------ Testing Remote Exclusive Read ------\\\\");
        remoteExclusive(timingOverhead());
        printf("\n\n\\\\------------------------------------------//");
    }
    else if (argv[1] == std::string("S")) {
        printf("\n//------ Testing Remote Shared Read ------\\\\");
        remoteShared(timingOverhead());
        printf("\n\n\\\\------------------------------------------//");
    }
    else {
        printf("\nInvalid Remote Read State Supplied");
    }

    printf("\n");
}