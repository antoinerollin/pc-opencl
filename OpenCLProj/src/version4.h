#ifndef VERS4_H
#define VERS4_H

#include "matrix.h"
#include "project.h"
#include "region.h"
#include "argument.h"
#include "version.h"
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>	
#endif
 

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


/** Divides in regions and initializes barrier, then launch process. */
void main_v4(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads);

/** Launch threads and manage the matrix heat. */
void process_v4(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter);

/** Thread function : process vertically then horizontally  in a region of the matrix */
void * thread_func_v4(void * p) ;

/** Acquire & release critical cection according to the caller */
void acquire_v4(int direction);
void release_v4(int direction);

#endif // VERS4_H
