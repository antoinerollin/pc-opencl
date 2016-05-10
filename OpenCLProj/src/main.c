/**
 * Concurrent Systems - STEP 3 (BARRIER WITH SEMAPHORE)
 * ROLLIN Antoine
 */

#include "main.h"

/**
 * MAIN
 */
int main (int argc, char * argv[])
{
    // Parse command
    parse_command(argc, argv);

    // Prints and checks the configuration
    print_configuration();
    check_configuration();

    // Pause
    press_enter();

    // Launch each selected step
    launch_versions();

    return EXIT_SUCCESS;
}

/**
 * Launch the process for each version
 */
void launch_versions()
{
    // For each version
    for (int i = 0; i < strlen(cf_versions); i++) {
        // Getting version number
        current_version = (int) cf_versions[i] - '0';

        // For each size factor
        for (int s = 0; s < strlen(cf_factors); s++) {
            current_factor_size = (int) cf_factors[s] - '0';

            if (current_factor_size < 0 || current_factor_size > 9) {
                printf("Size factor must be in [0..9]\n");
                break;
            }

            current_factor_size += 4;


            // For each thread factor
            for (int t = 0; t < strlen(cf_thread_numbers); t++) {

                // Useless to process version 0 for each thread factor
                if ((current_version == VERSION_0) && (t != 0))
                    break;

                int factor = (int) cf_thread_numbers[t] - '0';

                if (factor < 0 || factor > 5) {
                    printf("Thread factor must be in [0..5]\n");
                    break;
                }

                // Computes the number of threads unless for version 0
                if ((current_version == VERSION_0) && (t == 0))
                    current_thread_number = 0;
                else
                    current_thread_number = my_pow(4,factor);

                // Checks the current configuration
                check_configuration();

                // Print version name
                print_version_name();

                // Launch the version N times
                repeat_process();

                // Pause (except last loop)
                if (!(i == strlen(cf_versions)-1 && s == strlen(cf_factors)-1 && t == strlen(cf_thread_numbers)-1))
                    press_enter();

                printf("-----------------------------\n");
            }
        }
    }

    printf("END OF PROGRAM\n");
}

/**
 * Repeat N times each process and computes the average process time
 */
void repeat_process()
{

    // Times records
    double times_cpu[REPEAT_NUMBER];
    double times_user[REPEAT_NUMBER];
    long memory_usage[REPEAT_NUMBER];

    // Time variables
    double time_cpu_init;
    time_t time_user_init;

    // Memory variable
    struct rusage usage;

    // Repeat the process N times
    for (int r = 0; r < REPEAT_NUMBER; r++) {

        printf("\nExecution n°%d... ", r+1);
        fflush(stdout);

        // Init times
        time_cpu_init = clock();
        time_user_init = time(NULL);

        // Create matrices
        Matrix* matrix_one = create_matrix(current_factor_size);
        Matrix* matrix_two = create_matrix(current_factor_size);

        // Init memory usage
        getrusage(RUSAGE_SELF, &usage);

        if (matrix_one == NULL || matrix_two == NULL) {
            printf(">> [main.c] inefficient malloc causing abortion...\n");
            return;
        }

        // Init the matrix
        init_matrix(matrix_one);
        apply_heat_center(matrix_one, TEMP_HOT);

        // Print the initial matrix once
        if (cf_disp && r == 0) {
            print_iteration(PRINT_INIT);
            print_matrix(matrix_one);
        }

        // Process according to the version number
        if (process_version(matrix_one, matrix_two) == ERROR)
            return;

        // Manage time
        if (cf_time_cpu)
            times_cpu[r] = (clock() - time_cpu_init)/CLOCKS_PER_SEC;
        if (cf_time_user)
            times_user[r] = (time(NULL) - time_user_init);

        // Manage memory
        getrusage(RUSAGE_SELF, &usage);
        memory_usage[r] = usage.ru_maxrss;

        // Prints the final matrix once
        if (cf_disp && r == 0) {
            print_iteration(PRINT_RESULT);
            print_matrix(matrix_one);
        }

        printf("(Memory: %ld Ko)\n", memory_usage[r]);

        // Display times
        if (cf_time_cpu)
            printf("- CPU time = %f s\n", times_cpu[r]);
        if (cf_time_user)
            printf("- User time = %f s\n", times_user[r]);

        // Free matrice
        free_matrix(matrix_one);
        free_matrix(matrix_two);
    }

    // Prints total time
    if (cf_time_cpu)
        printf("\nAverage CPU time = %f s\n", get_average_double(times_cpu));
    if (cf_time_user)
        printf("\nAverage User time = %f s\n", get_average_double(times_user));

    printf("\nAverage memory used = %ld Ko\n", get_average_long(memory_usage));

}
/**
 * Process one version
 */
int process_version(Matrix * m1, Matrix * m2)
{
    int statement = 0;

    // Selecting the version to launch
    switch (current_version) {

    case VERSION_0:
        main_v0(cf_iteration_number,m1,m2);
        break;

    case VERSION_1:
        main_v1(cf_iteration_number,m1,m2,current_thread_number);
        break;

    case VERSION_2:
        main_v2(cf_iteration_number,m1,m2,current_thread_number);
        break;

    case VERSION_3:
        main_v3(cf_iteration_number,m1,m2,current_thread_number);
        break;

    case VERSION_4:
        main_v4(cf_iteration_number,m1,m2,current_thread_number);
        break;

    case VERSION_5:
        printf("Not supported yet.\n");
        statement = ERROR;
        break;

    default:
        printf("Invalid number of version\n");
        statement = ERROR;
        break;
    }

    return statement;
}

