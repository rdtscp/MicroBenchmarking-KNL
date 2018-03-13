#!/bin/bash

export OMP_PROC_BIND=true
OMP_NUM_THREADS=64
OMP_PLACES='cores(64)'
OMP_PROC_BIND=spread

numactl ./coherence_latencies.o