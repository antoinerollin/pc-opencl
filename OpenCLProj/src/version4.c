#include "version4.h"

// POSIX Barriers
pthread_barrier_t barr_a, barr_b;

/**
 * Divides in regions and initializes barrier, then launch process.
 */
void main_v4(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads)
{

    // Compute regions for threads
    Region ** regions = generate_regions(n_threads, matrix_src->size);

    if (regions == NULL) {
        printf(">> [version1.c] main_v4: inefficient malloc causing abortion...\n");
        return;
    }

    // Init barrier : left when n_threads are waiting
    pthread_barrier_init(&barr_a, NULL, n_threads);
    pthread_barrier_init(&barr_b, NULL, n_threads);

    // Launch process
    process_v4(matrix_src, matrix_dst, regions, n_threads, n_iter);

    // Destroying barriers
    pthread_barrier_destroy(&barr_a);
    pthread_barrier_destroy(&barr_b);

    // Free regions
    free_regions_list(*regions);
}

/**
 * Launch threads and manage the matrix heat.
 */
void process_v4(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter)
{

    // Creating n_threads references
    pthread_t t[n_threads];

    Argument ** args = malloc(n_threads * sizeof(Argument *));

    if (args == NULL) {
        printf(">> [version1.c] process_v4: inefficient malloc causing abortion...\n");
        return;
    }

    // Launch n_threads threads
    // One threads per region
    for (int i = 0; i < n_threads; i++) {
        // Creating Argument_v4
        Argument * a = create_arg(matrix_src, matrix_dst, r_list[i], n_iter);

        if (a == NULL) {
            printf(">> [version1.c] process_v4: inefficient malloc causing abortion...\n");
            return;
        }

        // Saving Argument_v4
        // (else the next Argument_v4 will have the same address
        // and erase the previous Argument_v4 values)
        args[i] = a;

        // Launching thread
        pthread_create(&t[i], NULL, thread_func_v4, &args[i]);
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
void * thread_func_v4 (void * p)
{
    // Getting Argument_v4 structure
    Argument * a = *(Argument **) p;

    // Process iterations
    for (int k = 1; k <= a->n_iter; k++) {

        acquire_v4(VERTICAL);

        // Apply the process vertically
        directed_process(a->m1, a->m2, VERTICAL, a->reg);

        release_v4(VERTICAL);


        acquire_v4(HORIZONTAL);

        // Apply the process horizontally
        directed_process(a->m2, a->m1, HORIZONTAL, a->reg);

        // Heat center
        apply_heat_center_region(a->m1, a->reg, TEMP_HOT);

        release_v4(HORIZONTAL);
    }

    // End of the thread

    return NULL;
}

void acquire_v4(int direction)
{
    // Nothing
}

void release_v4(int direction)
{
    if (direction == VERTICAL)
        // Unlock others threads chen everyone has done the vertical process
        pthread_barrier_wait(&barr_a);
    else if (direction == HORIZONTAL)
        // Unlock others threads chen everyone has done the horizontal process
        pthread_barrier_wait(&barr_b);
}
