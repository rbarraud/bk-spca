/*
 * Copyright Divakar Viswanath, 2009-2014
 */

/*     
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as 
 * published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "../utils/utils.hh"
#include "mpi_init.hh"
#include <mpi.h>
#include <cstdio>

enum gl_mpi_onoff_enum gl_mpi_onoff = MPIOFF;

void mpi_initialize(int& rank, int& nprocs){
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	gl_mpi_onoff = MPION;
}

void mpi_finalize(){
	MPI_Finalize();
	gl_mpi_onoff = MPIOFF;
}

void BlockDivide(long n, int P, long *fst){
	long  Q = n/P;
	long  R = n-Q*P;
	fst[0] = 0;
	for(int p=0; p < R; p++)
		fst[p+1] = fst[p] + (Q+1);
	for(int p=R; p < P; p++)
		fst[p+1] = fst[p]+Q;
}

