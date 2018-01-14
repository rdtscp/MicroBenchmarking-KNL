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
 
 #include <memory>
 
 int arr [1000];

 void test() {
    int x;
    for (int i = 0; i < 1000; i++) {
        auto t1 = std::chrono::steady_clock::now();
        x = arr[i];
        auto t2 = std::chrono::steady_clock::now();
        printf("%d\n", x);
    }
 }
 
 int main() {
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1;
    }
    test();
 }