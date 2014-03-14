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

#ifndef __jacobi22Nov2013__
#define __jacobi22Nov2013__
#include <mpi.h>

class Jacobi2D{
private:
	int nthreads;
	/*
	 * dim1 x dim2 = dimension of data on a single node
	 */
	int dim1;
	int dim2;
	/*
	 * a and b are both dim1 x (dim2+2)
	 * extra column on left = rightmost column of left neighbor
	 * extra column on right = leftmost column of right neighbor
	 * each  iteration updates b[] using a[]
	 */
	double *a, *b;
	/*
	 * lrank = rank of MPI process to the left
	 * rrank = rank of MPI process to the right
	 */
	int lrank;
	int rrank;
	MPI_Request reqlist[4];
	/*
	 * helper function for public members
	 */
	void leftrightinit();
	void initialize(int col1, int col2);
	void update(int col1, int col2);
	void copy(int col1, int col2);
public:
	/*
	 * d1(dim1) must be even
	 * d2(dim2) must be even
	 * even ---> assumed by initializepp() to get chessboard pattern
	 */
	Jacobi2D(int rank, int nprocs, int d1, int d2, int nth);
	~Jacobi2D();
	/*
	 * initialize to chessboard pattern of +/- 1
	 */
	void initializepp();
	void postsendrecv();
	void wait();
	/*
	 * b[] updated using a[]
	 */
	void updatepp();
	/*
	 * copy a[] to b[]
	 */
	void copypp();
	/*
	 * return pointer to data excluding column from left neighbor
	 */
	double* geta(){return a+dim1;}
};

#endif
