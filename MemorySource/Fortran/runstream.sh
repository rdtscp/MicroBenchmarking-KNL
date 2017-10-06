#!/bin/bash
#PBS -N streams
#PBS -l select=1:aoe=quad_100
#PBS -l walltime=00:05:00
#PBS -A knl-$user

cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=256
aprun -n 1 -j 4 -d $OMP_NUM_THREADS -cc depth ./stream_d
