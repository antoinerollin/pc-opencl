#include "version4.h"


// POSIX Barriers
pthread_barrier_t barr_a, barr_b;

#define MAX_SOURCE_SIZE (0x100000)  

void perrorOpenCL(cl_int err, const char *str) {
    switch (err) {
        case CL_SUCCESS:                            printf("%s: Success!\n", str); break;
        case CL_DEVICE_NOT_FOUND:                   printf("%s: Device not found.\n", str); break;
        case CL_DEVICE_NOT_AVAILABLE:               printf("%s: Device not available\n", str); break;
        case CL_COMPILER_NOT_AVAILABLE:             printf("%s: Compiler not available\n", str); break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:      printf("%s: Memory object allocation failure\n", str); break;
        case CL_OUT_OF_RESOURCES:                   printf("%s: Out of resources\n", str); break;
        case CL_OUT_OF_HOST_MEMORY:                 printf("%s: Out of host memory\n", str); break;
        case CL_PROFILING_INFO_NOT_AVAILABLE:       printf("%s: Profiling information not available\n", str); break;
        case CL_MEM_COPY_OVERLAP:                   printf("%s: Memory copy overlap\n", str); break;
        case CL_IMAGE_FORMAT_MISMATCH:              printf("%s: Image format mismatch\n", str); break;
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:         printf("%s: Image format not supported\n", str); break;
        case CL_BUILD_PROGRAM_FAILURE:              printf("%s: Program build failure\n", str); break;
        case CL_MAP_FAILURE:                        printf("%s: Map failure\n", str); break;
        case CL_INVALID_VALUE:                      printf("%s: Invalid value\n", str); break;
        case CL_INVALID_DEVICE_TYPE:                printf("%s: Invalid device type\n", str); break;
        case CL_INVALID_PLATFORM:                   printf("%s: Invalid platform\n", str); break;
        case CL_INVALID_DEVICE:                     printf("%s: Invalid device\n", str); break;
        case CL_INVALID_CONTEXT:                    printf("%s: Invalid context\n", str); break;
        case CL_INVALID_QUEUE_PROPERTIES:           printf("%s: Invalid queue properties\n", str); break;
        case CL_INVALID_COMMAND_QUEUE:              printf("%s: Invalid command queue\n", str); break;
        case CL_INVALID_HOST_PTR:                   printf("%s: Invalid host pointer\n", str); break;
        case CL_INVALID_MEM_OBJECT:                 printf("%s: Invalid memory object\n", str); break;
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    printf("%s: Invalid image format descriptor\n", str); break;
        case CL_INVALID_IMAGE_SIZE:                 printf("%s: Invalid image size\n", str); break;
        case CL_INVALID_SAMPLER:                    printf("%s: Invalid sampler\n", str); break;
        case CL_INVALID_BINARY:                     printf("%s: Invalid binary\n", str); break;
        case CL_INVALID_BUILD_OPTIONS:              printf("%s: Invalid build options\n", str); break;
        case CL_INVALID_PROGRAM:                    printf("%s: Invalid program\n", str); break;
        case CL_INVALID_PROGRAM_EXECUTABLE:         printf("%s: Invalid program executable\n", str); break;
        case CL_INVALID_KERNEL_NAME:                printf("%s: Invalid kernel name\n", str); break;
        case CL_INVALID_KERNEL_DEFINITION:          printf("%s: Invalid kernel definition\n", str); break;
        case CL_INVALID_KERNEL:                     printf("%s: Invalid kernel\n", str); break;
        case CL_INVALID_ARG_INDEX:                  printf("%s: Invalid argument index\n", str); break;
        case CL_INVALID_ARG_VALUE:                  printf("%s: Invalid argument value\n", str); break;
        case CL_INVALID_ARG_SIZE:                   printf("%s: Invalid argument size\n", str); break;
        case CL_INVALID_KERNEL_ARGS:                printf("%s: Invalid kernel arguments\n", str); break;
        case CL_INVALID_WORK_DIMENSION:             printf("%s: Invalid work dimension\n", str); break;
        case CL_INVALID_WORK_GROUP_SIZE:            printf("%s: Invalid work group size\n", str); break;
        case CL_INVALID_WORK_ITEM_SIZE:             printf("%s: Invalid work item size\n", str); break;
        case CL_INVALID_GLOBAL_OFFSET:              printf("%s: Invalid global offset\n", str); break;
        case CL_INVALID_EVENT_WAIT_LIST:            printf("%s: Invalid event wait list\n", str); break;
        case CL_INVALID_EVENT:                      printf("%s: Invalid event\n", str); break;
        case CL_INVALID_OPERATION:                  printf("%s: Invalid operation\n", str); break;
        case CL_INVALID_GL_OBJECT:                  printf("%s: Invalid OpenGL object\n", str); break;
        case CL_INVALID_BUFFER_SIZE:                printf("%s: Invalid buffer size\n", str); break;
        case CL_INVALID_MIP_LEVEL:                  printf("%s: Invalid mip-map level\n", str); break;
        default: printf("%s: Unknown\n", str); break;
    }
}


/**
 * Divides in regions and initializes barrier, then launch process.
 */
void main_v4(int n_iter, Matrix * matrix_src, Matrix * matrix_dst, int n_threads)
{
    printf("essai de lancement en opencl !!\n");
    //variables needed for opencl
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem srcmobj = NULL;    
    cl_mem dstmobj = NULL;    
    cl_program program = NULL;
    cl_kernel kernel = NULL;    
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
    
    int size = matrix_src->size;

    FILE *fp;
    const char fileName[] = "./computeKernel.cl";
    size_t source_size;
    char *source_str;

    /* Load kernel source file */
    fp = fopen(fileName, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");    
        exit(1);
    }   
    source_str = (char *)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    //we need to create matrix here and initialize it


    //initializing and configuring opencl
        /* Get Platform/Device Information */
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);    
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clGetPlatformIDs:"); exit(-1);}
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clGetPlatformIDs:"); exit(-1);}
 
    /* Create OpenCL Context */
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    if (context == NULL) {perrorOpenCL(ret, "clCreateContext:"); exit(-1);}
 
    /* Create command queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    if (command_queue == NULL) {perrorOpenCL(ret, "clCreateCommandQueue:"); exit(-1);}
 
    /* Create Buffer Object */
    /* theses are the buffer read from and written to by openCL
     *  where we store all our data */
    srcmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, size*size*sizeof(float), NULL, &ret);
    if (srcmobj == NULL) {perrorOpenCL(ret, "Amobj clCreateBuffer:"); exit(-1);}
    dstmobj = clCreateBuffer(context, CL_MEM_READ_WRITE, size*size*sizeof(float), NULL, &ret);
    if (dstmobj == NULL) {perrorOpenCL(ret, "Bmobj clCreateBuffer:"); exit(-1);}

    /* Copy input data to the memory buffer */
    ret = clEnqueueWriteBuffer(command_queue, srcmobj, CL_TRUE, 0, size*size*sizeof(float), matrix_src->mtx, 0, NULL, NULL);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clEnqueueWriteBuffer:"); exit(-1);}
    ret = clEnqueueWriteBuffer(command_queue, dstmobj, CL_TRUE, 0, size*size*sizeof(float), matrix_dst->mtx, 0, NULL, NULL);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clEnqueueWriteBuffer:"); exit(-1);}



    /* Create kernel program from source file */
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);    
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clCreateProgramWithSource:"); exit(-1);}
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (ret == CL_BUILD_PROGRAM_FAILURE) {
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char *log = (char *) malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
        exit(-1);
    }
    //if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clBuildProgram:"); exit(-1);}
 
    /* Create data parallel OpenCL kernel */    
    kernel = clCreateKernel(program, "computeKernel", &ret);
    if (kernel == NULL) {perrorOpenCL(ret, "clCreateKernel:"); exit(-1);}
    /*compute center region for the kernel*/
    int center_index = size/2;
    int range = size/16;

    int inf = center_index - range;
    int sup = center_index + range - 1;
    /* Set OpenCL kernel arguments */
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&srcmobj);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}

    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&dstmobj);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}

    ret = clSetKernelArg(kernel, 2, sizeof(size), (void *)&size);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}

    ret = clSetKernelArg(kernel, 3, sizeof(n_iter), (void *)&n_iter);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}

    ret = clSetKernelArg(kernel, 4, sizeof(inf), (void *)&inf);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}
    ret = clSetKernelArg(kernel, 5, sizeof(sup), (void *)&sup);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "Amobj clSetKernelArg:"); exit(-1);}
     size_t global_item_size = size*size;
    size_t local_item_size = size;

    /* Execute OpenCL kernel as data parallel */
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clEnqueueNDRangeKernel:"); exit(-1);}
 
    /* Transfer result to host */
    ret = clEnqueueReadBuffer(command_queue, srcmobj, CL_TRUE, 0, size*size*sizeof(float), matrix_src->mtx, 0, NULL, NULL);
    if (ret != CL_SUCCESS) {perrorOpenCL(ret, "clEnqueueReadBuffer:"); exit(-1);}
    //print_matrix(matrix_src);
   /* float * tmp = matrix_src->mtx;
    matrix_src->mtx = matrix_dst->mtx;
    matrix_dst->mtx = tmp;*/

}

/**
 * Launch threads and manage the matrix heat.
 */
void process_v4(Matrix* matrix_src, Matrix* matrix_dst, Region ** r_list, int n_threads, int n_iter)
{

    // Creating n_threads references
    pthread_t t[n_threads];

    Argument ** args = malloc(n_threads * sizeof(Argument *));

    if (args == NULL) {
        printf(">> [version1.c] process_v4: inefficient malloc causing abortion...\n");
        return;
    }

    // Launch n_threads threads
    // One threads per region
    for (int i = 0; i < n_threads; i++) {
        // Creating Argument_v4
        Argument * a = create_arg(matrix_src, matrix_dst, r_list[i], n_iter);

        if (a == NULL) {
            printf(">> [version1.c] process_v4: inefficient malloc causing abortion...\n");
            return;
        }

        // Saving Argument_v4
        // (else the next Argument_v4 will have the same address
        // and erase the previous Argument_v4 values)
        args[i] = a;

        // Launching thread
        pthread_create(&t[i], NULL, thread_func_v4, &args[i]);
    }

    // Ending threads
    for (int i = 0; i < n_threads; ++i)
        pthread_join(t[i], NULL);

    // Free Arguments
    free(*args);
}

/**
 * Thread function : process vertically then horizontally  in a region of the matrix
 */
void * thread_func_v4 (void * p)
{
    // Getting Argument_v4 structure
    Argument * a = *(Argument **) p;

    // Process iterations
    for (int k = 1; k <= a->n_iter; k++) {

        acquire_v4(VERTICAL);

        // Apply the process vertically
        directed_process(a->m1, a->m2, VERTICAL, a->reg);

        release_v4(VERTICAL);


        acquire_v4(HORIZONTAL);

        // Apply the process horizontally
        directed_process(a->m2, a->m1, HORIZONTAL, a->reg);

        // Heat center
        apply_heat_center_region(a->m1, a->reg, TEMP_HOT);

        release_v4(HORIZONTAL);
    }

    // End of the thread

    return NULL;
}

void acquire_v4(int direction)
{
    // Nothing
}

void release_v4(int direction)
{
    if (direction == VERTICAL)
        // Unlock others threads chen everyone has done the vertical process
        pthread_barrier_wait(&barr_a);
    else if (direction == HORIZONTAL)
        // Unlock others threads chen everyone has done the horizontal process
        pthread_barrier_wait(&barr_b);
}
