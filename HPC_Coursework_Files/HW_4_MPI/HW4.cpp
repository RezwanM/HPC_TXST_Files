/******************************************************************************************************************************************************
** Rezwan Matin
** EE5321 – HW#4
** Filename: HW4.cpp
** Due: 3/11/19
**
** Objective:
** To multiply two 10,000 x 10,000 matrices whose elements are randomly generated, to run the multiplication 1000 times and find the average of each element of the output, and to time the program - all using OpenMP + MPI.
**
*******************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <omp.h>
#include <mpi.h>

using namespace std;


int main(int argc, char *argv[]) {

        //Declare variables.
        int rank, size, rc, tag, offset, rows;
        int dimension = 10000, iterations = 1000;
        double t1, t2, t3, t4;

        MPI_Status status;

        //Starting MPI parallel execution
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        if (size < 2) { //Checking number of processes.
                printf("Need @ least 2 MPI Processes.  Goodbye!\n\n");
                MPI_Abort(MPI_COMM_WORLD, rc);
                exit(1);
        }

        //Declaring number of threads.
        omp_set_num_threads(25);

        //Dynamically allocating memory using contiguous 2D arrays.

        int a= dimension*dimension;

        float **matX= new float*[dimension];
        matX[0]= new float[a];
        for(int i= 1; i < dimension; i++)
          matX[i]= &matX[0][i*dimension];

        float **matY= new float*[dimension];
        matY[0]= new float[a];
        for(int i= 1; i < dimension; i++)
          matY[i]= &matY[0][i*dimension];

        float **matZ= new float*[dimension];
        matZ[0]= new float[a];
        for(int i= 1; i < dimension; i++)
          matZ[i]= &matZ[0][i*dimension];

        //***
        //  THE MASTER CODE
        //***

        if(rank == 0) {

                //Starting clock for entire program.
                t1 = MPI_Wtime();

                //Defining loop for randomly generating matrix elements 1000 times.
                for (int l = 0; l < iterations; l++){
                    //Matrix X and Y.
                    for (int i = 0; i < dimension; i++){
                        for (int j = 0; j < dimension; j++){
                            //Generating the random number and storing the random number as an element of Matrix X.
                            matX[i][j] = (199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;
                            matY[i][j] = (199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;
                        }
                    }
                }

                // Sending matrix data to the workers.
                rows = dimension / (size-1); //Dividing rows equally among workers.
                offset = 0; //Starting point for each worker.
                tag = 1; // From MASTER

                // MPI_Send (buffer, count, type, dest, tag, comm)

                for (int dest=1; dest <= size-1; dest++) {
                        printf("Sending %d rows to task %d offset=%d\n", rows, dest, offset);
                         MPI_Send(&offset, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&rows, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&matX[offset][0], rows*dimension, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&matY[0][0], dimension*dimension, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
                         offset = offset + rows;
                }

                // Need to receive data from the workers
                tag = 2; // From WORKER
                int source;

                // MPI_Recv(buffer, count, type, source, tag, comm, status)

                for (int i=1; i<=size-1; i++) {
                        source = i;
                        MPI_Recv(&offset, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
                        MPI_Recv(&rows, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
                        MPI_Recv(&matZ[offset][0], rows*dimension, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
                        printf("Received results from task %d\n", source);
                 }

                 //Printing Matrix Z for the 1000th iteration.
                 cout << "Average matrix =" << endl;
                     for (int i = 0; i < dimension; i++){
                         for (int j = 0; j < dimension; j++){
                             cout << matZ[i][j] / iterations << " ";
                         }
                         //Printing new line.
                         cout << endl;
                     }

                cout << endl;

                //Ending clock for entire program.
                t2 = MPI_Wtime();

                //Printing the average time for multiplying and the time for entire program to run.
                cout << "Average time of multiplication = " << t4-t3 / iterations << endl;
                cout << "Time for running the entire program = " << t2-t1;
        }
        //***
        // END of MASTER CODE
        //***

        //***
        // START of WORKER CODE
        //***

        /*      MPI_Send (buffer, count, type, dest, tag, comm)
                MPI_Recv (buffer, count, type, source, tag, comm, status)       */

        if (rank > 0)  {
                 tag = 1; //From MASTER
                 MPI_Recv(&offset, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
                 MPI_Recv(&rows, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
                 MPI_Recv(&matX[offset][0], rows*dimension, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &status);
                 MPI_Recv(&matY[0][0], dimension*dimension, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, &status);


                 //Starting clock for multiplication part.
                 t3 = MPI_Wtime();

                 //Defining loop for multiplying matrices X and Y 1000 times.
                 for (int l = 0; l < iterations; l++){

                     //Matrix Z will be the product of Matrix X and Matrix Y.
                     #pragma omp parallel for shared (matX, matY, matZ)
                     for (int i = 0; i < dimension; i++){
                        for (int j = 0; j < dimension; j++){
                            for (int k = 0; k < dimension; k++){
                                //Multiplying corresponding elements and adding them.
                                matZ[i][j] += matX[i][k] * matY[k][j];
                            }
                        }
                     }
                 }

                //Ending clock for multiplication part.
                t4 = MPI_Wtime();

                tag = 2; //From WORKER
                MPI_Send(&offset, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                MPI_Send(&rows, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                MPI_Send(&matZ[offset][0], rows*dimension, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
         }
        //***
        // END of WORKER Code
        //***

        //Ending all MPI processes.
        MPI_Finalize();

        return 0;
}
