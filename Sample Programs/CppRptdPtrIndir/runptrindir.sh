#!/bin/bash
#PBS -N ptrtests
#PBS -l select=1:aoe=quad_100
#PBS -l walltime=00:05:00
#PBS -A {redacted}

cd $PBS_O_WORKDIR
aprun -n 1 -d 1 ./prog