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
  return 0;
}
