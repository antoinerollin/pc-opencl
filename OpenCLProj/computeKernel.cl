#pragma OPENCL EXTENSION cl_amd_printf : enable


__kernel void computeKernel(__global float* src, __global float* dst,__const int size, __const int iteration,
	__const int inf,__const int sup)
{

	int base = get_global_id(0);
	int line_num = get_local_id(0);
	int column_num = (base - line_num)/size;
	float before = 0;
	float after = 0;
	int mat_size = size*size;

	//	printf("inf:%d sup: %d line_num:%d column_num:%d base:%d\n",inf,sup,line_num,column_num,base );
	float tmp;
	for(int i = 0; i < iteration; i++){
		if(line_num == 0)
			before = 0;
		else
			before = src[base - 1];
		if(line_num == size-1)
			after = 0;
		else
			after = src[base + 1];
		dst[base] = (before + 4*src[base]+after)/6;



		barrier(CLK_GLOBAL_MEM_FENCE);
		if(base - size < 0)
			before = 0;
		else
			before = dst[base - size];
		if(base + size >= mat_size)
			after = 0;
		else
			after = dst[base + size];

		src[base] = (before+ 4*dst[base] + after)/6;
		if(line_num >= inf && line_num <= sup && column_num >= inf && column_num <= sup)
			src[base] = 128;
		barrier(CLK_GLOBAL_MEM_FENCE);
	}
	
}

