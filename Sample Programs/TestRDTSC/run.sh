#!/bin/bash
g++ prog10.cpp
./a.out
g++ prog50.cpp
./a.out
g++ prog100.cpp
./a.out
g++ prog10_repeat.cpp
./a.out
g++ prog50_repeat.cpp
./a.out
g++ prog100_repeat.cpp
./a.out

echo " --- Stack Overflow ---"
g++ stack_overflow.cpp &> /dev/null
./a.out 1> /dev/null