#ifndef REGION_H
#define REGION_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

/** Region struct. */
typedef struct Region {
    int x;
    int y;
    int width;
} Region;

/** Compute N coordinates (regions) according to the matrix size. */
Region ** generate_regions(int n_threads, int size);

/** Cut each region of the list in 4 regions and returns the new regions. */
Region ** cut_in_4(Region * regions[], int nb_regions);

/** Allocate a region in memory and itinializes it. */
Region * create_region(int x, int y, int w);

/** Prints a list of regions. */
void print_regions_list(Region ** list);

/** Prints the coordinates of a region. */
void print_region(Region * region);

/** Free a list of regions. */
void free_regions_list(Region ** r_list);

/** Heat the center of the matrix according to a region. */
void apply_heat_center_region(Matrix* matrix, Region* reg, int value);


#endif
