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
        int rank, size, rc, offset, rows;
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
        omp_set_num_threads(28);

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

                // MPI_Scatter(&sendbuffer, sendcount, sendtype, &recvbuf, recvcnt, recvtype, root, comm)

                for (int dest=1; dest <= size-1; dest++) {
                        printf("Sending %d rows to task %d offset=%d\n", rows, dest, offset);
                         MPI_Scatter(&offset, 1, MPI_INT, &offset, 1, MPI_INT, dest, MPI_COMM_WORLD);
                         MPI_Scatter(&rows, 1, MPI_INT, &rows, 1, MPI_INT, dest, MPI_COMM_WORLD);
                         MPI_Scatter(&matX[offset][0], rows*dimension, MPI_FLOAT, &matX[offset][0], rows*dimension, MPI_FLOAT, dest, MPI_COMM_WORLD);
                         MPI_Scatter(&matY[0][0], dimension*dimension, MPI_FLOAT, &matY[0][0], dimension*dimension, MPI_FLOAT, dest, MPI_COMM_WORLD);
                         offset = offset + rows;
                }

                // Need to receive data from the workers
                int source;

                // MPI_Gather(&sendbuffer, sendcount, sendtype, &recvbuf, recvcnt, recvtype, root, comm)

                for (int i=1; i<=size-1; i++) {
                        source = i;
                        MPI_Gather(&offset, 1, MPI_INT, &offset, 1, MPI_INT, source, MPI_COMM_WORLD);
                        MPI_Gather(&rows, 1, MPI_INT, &rows, 1, MPI_INT, source, MPI_COMM_WORLD);
                        MPI_Gather(&matZ[offset][0], rows*dimension, MPI_FLOAT, &matZ[offset][0], rows*dimension, MPI_FLOAT, source, MPI_COMM_WORLD);
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


        /*      MPI_Scatter(&sendbuffer, sendcount, sendtype, &recvbuf, recvcnt, recvtype, root, comm)
                MPI_Gather(&sendbuffer, sendcount, sendtype, &recvbuf, recvcnt, recvtype, root, comm) */


        if (rank > 0)  {
                 MPI_Gather(&offset, 1, MPI_INT, &offset, 1, MPI_INT, 0, MPI_COMM_WORLD);
                 MPI_Gather(&rows, 1, MPI_INT, &rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
                 MPI_Gather(&matX[offset][0], rows*dimension, MPI_FLOAT, &matX[offset][0], rows*dimension, MPI_FLOAT, 0, MPI_COMM_WORLD);
                 MPI_Gather(&matY[0][0], dimension*dimension, MPI_FLOAT, &matY[0][0], dimension*dimension, MPI_FLOAT, 0, MPI_COMM_WORLD);


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

                MPI_Scatter(&offset, 1, MPI_INT, &offset, 1, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(&rows, 1, MPI_INT, &rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(&matZ[offset][0], rows*dimension, MPI_FLOAT, &matZ[offset][0], rows*dimension, MPI_FLOAT, 0, MPI_COMM_WORLD);
         }
        //***
        // END of WORKER Code
        //***

        MPI_Finalize();

        return 0;
}
