#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <sys/mman.h>

int data[2048];

int main() {
    memset(data, 0, 2048);

}