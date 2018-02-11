#!/bin/bash

if [ -z "$1" ]
  then
    echo "No argument supplied"
    echo "  0 - DDR"
    echo "  1 - MCDRAM"
    exit 1
fi

export OMP_PROC_BIND=true
cc stream.c -O3 -o stream -fopenmp -DSTREAM_ARRAY_SIZE=64000000

echo "+  1  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=1   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+  2  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=2   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+  4  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=4   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+  8  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=8   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+ 16  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=16   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+ 32  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=32   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+ 64  Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=64   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+ 128 Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=128   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"
echo "+ 256 Thread(s)    MB/s     Avg time     Min time     Max time +"
OMP_NUM_THREADS=256   numactl --membind $1 ./stream | grep Triad -B 3
echo "+--------------------------------------------------------------+"