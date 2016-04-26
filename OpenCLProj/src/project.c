#include "project.h"

/**
 * Returns Taylor value of the aimed cell according to its neighbors.
 */
float apply_taylor(float aimed_cell, float adj_cell1, float adj_cell2)
{
    return (adj_cell1 + (H-2)*aimed_cell + adj_cell2)/H;
}
