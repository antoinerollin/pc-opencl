#include "utils.h"

/**
 *  Swap pointers.
 */
void swap(void** value1, void** value2)
{
    void* value3 = *value1;
    *value1 = *value2;
    *value2 = value3;
}

/**
 * Prints iteration number.
 */
void print_iteration(int k)
{
    printf("\n----------------------------\n");

    switch(k) {
    case PRINT_INIT:
        printf("\tINITIAL");
        break;

    case PRINT_RESULT:
        printf("\tFINAL");
        break;

    default:
        printf("\tITERATION %d", k);
        break;
    }

    printf("\n----------------------------\n");
}

/**
 * Returns the average double value from a table
 */
double get_average_double(double table[])
{

    if (REPEAT_NUMBER < 1)
        return 0;

    // Init extremities & sum
    double min = table[0];
    double max = table[0];
    double sum = 0;

    // For each value
    for (int i = 0; i < REPEAT_NUMBER; i++) {
        // Updating extremities
        if (table[i] < min)
            min = table[i];
        else if (table[i] > max)
            max = table[i];

        // Computing sum
        sum += table[i];
    }

    double res = sum;

    // Removing extrimities if there are enough values
    if (REPEAT_NUMBER > 2) {
        res -= (min + max);
        res /= (REPEAT_NUMBER - 2);
    } else
        res /= REPEAT_NUMBER;

    return res;
}

/**
 * Returns the average long value from a table
 */
long get_average_long(long table[])
{

    if (REPEAT_NUMBER < 1)
        return 0;

    // Init extremities & sum
    long min = table[0];
    long max = table[0];

    long sum = 0;

    // For each value
    for (int i = 0; i < REPEAT_NUMBER; i++) {
        // Updating extremities
        if (table[i] < min)
            min = table[i];
        else if (table[i] > max)
            max = table[i];

        // Computing sum
        sum += table[i];
    }

    long res = sum;

    // Removing extrimities if there are enough values
    if (REPEAT_NUMBER > 2) {
        res -= (min + max);
        res /= (REPEAT_NUMBER - 2);
    } else
        res /= REPEAT_NUMBER;

    return res;
}

/**
 * Prints the version name
 */
void print_version_name()
{

    switch (current_version) {
    case VERSION_0:
        printf("\n|| ITERATIVE VERSION [0]");
        break;

    case VERSION_1:
        printf("\n|| POSIX BARRIER VERSION [1]");
        break;

    case VERSION_2:
        printf("\n|| CONDITION VARIABLE BARRIER VERSION [2]");
        break;

    case VERSION_3:
        printf("\n|| SEMAPHORE BARRIER VERSION [3]");
        break;

    case VERSION_4:
        printf("\n|| OPEN-CL CPU [4]");
        break;

    case VERSION_5:
        printf("\n|| OPEN-CL GPU [5]");
        break;

    default:
        printf("|| Invalid number of version\n");
        break;
    }

    int size = my_pow(2, current_factor_size);
    printf("\n|| Matrix Size: [%dx%d] - Thread Number: %d\n\n", size, size, current_thread_number);


}

/**
 * Get configuration from command
 */
void parse_command(int argc, char * argv[])
{

    // Default configuration
    cf_factors = "0";
    cf_time_cpu = false;
    cf_time_user = false;
    cf_disp = false;
    cf_iteration_number = 10000;
    cf_versions = "012345";
    cf_thread_numbers = "1";

    // No argument
    if (argc <= 1)
        return;

    int statement;      // Statement defining the validity of the argument
    char * err_mess;    // Buffer for the error message

    // For each argument
    for (int i = 1; i < argc; i++) {

        statement = VALID;
        printf("Checking %s... ", argv[i]);

        // Matrix size
        if (strcmp(argv[i], "-s") == 0) {

            if (strstr(argv[i+1], "-") != NULL) {
                statement = ERROR;
                err_mess = "invalid value";
            } else {
                int len = strlen(argv[++i]);
                cf_factors = malloc(sizeof(char)*len);
                cf_factors = argv[i];
            }
        }

        // CPU time display
        else if (strcmp(argv[i], "-m") == 0) {
            cf_time_cpu = true;
        }

        // User time display
        else if (strcmp(argv[i], "-M") == 0) {
            cf_time_user = true;
        }

        // Matrix diplay
        else if (strcmp(argv[i], "-a") == 0) {
            cf_disp = true;
        }

        // Iteration number
        else if (strcmp(argv[i], "-i") == 0) {

            int it = atoi(argv[++i]);

            // Validity checking
            if (it < 0) {
                statement = ERROR;
                err_mess = "i must be in positive";
            } else
                cf_iteration_number = it;
        }

        // Versions to launch
        else if (strcmp(argv[i], "-e") == 0) {

            if (strstr(argv[i+1], "-") != NULL) {
                statement = ERROR;
                err_mess = "invalid value";
            } else {
                int len = strlen(argv[++i]);
                cf_versions = malloc(sizeof(char)*len);
                cf_versions = argv[i];
            }
        }

        // Thread number
        else if (strcmp(argv[i], "-t") == 0) {
            if (strstr(argv[i+1], "-") != NULL) {
                statement = ERROR;
                err_mess = "invalid value";
            } else {
                int len = strlen(argv[++i]);
                cf_thread_numbers = malloc(sizeof(char)*len);
                cf_thread_numbers = argv[i];
            }
            // Unknown parameter
        } else {
            statement = ERROR;
            err_mess = "unknown parameter";
        }

        // Statement
        if (statement == VALID)
            printf("OK");
        else
            printf("KO (%s)", err_mess);
        printf("\n");
    }
}

/**
 * Check the consistency between the number of threads and the matrix size.
 */
void check_configuration()
{
    int m_size = my_pow(2, current_factor_size);
    int area = m_size * m_size;

    if (current_thread_number > area) {
        printf("\n/!\\ The input thread number is too high (%d). \nIts value is now %d.\n\n", current_thread_number, area);
        current_thread_number = area;
    }
}

/**
 * Prints the configuration.
 */
void print_configuration()
{
    printf("\n----------------------------\n");
    printf("\t INFOS");
    printf("\n----------------------------\n");

    printf("Arguments\n");

    printf("\tsize factors: %s\n", cf_factors);
    printf("\tthread factors: %s\n", cf_thread_numbers);
    printf("\tversions to launch: %s\n", cf_versions);
    printf("\tdisplay CPU time: %d\n", (int) cf_time_cpu);
    printf("\titeration number: %d\n", cf_iteration_number);
    printf("\tdisplay user time: %d\n", (int) cf_time_user);
    printf("\tdisplay matrix (1/4): %d\n", (int) cf_disp);
    printf("\n");

    printf("Other infos\n");

    printf("\tmatrix center heat: %d\n", TEMP_HOT);
    printf("\tspread factor (H):  %d\n", H);
    printf("\tloop number:  %d\n", REPEAT_NUMBER);

    printf("\n----------------------------\n");
}

/**
 * Waiting the user to press ENTER.
 */
void press_enter()
{
    printf("\n");
    printf("[PRESS ENTER TO CONTINUE]");
    printf("\n\n");
    getchar();
}

/**
 * Returns n^exp.
 */
int my_pow(int n, int exp){

    int coef = n/2;
    int res;

    if (exp == 0)
        res = 1;
    else if (exp > 0)
        res = n << (coef*(exp - 1));
    else
        res = 0;

    return res;
}
