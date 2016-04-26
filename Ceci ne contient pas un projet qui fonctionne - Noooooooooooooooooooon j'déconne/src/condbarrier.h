#ifndef BARC_H
#define BARC_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct CBarrier {
  	int count;
	int limit;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
} CBarrier;

/** Barrier actions */
CBarrier * my_cbarr_init(int limit);
void my_cbarr_wait(CBarrier * b);
void my_cbarr_destroy(CBarrier * b);
void print_cbarrier(CBarrier * b, char * name);

#endif // BARC_H
