#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>	
using namespace std;

void print_function(int*, int);

// Programando Tarjeta// 
__global__ void k_vector_sum_constante(int* arr, int* ans, int n, int constant) {  // arr -> Vector, ans -> Resultado, n -> tamaño de array
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < n) {
		ans[idx] = arr[idx] + constant;
	}
}

__global__ void k_vector_minus_constante(int* arr, int* ans, int n, int constant) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < n) {
		ans[idx] = arr[idx] - constant;
	}
}

__global__ void k_vector_sum_vector(int *ans, const int *arr_1, const int *arr_2, int size)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < size) {
		ans[idx] = arr_1[idx] + arr_2[idx];
	}
}

__global__ void k_vector_minus_vector(int *ans, const int *arr_1, const int *arr_2, int size)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < size) {
		ans[idx] = arr_1[idx] - arr_2[idx];
	}
}


void facade_k_vector_sum_minus_constante(int *arr, int* answer, unsigned int size, int k, char mood) {
	int *dev_arr = 0;
	int *dev_answer = 0;
	int dev_k = k;

	cudaSetDevice(0); // Seleccionando primera tarjeta de video en caso de sistemas con multiples tarjetas.
	cudaMalloc((void**)&dev_arr, size * sizeof(int)); // Reservando espacio de memoria en dispositivo
	cudaMalloc((void**)&dev_answer, size * sizeof(int));

	cudaMemcpy(dev_arr, arr, size * sizeof(int), cudaMemcpyHostToDevice); // Copiando contenido de vector a dispositivo
	if (mood == 's') {
		k_vector_sum_constante << <ceil(size / 500), 500 >> > (dev_arr, dev_answer, size, dev_k);
	}
	else {
		k_vector_minus_constante << < ceil(size / 500), 500 >> > (dev_arr, dev_answer, size, dev_k);
	}
	cudaDeviceSynchronize();

	cudaMemcpy(answer, dev_answer, size * sizeof(int), cudaMemcpyDeviceToHost); // Devolviendo datos del dispositivo
	cudaFree(dev_arr);
	cudaFree(dev_answer);
	return;
}

void facade_k_vector_sum_minus_vector(int* ans, int* arr_1, int* arr_2, unsigned int size, char mood) {
	int* dev_ans = 0;
	int* dev_arr_1 = 0;
	int* dev_arr_2 = 0;

	cudaSetDevice(0);
	cudaMalloc((void**)&dev_ans, size * sizeof(int));
	cudaMalloc((void**)&dev_arr_1, size * sizeof(int));
	cudaMalloc((void**)&dev_arr_2, size * sizeof(int));

	cudaMemcpy(dev_arr_1, arr_1, size * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_arr_2, arr_2, size * sizeof(int), cudaMemcpyHostToDevice);

	if (mood == 's') {
		k_vector_sum_vector << <ceil(size / 500), 500 >> > (dev_ans, dev_arr_1, dev_arr_2, size);
	}
	else {
		k_vector_minus_vector << <ceil(size / 500), 500 >> > (dev_ans, dev_arr_1, dev_arr_2, size);
	}
	cudaDeviceSynchronize();

	cudaMemcpy(ans, dev_ans, size * sizeof(int), cudaMemcpyDeviceToHost);
	cudaFree(dev_ans);
	cudaFree(dev_arr_1);
	cudaFree(dev_arr_2);
	return;
}

// Programando CPU <-- Separando ambos ambientes //
int main() {
	int size = 1000;
	int* arr = new int[size];
	int* arr_2 = new int[size];
	int* answer = new int[size];
	int constant = 2; // Cantidad a sumar o restar

	for (int i = 0; i < size; i++) {//Inicializando
		arr[i] = i;
		arr_2[i] = i + i;
		answer[i] = 1;
	}

	//Probando suma resta de vector con vector 
	cout << "Primer vector" << endl;
	print_function(arr, size);
	cout << "Segundo vector" << endl;
	print_function(arr_2, size);
	facade_k_vector_sum_minus_vector(answer, arr, arr_2, size, 's'); // s -> suma, m -> resta
	cout << "Vector resultante" << endl;
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


