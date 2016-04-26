#ifndef DEBUGS_H
#define DEBUGS_H

#define PRINT_INIT      -1
#define PRINT_RESULT    -2

#define ERROR           -1
#define VALID           0

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "project.h"

/** Prints iteration number. */
void print_iteration(int k);

/** Computes the average double value without extremities */
double get_average_double(double table[]);

/** Computes the average long value without extremities */
long get_average_long(long table[]);

/** Prints the version name */
void print_version_name();

/** Command line parser */
void parse_command(int argc, char * argv[]);

/** Prints configurations */
void print_configuration();

/** Waits for ENTER */
void press_enter();

/** Check the consistency between the number of threads and the matrix size. */
void check_configuration();

/** My pow function. */
int my_pow(int n, int exp);



#endif // DEBUGS_H
