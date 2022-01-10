#!/bin/bash 
#SBATCH --job-name="myjob_128_3"
#SBATCH -o myjob_128_3.%A.out
#SBATCH -e myjob_128_3.%A.err
#SBATCH -p par7.q
#SBATCH -t 03:10:00
#SBATCH --nodes=1
#SBATCH -n 2
#SBATCH --mail-type=ALL
#SBATCH --mail-user=lsxm74@durham.ac.uk

source /etc/profile.d/modules.sh

module load intelmpi/gcc/2019.6
module load gcc/9.3.0

mpiexec -n 128 ./main -N 4194304 -t BENCH
mpiexec -n 128 ./main -N 8388608 -t BENCH
mpiexec -n 128 ./main -N 16777216 -t BENCH
