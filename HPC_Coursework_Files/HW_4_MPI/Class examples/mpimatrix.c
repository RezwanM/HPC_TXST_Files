#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

        int rank, size, rc, tag, offset, rows;

        double a[100][100],
               b[100][100],
               c[100][100];

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        if (size < 2) {
                printf("Need @ least 2 MPI Processes.  Goodbye!\n\n");
                MPI_Abort(MPI_COMM_WORLD, rc);
                exit(1);
        }
        //*** 
        //  THE MASTER CODE
        //***

        if(rank == 0) {
                printf("The fun has started with %d tasks.\n", size);
                 printf("Initializing arrays...\n");
                 for (int i=0; i<100; i++) {
                         for (int j=0; j<100; j++) {
                                 a[i][j]= i+j;
                                 b[i][j]= i*j;
                        }
                }

                // Send matrix data to the workers
                rows = 100 / (size-1);
                offset = 0;
                tag = 1; // From MASTER
        
                // MPI_Send (buffer, count, type, dest, tag, comm)

                for (int dest=1; dest <= size-1; dest++) {
                        printf("Sending %d rows to task %d offset=%d\n", rows, dest, offset);
                         MPI_Send(&offset, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&rows, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&a[offset][0], rows*100, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
                         MPI_Send(&b, 100*100, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
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
                        MPI_Recv(&c[offset][0], rows*100, MPI_DOUBLE, source, tag,MPI_COMM_WORLD, &status);
                        printf("Received results from task %d\n", source);
                 }
                
                 printf("******************************************************\n");
                 printf("Result Matrix:\n");
                 for (int i=0; i<100; i++) {
                         printf("\n"); 
                         for (int j=0; j<100; j++) {
                                 printf("%6.2f   ", c[i][j]); }
                 }
                 printf("\n******************************************************\n");
                 printf ("Done.\n");
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
                 MPI_Recv(&a, rows*100, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
                 MPI_Recv(&b, 100*100, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);

                 for (int k=0; k<100; k++) {
                         for (int i=0; i<rows; i++) {
                                 c[i][k] = 0.0;
                                 for (int j=0; j<100; j++)
                                         c[i][k] = c[i][k] + a[i][j] * b[j][k];
                         }
                }
      
                tag = 2; //From WORKER
                MPI_Send(&offset, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                MPI_Send(&rows, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                MPI_Send(&c, rows*100, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
         }
        //***
        // END of WORKER Code
        //***

        MPI_Finalize();

        return 0;
}