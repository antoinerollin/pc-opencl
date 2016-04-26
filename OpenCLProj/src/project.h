#ifndef PROJECT_H
#define PROJECT_H

#include <stdbool.h>

#define H 		        6
#define TEMP_HOT        128
#define TEMP_COLD       0
#define REPEAT_NUMBER   10

#define SHOW_ALL        0

#define VERSION_0       0
#define VERSION_1       1
#define VERSION_2       2
#define VERSION_3       3
#define VERSION_4       4
#define VERSION_5       5

/** Configuration */
char * cf_factors;       // -s
bool cf_time_cpu;        // -m
bool cf_time_user;       // -M
bool cf_disp;            // -a
int cf_iteration_number; // -i
char * cf_versions;      // -e
char * cf_thread_numbers;// -t

int current_factor_size;
int current_thread_number;
int current_version;

/** Returns Taylor value of the aimed cell according to its neighbors. */
float apply_taylor(float aimed_cell, float adj_cell1, float adj_cell2);

#endif // PROJECT_H
