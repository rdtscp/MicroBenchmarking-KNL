#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char *argv[]) {

    printf("\n\t --- Timestamp Test ---");

    uint32_t start_hi, start_lo, end_hi, end_lo;
    uint64_t start, end;

    printf("\n\n\t\tRDTSCP\n\t\t#INSTR HERE\n\t\tRDTSCP\n\n\t[");
    for (int i=0; i < 20; i++) {
        asm volatile ("RDTSCP": "=r"(start_hi), "=r"(start_lo));
	asm volatile ("RDTSCP": "=r"(end_hi), "=r"(end_lo));
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        printf("%lli, ", end - start);
    }
    printf("]");

    printf("\n\n\t\tCPUID\n\t\tRDTSCP\n\t\t#INSTR HERE\n\t\tRDTSCP\n\n\t[");
    for (int i=0; i < 20; i++) {
        asm volatile ("CPUID");
        asm volatile ("RDTSCP": "=r"(start_hi), "=r"(start_lo));
        asm volatile ("RDTSCP": "=r"(end_hi), "=r"(end_lo));
        start   = ( ((uint64_t)start_hi << 32) | start_lo );
        end     = ( ((uint64_t)end_hi << 32) | end_lo );
        printf("%lli, ", end - start);
    }
    printf("]");

    printf("\n");
}
