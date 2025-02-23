#include<stdio.h>
#include<stdlib.h>
#define CL_TARGET_OPENCL_VERSION 220
#include<CL/cl.h>
const char *programS=
"__kernel\n"
"void add(__global int *a, __global int *b,__global int *c){\n"
"int idx=get_global_id(0);\n"
"c[idx]=a[idx]+b[idx];\n"
"}";
int main(){
    cl_int status;
    cl_uint num_platform,num_device;
    cl_platform_id *platform;
    cl_device_id *device;
    clGetPlatformIDs(0,NULL,&num_platform);
    platform=(cl_platform_id*)malloc(sizeof(cl_platform_id));
    clGetPlatformIDs(num_platform,platform,NULL);
    clGetDeviceIDs(platform[0],CL_DEVICE_TYPE_GPU,0,NULL,&num_device);
    device=(cl_device_id*)malloc(sizeof(cl_device_id));
    clGetDeviceIDs(platform[0],CL_DEVICE_TYPE_GPU,num_device,device,0);
    cl_context context=clCreateContext(NULL,num_device,device,NULL,NULL,&status);
    cl_command_queue command_queue=clCreateCommandQueue(context,device[0],0,&status);
    cl_mem bufferA,bufferB,bufferC;
    bufferA=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    bufferB=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    bufferC=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    int a[1],b[1],c[1];
    a[0]=9;
    b[0]=1;
    status=clEnqueueWriteBuffer(command_queue,bufferA,CL_FALSE,0,sizeof(int),a,0,NULL,NULL);
    status=clEnqueueWriteBuffer(command_queue,bufferB,CL_FALSE,0,sizeof(int),b,0,NULL,NULL);
    cl_program program=clCreateProgramWithSource(context,1,(const char**)&programS,NULL,&status);
    status=clBuildProgram(program,num_device,device,NULL,NULL,NULL);
    cl_kernel kernel=clCreateKernel(program,"add",&status);
    status=clSetKernelArg(kernel,0,sizeof(cl_mem),&bufferA);
    status|=clSetKernelArg(kernel,1,sizeof(cl_mem),&bufferB);
    status|=clSetKernelArg(kernel,2,sizeof(cl_mem),&bufferC);
    size_t globalGroupSize[1];
    globalGroupSize[0]=1;
    status=clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,globalGroupSize,NULL,0,NULL,NULL);
    clEnqueueReadBuffer(command_queue,bufferC,CL_TRUE,0,sizeof(int),c,0,NULL,NULL);
    printf("THe result is %d\n",c[0]);
}