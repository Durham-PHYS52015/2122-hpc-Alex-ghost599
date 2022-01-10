#!/bin/bash 
#SBATCH --job-name="myjob_16"
#SBATCH -o myjob_16.%A.out
#SBATCH -e myjob_16.%A.err
#SBATCH -p par7.q
#SBATCH -t 03:10:00
#SBATCH --nodes=1
#SBATCH --cpus-per-task=24
#SBATCH --mail-type=ALL
#SBATCH --mail-user=lsxm74@durham.ac.uk

source /etc/profile.d/modules.sh

module load intelmpi/gcc/2019.6
module load gcc/9.3.0

mpiexec -n 16 ./main -N 1 -t BENCH
mpiexec -n 16 ./main -N 2 -t BENCH
mpiexec -n 16 ./main -N 4 -t BENCH
mpiexec -n 16 ./main -N 8 -t BENCH
mpiexec -n 16 ./main -N 16 -t BENCH
mpiexec -n 16 ./main -N 32 -t BENCH
mpiexec -n 16 ./main -N 64 -t BENCH
mpiexec -n 16 ./main -N 128 -t BENCH
mpiexec -n 16 ./main -N 256 -t BENCH
mpiexec -n 16 ./main -N 512 -t BENCH
mpiexec -n 16 ./main -N 1024 -t BENCH
mpiexec -n 16 ./main -N 2048 -t BENCH
mpiexec -n 16 ./main -N 4096 -t BENCH
mpiexec -n 16 ./main -N 8192 -t BENCH
mpiexec -n 16 ./main -N 16384 -t BENCH
mpiexec -n 16 ./main -N 32768 -t BENCH
mpiexec -n 16 ./main -N 65536 -t BENCH
mpiexec -n 16 ./main -N 131072 -t BENCH
mpiexec -n 16 ./main -N 262144 -t BENCH
mpiexec -n 16 ./main -N 524288 -t BENCH
mpiexec -n 16 ./main -N 1048576 -t BENCH
mpiexec -n 16 ./main -N 2097152 -t BENCH
mpiexec -n 16 ./main -N 4194304 -t BENCH
mpiexec -n 16 ./main -N 8388608 -t BENCH
mpiexec -n 16 ./main -N 16777216 -t BENCH
