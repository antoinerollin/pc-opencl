#include "version2.h"

// POSIX Barriers
CBarrier * barr_a;
CBarrier * barr_b;

/**
 * Divides in regions and initializes barrier, then launch process.
 */
void main_v2(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads)
{
    // Compute regions for threads
    Region ** regions = generate_regions(n_threads, matrix_src->size);

    if (regions == NULL) {
        printf(">> [version2.c] main_v2: inefficient malloc causing abortion... (regions)\n");
        return;
    }

    // Init barrier : left when n_threads are waiting
    barr_a = my_cbarr_init(n_threads);
    barr_b = my_cbarr_init(n_threads);

    // Checking ineficient mallocs
    if (barr_a == NULL || barr_b == NULL){
        printf(">> [version2.c] main_v2: inefficient malloc causing abortion... (barriers)\n");
        return;
    }

    // Launch process
    process_v2(matrix_src, matrix_dst, regions, n_threads, n_iter);

    // Destroying barriers
    my_cbarr_destroy(barr_a);
    my_cbarr_destroy(barr_b);

    // Free regions
    free_regions_list(*regions);
}

/**
 * Launch threads and manage the matrix heat.
 */
void process_v2(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter)
{
    // Creating n_threads references
    pthread_t t[n_threads];

    Argument ** args = malloc(n_threads * sizeof(Argument *));

    if (args == NULL) {
        printf(">> [version2.c] process_v2: inefficient malloc causing abortion...\n");
        return;
    }

    // Launch n_threads threads
    // One threads per region
    for (int i = 0; i < n_threads; i++) {
        // Creating Argument_v2
        Argument * a = create_arg(matrix_src, matrix_dst, r_list[i], n_iter);

        if (a == NULL) {
            printf(">> [version2.c] process_v2: inefficient malloc causing abortion...\n");
            return;
        }

        // Saving Argument_v2
        // (else the next Argument will have the same address
        // and erase the previous Argument values)
        args[i] = a;

        // Launching thread
        pthread_create(&t[i], NULL, thread_func_v2, &args[i]);
    }

    // Ending threads
    for (int i = 0; i < n_threads; ++i)
        pthread_join(t[i], NULL);

    // Free Arguments
    free(*args);
}

/**
 * Thread function : process vertically then horizontally  in a region of the matrix
 */
void * thread_func_v2 (void * p)
{
    // Getting Argument_v2 structure
    Argument * a = *(Argument **) p;

    // Process iterations
    for (int k = 1; k <= a->n_iter; k++) {

        acquire_v2(VERTICAL);

        // Apply the process vertically
        directed_process(a->m1, a->m2, VERTICAL, a->reg);

        release_v2(VERTICAL);


        acquire_v2(HORIZONTAL);

        // Apply the process horizontally
        directed_process(a->m2, a->m1, HORIZONTAL, a->reg);

        // Heat matrix
        apply_heat_center_region(a->m1, a->reg, TEMP_HOT);

        release_v2(HORIZONTAL);
    }

    // End of the thread

    return NULL;
}

void acquire_v2(int direction)
{
    // Nothing
}
void release_v2(int direction)
{
    if (direction == VERTICAL)
        // Unlock others threads when everyone has done the vertical process
        my_cbarr_wait(barr_a);
    else if (direction == HORIZONTAL)
        // Unlock others threads when everyone has done the horizontal process
        my_cbarr_wait(barr_b);
}
