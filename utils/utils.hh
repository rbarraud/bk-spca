#ifndef dvutils25June2013
#define dvutils25June2013
#include <cstdio>
#include <iostream>
#include <fstream>
const double PI = 3.1415926535897932384e+00;

/*
 * (Based on http://stackoverflow.com/questions/5252375/custom-c-assert-macro.)
 * Like assert() in <cassert> but works outside DEBUG mode too.
 */
#define assrt(cond) \
    do \
    { \
	 if (!(cond)) \
	 { \
		  std::cout<<"ASSRT FAILED:"<<#cond<<std::endl	\
			   <<"file: "<<__FILE__<<std::endl	\
			   <<"line: "<<__LINE__<<std::endl;	\
		 __builtin_trap();				\
        } \
    } while(0)  

/*    
 * Returns number of cpus on system.
 */
int num_cpu();

 /*
  * v[i] = fabs(v[i]) for i=0...n-1.
  */
void array_abs(double *v, int n);

/*
 * Returns max of abs values of v[0..n-1].
 */
double array_max(double *v, int n);

 /*
  * Displays n entries of v[] on stdout.
  */
void array_show(double *v, int n, const char* mesg);

/*
 * v[] = v[] - w[].
 */
void array_diff(double *restrict v, double *restrict w, int n);

 /*
  * Copy: w[] = v[].
  */
 void array_copy(double *restrict v, double *restrict w, int n);

/*
 * v[]   : array to be output (column major).
 * m     : num of rows.
 * n     : num of cols .
 * fname : name of file for output.
 *         (Uses stdout if fname == NULL.)
 */
void array_out(double *v, int m, int n, const char *fname = NULL);

 /*
  * Same as above except for lda.
  * i,j th entry : v[i+j*lda]
  * Uses stdout if fname == NULL
  */
void array_out(double *v, int m, int n, int lda, const char *fname = NULL);

/*
 * Counterpart of array_out().
 * size: number of entries of v[].
 */
void array_in(double *v, int size,  const char* fname);

/*
 *   A[]: 2x2 doubles in column major format.
 * rhs[]: 2 doubles.
 *   x[]: soln of Ax=rhs (output).
 */
void solve2x2(double *restrict A, double *restrict rhs, double *restrict x);

 /*
  * Verifies if the directory exists.
  * If it does not, then creates it.
  */
void verify_dir(const char *dir);

/*
 * dir[]: name of directory.
 * pfx[]: file name prefix.
 * Removes all files in directory starting with prefix.
 */
void mop_dir(const char* dir, const char *pfx);


enum link_cout_flag_enum {LC_APP, LC_NOAPP}; 
/*
 * Opens file fname and links its stream to that of cout.
 * flag: LC_APP then file opened for appending.
 * flag: LC_NOAPP then file opened for writing.
 */
void link_cout(const char *fname, enum link_cout_flag_enum flag = LC_NOAPP);

/*
 * Closes file opened with link2cout and restores cout stream.
 */
void unlink_cout();

/*
 * Prints the file to cout (omitting unprintable characters).
 * The contents of the file are put inside a box.
 */
void box_file(const char* fname, const char* mesg);

/*
 * Calls getpid() and uses it to copy /proc/pid/status to std::cout.
 */
void print_proc_status(const char* mesg);


/*
 * Reads shell variable OMP_NUM_THREADS.
 */
int dv_omp_nthreads();
#endif

