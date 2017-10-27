#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Single struct is 16B
struct Cell {
    struct Cell *next;
    int val;
};

struct Cell head;

void init() {
    printf(" --- Initialising --- \n");
    // Set up linked list of cells
    Cell *curr = &head;                              // Declare pointer to head of list => curr == address of head.
    printf("Starting new list @ %p \n", curr);
    for (int i = 0; i < 100; i++) {
        Cell *nextCell = new Cell();
        nextCell->val = 10;
        curr->next = nextCell;      
        printf("Declared new cell @ %p \n", curr->next);
        curr = curr->next;
    }
    curr->val = 10;
    printf(" --- Initialised --- \n");
}

int runTests() {
    printf(" --- Testing --- \n");
    // Fetch the last struct of the list.
    struct Cell *ptr = &head;
    printf("%p \n", ptr);
    while (ptr->next != NULL) {
        printf("%p \n", ptr->next);
        ptr = ptr->next;
    }
    printf("%p \n", ptr->next);
    int x = ptr->val;
    printf(" --- Tested ---\n"); 
    return x;
}

int main() {
    clock_t initTime = time(NULL);
    init();
    clock_t startTime = time(NULL);
    int x = runTests();
    clock_t endTime   = time(NULL);
    printf(" --- Results ---");
    printf("\n    Init: %f", (double)(startTime - initTime) / CLOCKS_PER_SEC);
    printf("\n    Test: %f", (double)(endTime - startTime) / CLOCKS_PER_SEC);
    printf("\n    Val : %d", x);
}



