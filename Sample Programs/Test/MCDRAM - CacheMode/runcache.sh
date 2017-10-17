#!/bin/bash
#PBS -N streams
#PBS -l select=1:aoe=a2a_100
#PBS -l walltime=00:05:00
#PBS -A {budget-code}

cd $PBS_O_WORKDIR
aprun -n 1 -d 1 ./cache