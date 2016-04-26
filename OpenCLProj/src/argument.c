#include "argument.h"

/**
 * Allocates and creates a thread Argument.
 */
Argument * create_arg(Matrix * m1, Matrix * m2, Region * r, int n_iter)
{
    Argument * a = malloc(sizeof(Argument));

    if (a == NULL)
        return NULL;

    a->m1 = m1;
    a->m2 = m2;
    a->reg = r;
    a->n_iter = n_iter;

    return a;
}

/**
 * Free an Argument.
 */
void free_arg(Argument * arg)
{
    free(arg->reg);
    free(arg);
}

/**
 * Free a list of Arguments
 */
void free_arg_list(Argument ** args)
{
    int i = 0;
    while (args[i] != '\0') {
        free_arg(args[i]);
        i++;
    }

    free(args);
}




