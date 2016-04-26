#include "condbarrier.h"

/**
 * Create a barrier initialized with the limit number of call (before unblocking threads)
 */
CBarrier * my_cbarr_init(int limit){
    CBarrier * b;
    b = malloc(2*sizeof(int) + sizeof(pthread_mutex_t) + sizeof(pthread_cond_t));

    if (b == NULL)
        return NULL;

    b->count = 0;
    b->limit = limit;

    if (pthread_mutex_init( &(b->mutex), NULL ) != 0) return NULL;
    if (pthread_cond_init( &(b->cond), NULL ) != 0) return NULL;

    return b;
}

/**
 * Waiting for the barrier to be raised or raising the barrier when limit is reached.
 */
void my_cbarr_wait(CBarrier * b){

    // Count increasement and broadcast/wait functions
    // can't be done simultaneously by several threads
    pthread_mutex_lock( &(b->mutex) );

    // Increasing count
    b->count++;

    // Raises the barrier when limit is reached (+ set count to 0)
    // else waiting for the barrier to be raised
    if (b->count == b->limit) {
            b->count = 0;
            pthread_cond_broadcast( &(b->cond) );
    } else {
            pthread_cond_wait( &(b->cond), &(b->mutex) );
    }

    // End of critical section
    pthread_mutex_unlock( &(b->mutex) );
}

/**
 * Free the barrier.
 */
void my_cbarr_destroy(CBarrier * b){
    free(b);
}

/**
 * Prints the barrier statement.
 */
void print_cbarrier(CBarrier * b, char * name) {
    printf("\n[Barrier %s] Count: %d - Limit: %d\n", name, b->count, b->limit);
}






