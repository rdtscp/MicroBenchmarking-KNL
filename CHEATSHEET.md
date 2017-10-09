## Login
ssh -l {username} login.archer.ac.uk
ssh knl-login

## Copy Files
scp ./{file}.tar.gz {username}@login.archer.ac.uk:

scp {file}.tar.gz knl-login:/work/knl-users/$USER/

## File Locations
/work/knl-users/$USER

## Compiling
module swap PrgEnv-cray PrgEnv-intel


## Submitting Jobs
 * qsub {batch script}.sh

{batch script}.sh should be of form:

```
#!/bin/bash
#PBS -N streams
#PBS -l select=1:aoe=quad_100
#PBS -l walltime=00:05:00
#PBS -A {budget account}

cd $PBS_O_WORKDIR
aprun -n {number of KNL nodes to use} -d {number of threads} ./{application executable}
```