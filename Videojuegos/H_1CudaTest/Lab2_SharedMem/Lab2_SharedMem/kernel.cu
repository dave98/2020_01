#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#ifndef __CUDACC_RTC__   // for __syncthreads()
#define __CUDACC_RTC__
#endif // !(__CUDACC_RTC__)

#ifndef __CUDACC__  // for atomicAdd()
#define __CUDACC__
#endif // !__CUDACC__

#include "device_atomic_functions.h"
#include "device_functions.h"
#include <stdio.h>
#include <iostream>	
#include <time.h>
#include <stdlib.h>
using namespace std;

void print_function(float*, int, int);
void fill_function(float*, int, int, int is_zero = -1);


__global__ void kernel_1(int columns, int rows, float* mat1, float* matanswer) {
	int columna = threadIdx.x;  //En que columna operamos (no filas)
	float temp_value = 0;

	for (int k = 0; k < rows; k++) {
		temp_value = temp_value + mat1[(k * columns) + columna];
	}
	matanswer[columna] = temp_value;
}

__global__ void kernel_2_shared(int columns, int rows, float* mat1, float* matanswer) {
	__shared__ float temp_answer[32];
	if (threadIdx.y == 0) {
		temp_answer[threadIdx.x] = float(0);
	}
	__syncthreads();  //Existe pero no es reconocido por Itellisense

	int thread_mat_colid = blockIdx.x * blockDim.x + threadIdx.x;
	int thread_mat_rowid = blockIdx.y * blockDim.y + threadIdx.y;
	int position_in_matrix = thread_mat_rowid * columns + thread_mat_colid;

	atomicAdd(&(temp_answer[threadIdx.x]), mat1[position_in_matrix]);
	__syncthreads();  //Existe pero no es reconocido por Itellisense

	if (blockIdx.x == 0 && blockIdx.y == 1 && threadIdx.x == 0 && threadIdx.y == 0) {
		printf("%d Value %f \n", position_in_matrix, mat1[position_in_matrix]);
	}

	if (threadIdx.y == rows - 1) {
		atomicAdd(&(matanswer[thread_mat_colid]), temp_answer[threadIdx.x]);
	}
	__syncthreads();
	//printf("BlockID_x: %d BlockID_y: %d Blockdim_x: %d  Blockdim_y: %d ThreadIdx_x: %d ThreadIdx_y: %d \n",  blockIdx.x, blockIdx.y, blockDim.x, blockDim.y, threadIdx.x, threadIdx.y);
}

void column_sum_facade(int columns, int rows, float* mat1, float* matanswer) {
	int size = columns * rows * sizeof(float); // Matriz de entrada
	int size_2 = columns * sizeof(float);      // Vector con los resultados     
	float* dev_mat1;
	float* dev_matanswer;

	cudaSetDevice(0);
	cudaMalloc((void**)&dev_mat1, size);       //Reservando espacio
	cudaMalloc((void**)&dev_matanswer, size_2);

	cudaMemcpy(dev_mat1, mat1, size, cudaMemcpyHostToDevice);   //Inicializando con datos
	cudaMemset(dev_matanswer, 0, size_2);

	//kernel_1 <<< 1, 1024>>> (columns, rows, dev_mat1, dev_matanswer);
	dim3 grid_dim = dim3(ceil(columns / 32), ceil(rows / 16), 1);  // Numero de bloques en un grid
	dim3 block_dim = dim3(32, 16, 1);                              // Numero de threads en un bloque
	kernel_2_shared << < grid_dim, block_dim >> > (columns, rows, dev_mat1, dev_matanswer);

	cudaMemcpy(matanswer, dev_matanswer, size_2, cudaMemcpyDeviceToHost);
	cudaFree(dev_mat1);
	cudaFree(dev_matanswer);
}


// Programando CPU <-- Separando ambos ambientes //
int main() {
	srand(time(NULL));

	const int col_siz = 64;
	const int row_siz = 16;

	float* arr_1 = new float[col_siz * row_siz];
	float* arr_ans = new float[col_siz];


	fill_function(arr_1, col_siz, row_siz);
	fill_function(arr_ans, col_siz, 1, 0);

	column_sum_facade(col_siz, row_siz, arr_1, arr_ans);

	print_function(arr_1, col_siz, row_siz);
	print_function(arr_ans, col_siz, 1);


	cudaDeviceReset();
	return 0;
}


void print_function(float* arr, int col, int row) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i * col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void fill_function(float* arr, int col, int row, int is_zero) {
	if (is_zero == -1) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				arr[i * col + j] = float(rand() % 10);
			}
		}
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				arr[i * col + j] = float(is_zero);
			}
		}
	}

}
