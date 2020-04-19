#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

using namespace std;

void main() {
	cudaDeviceProp prop;
	int count = 0;
	cudaGetDeviceCount(&count);

	for (int index = 0; index < count; index++) {
		cudaGetDeviceProperties(&prop, index);

		cout << prop.name << endl;
		cout << prop.minor << " - " << prop.major << endl;
		cout << prop.clockRate << endl;
	}
}

/* Resultados */
/*
GeForce 930MX
0 - 5
1019500
*/