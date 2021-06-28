#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{

    //Declaring some more variables for our random function.
    int dimension = 10000, iterations = 1;

    //clock_t is an arithmetic type representing clock tick counts.
    clock_t start_mul, finish_mul, start_whole, finish_whole;
    double time_for_program = 0, avg_time_for_mul = 0, time_for_mul = 0;

    start_whole = clock();

    srand(time(0));
    double** matX = new double*[dimension];
    double** matY = new double*[dimension];
    double** matZ = new double*[dimension];

        for(int i = 0; i < dimension; i++){
        //Dynamic allocation for matrix X 2D array.
        matX[i] = new double[dimension];
        //Dynamic allocation for matrix Y 2D array.
        matY[i] = new double[dimension];
        //Dynamic allocation for matrix Z 2D array.
        matZ[i] = new double[dimension];
        }

   start_mul = clock();
    //Defining loop for running multiple iterations.
    for (int l = 0; l < iterations; l++){

            //Matrix X.
            for (int i = 0; i < dimension; i++){
                for (int j = 0; j < dimension; j++){
                //Generating the random number and storing the random number as an element of Matrix X.
                //double randNumX = (199.9 + 199.9)*((double) rand()/(double)RAND_MAX) - 199.9;
                matX[i][j] = 1;
                }
            }

            //Matrix Y.
            for (int i = 0; i < dimension; i++){
                for (int j = 0; j < dimension; j++){
                //Generating the random number and storing the random number as an element of Matrix Y.
                    //double randNumY = (199.9 + 199.9)*((double) rand()/(double)RAND_MAX) - 199.9;
                    matY[i][j] = 1;
                }
            }
            //Matrix Z will be the product of Matrix X and Matrix Y.
            for (int i = 0; i < dimension; i++){
                for (int j = 0; j < dimension; j++){
                    matZ[i][j] = 0;
                    for (int k = 0; k < dimension; k++){
                        //Multiplying corresponding elements and adding them.
                        matZ[i][j] += matX[i][k] * matY[k][j];
                    }
                }
            }
    }

    finish_mul = clock();

    //Calculating time for multiplying the two matrices once.
    time_for_mul = ((double) (finish_mul - start_mul)) / CLOCKS_PER_SEC;

    //Printing Matrix Z for the 10th iteration.
    cout << "Average matrix = \n";
        for (int i = 0; i < dimension; i++){
            for (int j = 0; j < dimension; j++){
                cout << matZ[i][j] / iterations << " ";
            }
            //Printing multiple spaces to align matrix elements.
            cout << endl;
        }

    cout << endl;

    finish_whole = clock();

    //Calculating time taken to run the entire program.
    time_for_program = ((double) (finish_whole - start_whole)) / CLOCKS_PER_SEC;

    //Printing the average time for multiplying and the time for entire program to run.
    cout << "Average time of multiplication = " << time_for_mul / iterations << endl;
    cout << "Time for running the entire program = " << time_for_program << endl;

    //Clearing up memory.
        for(int i = 0; i < dimension; i++){
        delete [] matX[i];
        delete [] matY[i];
        delete [] matZ[i];
        }

    delete [] matX;
    delete [] matY;
    delete [] matZ;

    return 0;

}
