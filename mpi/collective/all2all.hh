#ifndef all2all26NOV2013
#define all2all26NOV2013
#include <mpi.h>

/*
 * Every proc sends n doubles to every other proc.
 * Makes a single mpi call.
 */
double mpi_all2all(int rank, int nprocs, 
		   double *sendbuf, double *recvbuf, int n);

/*
 * Same as above but implemented using MPI_Scatter.
 */
double scatter_all2all(int rank, int nprocs, 
		       double *sendbuf, double *recvbuf, int n);

/*
 * Same as above implemented using send/recv.
 */
MPI_Request *all2all_init(int rank, int nprocs, 
			  double *sendbuf, double *recvbuf, int n);
double all2all(int rank, int nprocs, MPI_Request* reqlist);
void all2all_finalize(MPI_Request *reqlist);

#endif

