/*  Compile:
 *      g++ -O0 -std=c++11 prog.cpp -o prog
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// Single struct is 16B
struct Cell {
    struct Cell *next;
    int val;
};

int mem_fill_blocks = 400 * 64 * 1024;  // Number of 16B structs to make.
int l1_cache_blocks = 2 * 1024;         // Number of 16B structs to fill L1 Cache.
int l2_cache_blocks = 1024 * 64;        // Number of 16B structs to fill L2 Cache.

Cell head;

void init() {
    printf(" --- Initialising --- \n");
    // Set up linked list of cells
    Cell *curr = &head;                              // Declare pointer to head of list => curr == address of head.
    printf("Starting new list @ %p \n", curr);
    for (int i = 0; i < mem_fill_blocks; i++) {
        Cell *nextCell = new Cell();
        curr->next = nextCell;
        // Second last
        if (i == mem_fill_blocks - 1) curr->val = 99;
        // Last read of L1 Cache
        if (i == l1_cache_blocks - 1) curr->val = 1;
        // Last read of L2 Cache
        if (i == l2_cache_blocks - 1) curr->val = 2;
        curr = curr->next;
    }
    printf(" --- Block Numbers ---\n");
    printf("     L2 Cache Starts at cell: %d", (4 * 1024));
    printf("\n     DRAM Starts at cell: %d", ((64 *  1024 + 2 * 1024 * 1024)/16));
    printf("\n --- Initialised --- \n");
}

int runTests() {
    printf(" --- Testing --- \n");
    // Fetch the last struct of the list.
    struct Cell *ptr = &head;
    auto t0 = std::chrono::steady_clock::now();
    while (ptr->next != NULL) {
        ptr = ptr->next;
        if (ptr->val != 0) {
            int level = ptr->val;
            auto t1 = std::chrono::steady_clock::now();
            ptr = ptr->next;
            auto t2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> lastread = t2 - t1;
            std::cout << "First Read, Level " << level++ << ": " << lastread.count() << '\n';
            if (level == 99) return 0;
        }
    }
    printf(" --- Tested ---\n");
    return 1;
}

/*
 *  Solution for reading processes memory usage: https://stackoverflow.com/a/64166
 */
int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int main() {
    init();
    runTests();
    printf(" --- Finished ---\n");
    printf(" --- Memory Usage --- \n");
    int mem_usg = getValue();
    printf("    - Physical by Curr Proc: %dKB\n", mem_usg);
}