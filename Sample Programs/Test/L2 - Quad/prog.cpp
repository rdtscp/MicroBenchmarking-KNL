#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

cpu_set_t mask;

int data_arr[4096];

inline void assignToCore(int core_id) {
    CPU_ZERO(&mask);
    CPU_SET(core_id, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

void init() {
    for (int i = 0; i < 4096; i++) {
        data_arr[i] = 1;
    }
}

int test() {
    int temp = 0;
    uint64_t a;
    uint64_t b;
    uint64_t out;
    for (int i = 0; i < 4096; i++) {
        temp = data_arr[i];
        if (i == 2047) {
            asm("rdtscp" : "=A"(a));
            temp = data_arr[i+1];
            asm("rdtscp" : "=A"(b));
            out = b - a;
        }
    }
    return out;
}


int main() {
    assignToCore(0);
    init();
    long long test_average = 0;
    for (int i = 0; i < 1000000; i++) {
        test_average += test();
    }
    test_average = test_average / 1000000;
    printf("Average cycles for L1 Cache Access: %d\n", test_average);
}