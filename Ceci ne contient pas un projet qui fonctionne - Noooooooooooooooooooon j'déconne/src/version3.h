#ifndef VERS3_H
#define VERS3_H

#include "matrix.h"
#include "project.h"
#include "region.h"
#include "version.h"
#include "argument.h"
#include "sembarrier.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/** Divides in regions and initializes barrier, then launch process. */
void main_v3(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads);

/** Launch threads and manage the matrix heat. */
void process_v3(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter);

/** Thread function : process vertically then horizontally  in a region of the matrix */
void * thread_func_v3 (void * p) ;

/** Acquire & release critical cection according to the caller */
void acquire_v3(int direction);
void release_v3(int direction);

#endif // VERS3_H
