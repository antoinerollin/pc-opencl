#ifndef VERS0_H
#define VERS0_H

#include "matrix.h"
#include "project.h"

/** Process n_iter iterations. */
void main_v0(int n_iter, Matrix * matrix_src, Matrix * matrix_dst);

/** Apply one iteration process. */
void process_v0(Matrix* matrix_src, Matrix* matrix_dst);

/**
 * Apply one iteration process on the destination matrix according to
 * the source matrix and the direction (horizontally or vertically).
 */
void directed_process_v0(Matrix* matrix_src, Matrix* matrix_dst, int direction);

/** Process the line/column at the index. */
void compute_line_or_column_at_index_v0(Matrix* matrix_src, Matrix* matrix_dst, int direction, int index);

#endif // VERS0_H
