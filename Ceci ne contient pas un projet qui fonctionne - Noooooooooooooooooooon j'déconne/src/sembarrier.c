#include "sembarrier.h"

/**
 * Create a barrier initialized with the limit number of call (before unblocking threads)
 */
SBarrier * my_sbarr_init(int limit){
    SBarrier * b;
    b = malloc(2*sizeof(int) + sizeof(pthread_mutex_t) + sizeof(pthread_cond_t));

    if (b == NULL)
        return NULL;

    b->count = 0;
    b->limit = limit;

    if (sem_init( &(b->lock), 0, 1 ) < 0) return NULL;
    if (sem_init( &(b->sem ), 0, 0 ) < 0) return NULL;

    return b;
}

/**
 * Waiting for the barrier to be raised or raising the barrier when limit is reached.
 */
void my_sbarr_wait(SBarrier * b){

    // Entering in critical section
    sem_wait( &(b->lock) );
    b->count++;

    // Free all threads if limit reached
    if (b->count == b->limit)
    {
        // Unblocking threads
        for (int i = 0; i < b->limit-1; i++)
            sem_post( &(b->sem) );

        // Reset counter
        b->count = 0;

        // Exiting critical section
        sem_post( &(b->lock) );
    }
    else
    {
        // Exiting critical section
        sem_post( &(b->lock) );

        // Waiting
        sem_wait( &(b->sem) );
    }
}

/**
 * Free the barrier.
 */
void my_sbarr_destroy(SBarrier * b){
    sem_destroy( &(b->lock) );
    sem_destroy( &(b->sem) );
    free(b);
}

/**
 * Prints the barrier statement.
 */
void print_sbarrier(SBarrier * b, char * name) {
    printf("\n[Barrier %s] Count: %d - Limit: %d\n", name, b->count, b->limit);
}






