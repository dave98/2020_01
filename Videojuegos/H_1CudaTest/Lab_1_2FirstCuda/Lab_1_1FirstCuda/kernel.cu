#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
using namespace std;

// Can´t use iostream enviroments inside cuda kernels
__global__ void myFirstKernel() {
	printf("First kernel");
}

int main() {
	myFirstKernel <<< 1, 1 >>> ();
}