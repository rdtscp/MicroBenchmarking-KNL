#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

cpu_set_t mask;

int data_arr[4096];
long a,b,reg_a,reg_b,reg_c,reg_d;

// BenchIT

int get_rdtsc_latency()
{
   unsigned int latency=0xffffffff,i;
   double tmp;

   /*
   * Output : EDX:EAX stop timestamp
   *          ECX:EBX start timestamp
   */
   for(i=0;i<100;i++)
   {
     __asm__ __volatile__(
                //start timestamp
                "rdtsc;"
                "mov %%rax,%%rbx;"
                "mov %%rdx,%%rcx;"
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
                //stop timestamp
                "rdtsc;"
                : "=a" (reg_a), "=b" (reg_b), "=c" (reg_c), "=d" (reg_d)
     );
    a=(reg_d<<32)+(reg_a&0xffffffffULL);
    b=(reg_c<<32)+(reg_b&0xffffffffULL);
    tmp=rint(((double)(a-b))/((double)257));
    if (tmp<latency) latency=(int)tmp;
  }
  return latency;
}

unsigned long long timestamp()
{
  __asm__ __volatile__("rdtsc;": "=a" (reg_a), "=d" (reg_d));
  return (reg_d<<32)|(reg_a&0xffffffffULL);
}

// Me

void init() {
    for (int i = 0; i < 4096; i++) {
        data_arr[i] = 1;
    }
}

inline void assignToCore(int core_id) {
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

uint64_t rdtscp() {
    uint64_t a;
    uint64_t b;
    asm volatile("rdtscp" : "=A"(a));
    asm volatile("rdtscp" : "=A"(b));
    return (b - a);
}

int testL1() {
    volatile int temp = 0;
    uint64_t a;
    uint64_t b;
    uint64_t out;
    for (int i = 0; i < 16; i++) {
        temp = data_arr[i];
    }
    a = timestamp();
    temp = data_arr[0];                     // This value has already been fetched in above loop, so should exist in L1 Cache
    b = timestamp();
    out = b - a;
    return out;
}

int testDiv() {
    int x = 10;
    int y = 2;
    int a, b, z;
    a = timestamp();
    z = x / y;
    b = timestamp();
    return b-a;
}

int main() {    
    uint64_t testL1_Avg     = 0;
    uint64_t testDiv_Avg    = 0;

    init();    

    assignToCore(0);

    // Test L1 Cache Hit
    int cacheL1Tests = 1000000;     // 1 Million
    for (int i = 0; i < cacheL1Tests; i++) {
        testL1_Avg += testL1();
    }
    testL1_Avg = testL1_Avg / cacheL1Tests;

    // Test Div Operation
    int divTests = 1000000;
    for (int i = 0; i < divTests; i++) {
        testDiv_Avg += testDiv();
    }
    testDiv_Avg = testDiv_Avg / divTests;

    printf(" --- CYCLES ---\n");
    printf("RDTSC Overhead:\t\t%d\n", get_rdtsc_latency());
    printf("L1 Cache Hit:\t\t%d\n", testL1_Avg);
    printf("DIV Cycles:\t\t%d\n", testDiv_Avg);
}


