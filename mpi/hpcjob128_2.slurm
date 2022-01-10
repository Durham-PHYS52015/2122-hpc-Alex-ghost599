#!/bin/bash 
#SBATCH --job-name="myjob_128_2"
#SBATCH -o myjob_128_2.%A.out
#SBATCH -e myjob_128_2.%A.err
#SBATCH -p par7.q
#SBATCH -t 03:10:00
#SBATCH --nodes=1
#SBATCH -n 2
#SBATCH --mail-type=ALL
#SBATCH --mail-user=lsxm74@durham.ac.uk

source /etc/profile.d/modules.sh

module load intelmpi/gcc/2019.6
module load gcc/9.3.0

mpiexec -n 128 ./main -N 65536 -t BENCH
mpiexec -n 128 ./main -N 131072 -t BENCH
mpiexec -n 128 ./main -N 262144 -t BENCH
mpiexec -n 128 ./main -N 524288 -t BENCH
mpiexec -n 128 ./main -N 1048576 -t BENCH
mpiexec -n 128 ./main -N 2097152 -t BENCH
