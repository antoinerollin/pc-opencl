#include "version.h"

/**
 * Apply one iteration process on a region of the destination matrix according to
 * the source matrix and the direction (horizontally or vertically).
 */
void directed_process(Matrix* matrix_src, Matrix* matrix_dst, int direction, Region * region)
{

    int variant = (direction == VERTICAL) ? region->x : region->y;

    // Process each line OR column of the region
    for(int i = variant; i < (variant + region->width); i++)
        compute_line_or_column_at_index(matrix_src, matrix_dst, direction, i, region);

}

/**
 *  Process the index-ieme line/column (direction) on a region.
 */
void compute_line_or_column_at_index(Matrix* matrix_src, Matrix* matrix_dst, int direction, int index, Region * region)
{
    // Cells required for Taylor formula
    float aim, adj1, adj2;

    int variant2 = (direction == VERTICAL) ? region->y : region->x;

    // For each cell of the line/column
    for (int mutant = variant2; mutant < (variant2 + region->width); mutant++) {
        if (direction == VERTICAL) { // COLUMN
            // Previous aimed cell value
            aim = MCELL(matrix_src, index, mutant);

            // Neighbors values
            adj1 = (mutant >= 1) ? MCELL(matrix_src, index, (mutant-1)) : TEMP_COLD;
            adj2 = (mutant < matrix_dst->size-1) ? MCELL(matrix_src, index, (mutant+1)) : TEMP_COLD;

            // Computes the new value
            MCELL(matrix_dst, index, mutant) = apply_taylor(aim, adj1, adj2);

        } else if (direction == HORIZONTAL) { // LINE
            // Previous aimed cell value
            aim = MCELL(matrix_src, mutant, index);

            // Neighbors values
            adj1 = (mutant >= 1) ? MCELL(matrix_src, (mutant-1), index) : TEMP_COLD;
            adj2 = (mutant < matrix_dst->size-1) ? MCELL(matrix_src, (mutant+1), index) : TEMP_COLD;

            // Computes the new value
            MCELL(matrix_dst, mutant, index) = apply_taylor(aim, adj1, adj2);
        }
    }
}
