#include "matrix.h"

/**
 * Create a matrix.
 */
Matrix* create_matrix(int factor)
{

    // Size = 2^factor
    int size = my_pow(2, factor);

    // Alloc matrix memories
    Matrix* matrix = malloc(sizeof(Matrix));

    if (matrix == NULL)
        return NULL;

    //matrix->mtx = calloc(size * size, sizeof(float) * size * size);
    matrix->mtx = malloc(sizeof(float) * size * size);

    if (matrix->mtx == NULL)
        return NULL;

    // Init struct values
    matrix->size = size;
    matrix->factor = factor;

    return matrix;
}

void init_matrix(Matrix * m)
{
    for (int i = 0; i < m->size; i++)
        for (int j = 0; j < m->size; j++)
            MCELL(m, i, j) = (float) 0;
}

/**
 * Free the matrix.
 */
void free_matrix(Matrix* matrix)
{
    free(matrix->mtx);
    free(matrix);
}

/**
 * Print the matrix.
 */
void print_matrix(Matrix* matrix)
{
    printf("\n[");

    // Computing the number of digits to display
    // if
    char to_str[32];
    sprintf(to_str, "%d", TEMP_HOT);

    int len = strlen(to_str);

    // Displays len digits and 2 digits of the decimal part
    char format[] = "%%%d.2f ";
    sprintf(to_str, format, len+3);

    // Scale for the display
    int scale = (SHOW_ALL) ? 1 : my_pow(2, current_factor_size-4);

    // Show the entire matrix or not
    int limit = matrix->size;
    limit /= (SHOW_ALL) ? 1 : 2;

    // Display 1 cell on "scale"
    for(int i = 0; i < limit; i+=scale) {
        printf("\n");

        for(int j = 0; j < limit; j+=scale)
            printf(to_str, i, j, MCELL(matrix, i, j));
    }

    printf("\n]\n\n");
}

// =============

/**
 * Heat the center of the matrix.
 */
void apply_heat_center(Matrix* matrix, int value)
{
    // Compute center area
    int center_index = matrix->size/2;
    int range = matrix->size/16;

    int inf = center_index - range;
    int sup = center_index + range - 1;

    // Initialize center cells
    for(int i = inf; i <= sup; i++)
        for(int j = inf; j <= sup; j++)
            MCELL(matrix, i, j) = (float) value;
}

/**
  * Sum of all matrix values. (For debug)
  */
float matrix_sumvalue(Matrix* m)
{
    float res = 0;

    for(int i = 0; i < m->size; i++) {
        for(int j = 0; j < m->size; j++)
            res += MCELL(m, i, j);
    }

    return res;
}
