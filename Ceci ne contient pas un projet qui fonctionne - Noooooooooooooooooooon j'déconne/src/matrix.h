#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "project.h"
#include "utils.h"

#define MINDEX(m, i, j) (i * m->size + j)
#define MCELL(m, i, j) m->mtx[MINDEX(m, i, j)]

#define VERTICAL        0
#define HORIZONTAL      1

/** Matrix struct. */
typedef struct Matrix {
    float* mtx;
    int factor;
    int size;
} Matrix;

/** Create the matrix. */
Matrix* create_matrix(int factor);

/** Free the matrix. */
void free_matrix(Matrix* matrix);

/** Print the matrix. */
void print_matrix(Matrix* matrix);

/** Set the matrix values to 0 */
void init_matrix(Matrix * m);

// =============

/** Init the center of the matrix. */
void apply_heat_center(Matrix* matrix, int value);

/** Sum of all matrix values. */
float matrix_sumvalue(Matrix* m);

// =============

#endif // MATRIX_H
