#ifndef BARS_H
#define BARS_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct SBarrier {
  	int count;
	int limit;
	sem_t sem;
	sem_t lock;
} SBarrier;

/** Barrier actions */
SBarrier * my_sbarr_init(int limit);
void my_sbarr_wait(SBarrier * b);
void my_sbarr_destroy(SBarrier * b);
void print_sbarrier(SBarrier * b, char * name);

#endif // BARS_H
