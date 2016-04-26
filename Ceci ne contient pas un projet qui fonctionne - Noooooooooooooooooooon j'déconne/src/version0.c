#include "version0.h"

/**
 * Process n_iter iterations.
 */
void main_v0(int n_iter, Matrix * matrix_src, Matrix * matrix_dst)
{
    // Process iterations
    for (int k = 1; k <= n_iter; k++) {
        process_v0(matrix_src, matrix_dst);

        // Heat the center
        apply_heat_center(matrix_src, TEMP_HOT);
    }
}

/**
 * Apply one iteration process.
 */
void process_v0(Matrix* matrix_src, Matrix* matrix_dst)
{
    // Apply the process vertically
    directed_process_v0(matrix_src, matrix_dst, VERTICAL);

    // Apply the process horizontally
    directed_process_v0(matrix_dst, matrix_src, HORIZONTAL);
}

/**
 * Apply one iteration process on the destination matrix according to
 * the source matrix and the direction (horizontally or vertically).
 */
void directed_process_v0(Matrix* matrix_src, Matrix* matrix_dst, int direction)
{
    // Process each line OR column
    for(int i = 0; i < matrix_dst->size; i++)
        compute_line_or_column_at_index_v0(matrix_src, matrix_dst, direction, i);
}

/**
 *  Process the index-ieme line/column (direction).
 */
void compute_line_or_column_at_index_v0(Matrix* matrix_src, Matrix* matrix_dst, int direction, int index)
{
    // Cells required for Taylor formula
    float aim, adj1, adj2;

    // For each cell of the line/column
    for (int mutant = 0; mutant < matrix_dst->size; mutant++) {
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
