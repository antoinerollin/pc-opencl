#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "matrix.h"
#include "utils.h"
#include "version0.h"
#include "version1.h"
#include "version2.h"
#include "version3.h"

/** Launch the process for each version */
void launch_versions();

/** Repeat N times each process and computes the average process time */
void repeat_process();

/** Process one version */
int process_version(Matrix * m1, Matrix * m2);
