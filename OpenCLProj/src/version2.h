#ifndef VERS2_H
#define VERS2_H

#include "matrix.h"
#include "project.h"
#include "region.h"
#include "version.h"
#include "argument.h"
#include "condbarrier.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/** Divides in regions and initializes barrier, then launch process. */
void main_v2(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads);

/** Launch threads and manage the matrix heat. */
void process_v2(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter);

/** Thread function : process vertically then horizontally  in a region of the matrix */
void * thread_func_v2 (void * p) ;

/** Acquire & release critical cection according to the caller */
void acquire_v2(int direction);
void release_v2(int direction);

#endif // VERS2_H
