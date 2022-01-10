#include <mpi.h>
#include <stdio.h>
#include "reduce.h"
#include "utils.h"

/* This is the implementation that we came up with in the exercises for
   MPI_SUM. */
int ring_allreduce(const int *sendbuf, int *recvbuf, int count, MPI_Op op,
                   MPI_Comm comm)
{
  int rank, size;
  int i, c;
  int ierr;
  int source;
  int dest;

  if (op != MPI_SUM) {
    fprintf(stderr, "Only coded for op == MPI_SUM\n");
    return MPI_Abort(comm, 1);
  }
  ierr = MPI_Comm_rank(comm, &rank);CHKERR(ierr);
  ierr = MPI_Comm_size(comm, &size);CHKERR(ierr);

  source = (rank + size - 1) % size;
  dest = (rank + 1) % size;
  for (c = 0; c < count; c++) {
    recvbuf[c] = sendbuf[c];
  }
  for (i = 0; i < size - 1; i++) {
    ierr = MPI_Sendrecv_replace(recvbuf, count, MPI_INT, dest, 0, source, 0, comm, MPI_STATUS_IGNORE);CHKERR(ierr);
    /* Only correct for op == MPI_SUM */
    for (c = 0; c < count; c++) {
      recvbuf[c] += sendbuf[c];
    }
  }
  return 0;
}

int tree_allreduce(const int *sendbuf, int *recvbuf, int count, MPI_Op op,
                   MPI_Comm comm)
{
  /* You should implement the tree reduction here, you should handle
     MPI_SUM, MPI_PROD, MPI_MIN, and MPI_MAX for the MPI_Op
     argument. */
    int rank, size;
    int c, ierr;
    int temps1[count], temps2[count];
    int remain, half;
    ierr = MPI_Comm_rank(comm, &rank);CHKERR(ierr);
    ierr = MPI_Comm_size(comm, &size);CHKERR(ierr);
    remain = size;
    for (c = 0; c < count; c++) {
      recvbuf[c] = sendbuf[c];
      temps1[c] = sendbuf[c];
    }

    

    while (remain != 1)
    {
      half = remain/2;
      if (rank<half){
        ierr = MPI_Recv(&temps2, count, MPI_INT, rank+half, 0, comm, MPI_STATUS_IGNORE);CHKERR(ierr);
        for (c = 0; c < count; c++){
          if (op == MPI_SUM){
            recvbuf[c] += temps2[c];
          }else if (op == MPI_PROD){
            recvbuf[c] *= temps2[c];
          }else if (op == MPI_MIN){
            if (recvbuf[c]>temps2[c]){
              recvbuf[c] = temps2[c];
            }  
          }else if (op == MPI_MAX){
            if (recvbuf[c]<temps2[c]){
              recvbuf[c] = temps2[c];
            } 
          }
        }
        for (c = 0; c < count; c++) {
          temps1[c] = recvbuf[c];
        }
      }else if(rank>=half && rank < remain){
        ierr = MPI_Send(&temps1, count, MPI_INT, rank-half, 0, comm);CHKERR(ierr);
        remain = half;
        break;
      }
      remain = half;
    }

    while (remain!=size)
    {
      half = remain;
      remain *= 2;
      if (rank<half)
      {
        ierr = MPI_Send(&temps1, count, MPI_INT, rank+half, 0, comm);CHKERR(ierr);
      }else if(rank>=half && rank < remain)
      {
        ierr = MPI_Recv(&temps2, count, MPI_INT, rank-half, 0, comm, MPI_STATUS_IGNORE);CHKERR(ierr);
        for (c = 0; c < count; c++) {
          recvbuf[c] = temps2[c];
          temps1[c] = temps2[c];
        }
      } 
    }
    
    
  return 0;
}
