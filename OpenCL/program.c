//gcc program.c -o program -I/opt/homebrew/Cellar/opencl-headers/2024.10.24/include -L/opt/homebrew/lib -framework OpenCL
#include<stdio.h>
#include<stdlib.h>
#define CL_TARGET_OPENCL_VERSION 220
#include<CL/cl.h>
const char* programSource =
 "__kernel                                   		\n"
"void sajan(__global int *A,     		\n"
"                    __global int *B,      		\n" 
"                    __global int *C)     		\n"
"{                                                		\n"
"                                                 		\n"
"int idx = get_global_id(0);                      	\n"
"C[idx] = A[idx] + B[idx];                         	\n"
"}                                                              	\n"
;

int main(){
    cl_uint num_platform=0;
    cl_int status;
    cl_platform_id *platform=NULL;
    status=clGetPlatformIDs(0,NULL,&num_platform);
    platform=(cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platform);
    status=clGetPlatformIDs(num_platform,platform,NULL);
    for(int i=0;i<num_platform;i++){
        char name[256];
        clGetPlatformInfo(platform[i],CL_PLATFORM_NAME,sizeof(name),name,NULL);
        printf("Name of Platform: %s\n",name);
    }
    cl_uint num_device;
    cl_device_id *device=NULL;
    status=clGetDeviceIDs(platform[0],CL_DEVICE_TYPE_GPU,0,NULL,&num_device);
    device=(cl_device_id*)malloc(sizeof(cl_device_id)*num_device);
    status=clGetDeviceIDs(platform[0],CL_DEVICE_TYPE_GPU,num_device,device,NULL);
    for(int i=0;i<num_device;i++){
        char dname[256];
        clGetDeviceInfo(device[i],CL_DEVICE_NAME,sizeof(dname),dname,NULL);
        printf("Name of device: %s\n",dname);
    }
    cl_context context=NULL;
    context=clCreateContext(NULL,num_device,device,NULL,NULL,&status);
    cl_device_id context_device[1];
    clGetContextInfo(context,CL_CONTEXT_DEVICES,sizeof(context_device),context_device,NULL);
    char cname[256];
    clGetDeviceInfo(context_device[0],CL_DEVICE_NAME,sizeof(cname),cname,NULL);
    printf("Name of Device in Context: %s\n",cname);

    cl_command_queue command_queue;
    command_queue=clCreateCommandQueue(context,device[0],0,&status);
    cl_mem bufferA,bufferB,bufferC;
    bufferA=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    bufferB=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    bufferC=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&status);
    int *A,*B,*C;
    A=(int*)malloc(sizeof(int));
    B=(int*)malloc(sizeof(int));
    C=(int*)malloc(sizeof(int));
    A[0]=5;
    B[0]=6;
    status=clEnqueueWriteBuffer(command_queue,bufferA,CL_FALSE,0,sizeof(int),A,0,NULL,NULL);
    status=clEnqueueWriteBuffer(command_queue,bufferB,CL_FALSE,0,sizeof(int),B,0,NULL,NULL);
    cl_program program=clCreateProgramWithSource(context,1,(const char**)&programSource,NULL,&status);
    status=clBuildProgram(program,num_device,device,NULL,NULL,NULL);
    cl_kernel kernel=clCreateKernel(program,"sajan",&status);
    status=clSetKernelArg(kernel,0,sizeof(cl_mem),&bufferA);
    status|=clSetKernelArg(kernel,1,sizeof(cl_mem),&bufferB);
    status|=clSetKernelArg(kernel,2,sizeof(cl_mem),&bufferC);
    size_t globalWorkSize[1];
    globalWorkSize[0]=1;
    status=clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,globalWorkSize,NULL,0,NULL,NULL);
    clEnqueueReadBuffer(command_queue,bufferC,CL_TRUE,0,sizeof(int),C,0,NULL,NULL);
    printf("The result is %d\n",C[0]);
}
