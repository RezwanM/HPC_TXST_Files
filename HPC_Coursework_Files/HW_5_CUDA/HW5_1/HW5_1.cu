/******************************************************************************************************************************************************
** Rezwan Matin
** EE5321 – HW#5_1
** Filename: HW5_1.cu
** Due: 4/5/19
**
** Objective:
** To multiply two 2000 x 2000 matrices whose elements are randomly generated, to print out the resultant matrix, and to time the program - all using CUDA C.
**
*******************************************************************************************************************************************************/

#include <stdio.h>
#include <time.h>
#include <cuda.h>
#include <stdlib.h>
#include <math.h>

#define Tile_size 32
#define dimension 2000

int numARows = dimension;   //Number of rows in the matrix A.
int numAColumns = dimension;  //Number of columns in the matrix A.
int numBRows = dimension;   //Number of rows in the matrix B.
int numBColumns = dimension;  //Number of columns in the matrix B.
int numCRows;  //Number of rows in the matrix C.
int numCColumns;  //Number of columns in the matrix C.


/*************************************************************
*
* 	Matrix Multiplication Kernel Function
*
**************************************************************/
__global__ void matrixMultiply(float * A, float * B, float * C,
                               int numARows, int numAColumns,
                               int numBRows, int numBColumns,
                               int numCRows, int numCColumns)  {

        //Tile size arrays.
        __shared__ float sA[Tile_size][Tile_size];
    	__shared__ float sB[Tile_size][Tile_size];

        //IDs of threads.
    	int Row = blockDim.y*blockIdx.y + threadIdx.y;
    	int Col = blockDim.x*blockIdx.x + threadIdx.x;
    	float Cvalue = 0.0;

        //Initialized to zero.
        sA[threadIdx.y][threadIdx.x] = 0.0;
    	sB[threadIdx.y][threadIdx.x] = 0.0;

    	for (int k = 0; k < (((numAColumns - 1)/ Tile_size) + 1); k++)  {

            //Copy data to tile from matrix A.
            if ( (Row < numARows) && (threadIdx.x + (k*Tile_size)) < numAColumns) {
                sA[threadIdx.y][threadIdx.x] = A[(Row*numAColumns) + threadIdx.x + (k*Tile_size)];
            }
        	else {
                sA[threadIdx.y][threadIdx.x] = 0.0; // if outside the boundaries of the matrix
        	}

            //Copy data to tile from matrix B.
            if ( Col < numBColumns && (threadIdx.y + k*Tile_size) < numBRows) {
                sB[threadIdx.y][threadIdx.x] = B[(threadIdx.y + k*Tile_size)*numBColumns + Col];
        	}
        	else {
                sB[threadIdx.y][threadIdx.x] = 0.0; //if outside the boundary of the matrix
        	}

            //Making sure all threads have arrived before multiplications.
            __syncthreads();

            //Multiplying elements present in the current tile.
        	for (int j = 0; j < Tile_size; ++j) {
                Cvalue += sA[threadIdx.y][j] * sB[j][threadIdx.x];  //each thread's C-value in the tile
        	}
    	}

        //Saving final result to Matrix C.
        if (Row < numCRows && Col < numCColumns) {
            C[Row*numCColumns + Col] = Cvalue;
    	}
}

/*************************************************************
*
* 	Matrix Print function
*
**************************************************************/

void Print_Mat(int Row,int Col,float * Mat) {

	for(int i=0;i<Row*Col;i++) {

		printf("%f  ",*(Mat+i));

   		if(( i % Col) == 0 ) {
            printf("\n");
        }
   	}
}

/*************************************************************
*
* 	Main Function
*
**************************************************************/
int main(int argc, char ** argv) {

        float * hostA; // The A matrix
    	float * hostB; // The B matrix
    	float * hostC; // The output C matrix
    	float * deviceA;
    	float * deviceB;
    	float * deviceC;

        clock_t start_whole, finish_whole;
        float time_for_program = 0;

        //Start the timer for the entire program.
        start_whole = clock();

        //Seed the rand function.
        srand(time(0));

    	hostA = (float *) malloc(sizeof(float)*numARows*numAColumns);
    	hostB = (float *) malloc(sizeof(float)*numBRows*numBColumns);

        printf("\nGenerating Matrix A.....\n");
    	for (int i = 0; i < numARows*numAColumns; i++) {
            hostA[i]=(199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;
    	}
        printf("\nDone with Matrix A.....\n");

        printf("\nGenerating Matrix B.....\n");
    	for (int i = 0; i < numBRows*numBColumns; i++) {
            hostB[i]=(199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;;
    	}
        printf("\nDone with Matrix B.....\n");


        //Setting numCRows and numCColumns.
    	numCRows = numARows;
    	numCColumns = numBColumns;

    	hostC = (float *) malloc(sizeof(float)*numCRows*numCColumns);

        //Allocating GPU memory.
    	cudaMalloc((void **)&deviceA, sizeof(float)*numARows*numAColumns);
    	cudaMalloc((void **)&deviceB, sizeof(float)*numBRows*numBColumns);
    	cudaMalloc((void **)&deviceC, sizeof(float)*numCRows*numCColumns);

        //Copy memory to the GPU.
    	cudaMemcpy(deviceA, hostA, sizeof(float)*numARows*numAColumns, cudaMemcpyHostToDevice);
    	cudaMemcpy(deviceB, hostB, sizeof(float)*numBRows*numBColumns, cudaMemcpyHostToDevice);

        //Initialize the grid and block dimensions.
    	dim3 dimGrid((numCColumns/Tile_size) + 1, (numCRows/Tile_size) + 1, 1); //Number of Blocks required
    	dim3 dimBlock(Tile_size, Tile_size, 1);	 //Number of threads in each block
        printf("\n Kernel Call Made....\n");
    	matrixMultiply<<<dimGrid, dimBlock>>>(deviceA, deviceB, deviceC,
						numARows, numAColumns,
						numBRows, numBColumns,
						numCRows, numCColumns);

        //Synchronize threads from the GPU.
    	cudaDeviceSynchronize();

    	// Copy the results in GPU memory back to the CPU.
        printf("\n Bring resutls to the HOST...\n");
    	cudaMemcpy(hostC, deviceC, sizeof(float)*numCRows*numCColumns, cudaMemcpyDeviceToHost);

    	printf("\nMatrix C From Device\n");
    	Print_Mat(numCRows,numCColumns,hostC);


    	printf("\n Number of Blocks Created:%d \n",((numCColumns/Tile_size) + 1)*((numCColumns/Tile_size) + 1));
    	printf("\n Number of Threads Per Block: %d \n",(Tile_size*Tile_size));

        //Ending the timer for the entire program.
        finish_whole = clock();

        //Calculate time taken to run the entire program.
        time_for_program = ((float) (finish_whole - start_whole)) / CLOCKS_PER_SEC;

        //Print time for entire program.
        printf("\n Time for running the entire program = %f \n", time_for_program);

        //Free the GPU memory.
    	cudaFree(deviceA);
    	cudaFree(deviceB);
    	cudaFree(deviceC);

        //Free the Pointer Memory.
    	free(hostA);
    	free(hostB);
    	free(hostC);

        printf("\n Deallocations done!...Goodnight!\n");

    	return 0;
}
