#!/bin/bash

export OMP_PROC_BIND=true
OMP_NUM_THREADS=64
OMP_PLACES=cores

numactl ./coherence_latencies.o