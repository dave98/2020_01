#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>	
using namespace std;

void print_function(int*, int);

// Programando Tarjeta// 
__global__ void k_vector_x_constante(int* arr, int* answer, int n, int k) { // arr -> Vector, n -> tamaño de array, k flotante
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < n) {
		answer[idx] = arr[idx] * k;
	}
}


void facade_k_vector_x_constante(int *arr, int* answer, unsigned int size, int k) {
	int *dev_arr = 0;
	int *dev_answer = 0;
	int dev_k = k;

	//cudaSetDevice(0); // Seleccionando primera tarjeta de video en caso de sistemas con multiples tarjetas.
	
	cudaMalloc((void**)&dev_arr, size * sizeof(int)); // Reservando espacio de memoria en dispositivo
	cudaMalloc((void**)&dev_answer, size * sizeof(int));

	cudaMemcpy(dev_arr, arr, size * sizeof(int), cudaMemcpyHostToDevice); // Copiando contenido de vector a dispositivo
	//k_vector_x_constante<<<ceil(size / 512), 512>>>(dev_arr, dev_answer, size, dev_k); // <<<n_blocks, n_threads >>>
	k_vector_x_constante <<< ceil(size / 500), 500 >>> (dev_arr, dev_answer, size, dev_k); // Can run many blocks  at the same time, newer gps 1024 threads, older gpu 512
	cudaDeviceSynchronize();
	

	cudaMemcpy(answer, dev_answer, size * sizeof(int), cudaMemcpyDeviceToHost); // Devolviendo datos del dispositivo
	cudaFree(dev_arr);
	cudaFree(dev_answer);
	return;
}
//cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);

// Programando CPU <-- Separando ambos ambientes //
int main() {
	int size = 10000;
	int* arr = new int[size];
	int* answer = new int[size];
	int constant = 2;

	for (int i = 0; i < size; i++) {//Inicializando
		arr[i] = i;
		answer[i] = 1;
	}

	print_function(arr, size);
	facade_k_vector_x_constante(arr, answer, size, constant);
	print_function(answer, size);
	
	cudaDeviceReset();
	return 0;
}

void print_function(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ", ";
	}
	cout << endl << endl;
}
