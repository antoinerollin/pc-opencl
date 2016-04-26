#ifndef VER_H
#define VER_H

#include "matrix.h"
#include "region.h"

/**
 * Apply one iteration process on a region of the destination matrix according to
 * the source matrix and the direction (horizontally or vertically).
 */
void directed_process(Matrix* matrix_src, Matrix* matrix_dst, int direction, Region * region);

/** Process the line/column at the index. */
void compute_line_or_column_at_index(Matrix* matrix_src, Matrix* matrix_dst, int direction, int index, Region * region);


#endif // VER_H
