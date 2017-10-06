#!/bin/bash 
#PBS -N xthijob
#PBS -l select=1
#PBS -l walltime=00:10:00
#PBS -A knl-$user

module unload PrgEnv-cray
module load PrgEnv-intel
cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=256
aprun -n 1 -j 4 -d $OMP_NUM_THREADS -cc depth ./xthi
aprun -n 1 numactl -H
