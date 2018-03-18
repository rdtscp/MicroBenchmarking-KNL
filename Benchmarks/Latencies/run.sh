#!/bin/bash

if [ -z "$1" ]
  then
    echo "./run.sh {0,1} "
    echo "No argument supplied"
    echo "  0 - DDR"
    echo "  1 - MCDRAM"
    exit 1
fi

export OMP_PROC_BIND=true
OMP_NUM_THREADS=1   numactl --membind $1 ./latencies.o $1