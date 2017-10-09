## Login
ssh -l {username} login.archer.ac.uk
ssh knl-login

## Copy Files
scp ./{file}.tar.gz {username}@login.archer.ac.uk:

scp {file}.tar.gz knl-login:/work/knl-users/$USER/

## Compiling
module swap PrgEnv-cray PrgEnv-intel
