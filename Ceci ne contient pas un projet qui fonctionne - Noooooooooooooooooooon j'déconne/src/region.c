#include "region.h"

/**
 * Returns a list of n_threads regions.
 */
Region ** generate_regions(int n_threads, int size)
{

    // Creating a list of region
    Region ** regions = malloc(sizeof(Region *));

    if (regions == NULL)
        return NULL;

    // The first region is the whole matrix
    regions[0] = create_region(0,0,size);
    regions[1] = '\0';

    int nb_regions = 1;

    if (regions[0] == NULL) {
        printf(">> [region.c] generate_regions: inefficient malloc causing abortion...\n");
        return NULL;
    }

    if (n_threads <= 1)
        return regions;

    // Final list of regions
    Region ** res;

    // Aim : get n_threads regions
    while(nb_regions < n_threads) {
        // Cut each region of the list in 4 regions
        res = cut_in_4(regions, nb_regions);
        regions = res;

        // The number of regions is multiplied by 4
        nb_regions *= 4;
    }

    return res;
}

/**
 * Cut each region of the list in 4 regions and returns the new regions.
 */
Region ** cut_in_4(Region * regions[], int nb_regions)
{

    // The size of the new regions is the previous size divided by 2
    int new_width = regions[0]->width/2;

    // The number of regions will be multiplied by 4
    int new_nb_regions = nb_regions*4;

    // Final regions list
    Region ** res = malloc(new_nb_regions * sizeof(Region *));

    //int i = 0;
    int k = 0;

    // For each region
    for (int i = 0; i < nb_regions; i++) {
        // Creates the 4 new regions from the previous one
        Region * r1 = create_region(regions[i]->x, regions[i]->y, new_width);
        Region * r2 = create_region(regions[i]->x, regions[i]->y+new_width, new_width);
        Region * r3 = create_region(regions[i]->x+new_width, regions[i]->y, new_width);
        Region * r4 = create_region(regions[i]->x+new_width, regions[i]->y+new_width, new_width);

        // Saving regions
        res[k] = r1;
        res[k+1] = r2;
        res[k+2] = r3;
        res[k+3] = r4;

        k+=4;
    }

    free(*regions);

    return res;
}
/**
 * Allocate a region in memory and itinializes it.
 */
Region * create_region(int x, int y, int w)
{
    Region * r = malloc(sizeof(Region));

    if (r == NULL)
        return NULL;

    r->x = x;
    r->y = y;
    r->width = w;

    return r;
}

/**
 * Prints a list of regions.
 */
void print_regions_list(Region ** list)
{
    int i = 0;

    // For each region
    while (list[i] != '\0') { // So ugly and dangerous
        printf("i:%d => x:%d - y:%d - w:%d\n", i, list[i]->x, list[i]->y, list[i]->width);
        i++;
    }
}

/**
 * Prints a region.
 */
void print_region(Region * region)
{
    printf("x:%d - y:%d - w:%d\n", region->x, region->y, region->width);
}

/**
 * Free a regions list.
 */
void free_regions_list(Region ** r_list)
{
    int i = 0;

    while (r_list[i] != '\0') {
        free(r_list[i]);
        i++;
    }

    free(r_list);
}

/**
 * Prints the region of a matrix.
 */
/*void print_matrix_region(Matrix * m, Region * r)
{
    printf("\n[\n");

    for (int i = r->x; i < (r->x+r->width); i++) {
        for (int j = r->y; j < (r->y+r->width); j++)
            printf("%3d ", (int) MCELL(m, i, j));
        printf("\n");
    }

    printf("]\n");
}*/

/**
 * Heat the center of the matrix according to a region.
 */
void apply_heat_center_region(Matrix* matrix, Region * reg, int value)
{
    // Compute center area
    int center_index = matrix->size/2;
    int range = matrix->size/16;

    int inf = center_index - range;
    int sup = center_index + range - 1;

    // Initialize center cells
    for(int i = reg->x; i < (reg->x + reg->width); i++) {
        for(int j = reg->y; j < (reg->y + reg->width); j++) {
            if (i >= inf && i <= sup && j >= inf && j <= sup)
                MCELL(matrix, i, j) = (float) value;
        }
    }
}

