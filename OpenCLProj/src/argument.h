#ifndef ARG_H
#define ARG_H

#include "matrix.h"
#include "region.h"

#include <unistd.h>

#define MAIN    0
#define THREAD  1

/** Argument structure for thread function */
typedef struct Argument {
    Matrix* m1;
    Matrix* m2;
    Region* reg;
    int n_iter;
} Argument;


/** Allocate an Argument struct. */
Argument * create_arg(Matrix * m1, Matrix * m2, Region * r, int n_iter);

/** Free an Argument */
void free_arg(Argument * arg);

/** Free a list of Arguments */
void free_arg_list(Argument ** args);


#endif // ARG_H
