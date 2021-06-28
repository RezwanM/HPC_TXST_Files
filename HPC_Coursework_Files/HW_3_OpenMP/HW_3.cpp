/******************************************************************************************************************************************************
** Rezwan Matin
** EE5321 – HW#3
** Filename: HW_3.cpp
** Due: 2/18/19
**
** Objective:
** To multiply two 10,000 x 10,000 matrices whose elements are randomly generated, to run the multiplication 1000 times and find the average of each element of the output, and to time the program - all using OpenMP.
**
*******************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <omp.h>

using namespace std;

int main()
{

    omp_set_num_threads(28);
    //Declaring some more variables for our random function.
    int dimension = 10000, iterations = 1000;

    //clock_t is an arithmetic type representing clock tick counts.
    clock_t start_mul, finish_mul, start_whole, finish_whole;
    float time_for_program = 0, avg_time_for_mul = 0, time_for_mul = 0;

    //Starting the timer for the entire program.
    start_whole = clock();

    //Seeding the rand function.
    srand(time(0));

    //Dynamically allocating memory for our matrix arrays.
    float** matX = new float*[dimension];
    float** matY = new float*[dimension];
    float** matZ = new float*[dimension];

        for(int i = 0; i < dimension; i++){
            //Dynamic allocation for matrix X 2D array.
            matX[i] = new float[dimension]();
            //Dynamic allocation for matrix Y 2D array.
            matY[i] = new float[dimension]();
            //Dynamic allocation for matrix Z 2D array.
            matZ[i] = new float[dimension]();
        }

   //Starting the multiplication timer.
   start_mul = clock();

        //Defining loop for running multiple iterations.
        for (int l = 0; l < iterations; l++){
            //Matrix X and Y.
            for (int i = 0; i < dimension; i++){
                for (int j = 0; j < dimension; j++){
                    //Generating the random number and storing the random number as an element of Matrix X.
                    matX[i][j] = (199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;
                    matY[i][j] = (199.9 + 199.9)*((float) rand()/(float)RAND_MAX) - 199.9;
                }
            }

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

    //Ending the multiplication timer.
    finish_mul = clock();

    //Calculating time for multiplying the two matrices once.
    time_for_mul = ((float) (finish_mul - start_mul)) / CLOCKS_PER_SEC;

    //Printing Matrix Z for the 10th iteration.
    cout << "Average matrix =" << endl;
        for (int i = 0; i < dimension; i++){
            for (int j = 0; j < dimension; j++){
                cout << matZ[i][j] / iterations << " ";
            }
            //Printing new line.
            cout << endl;
        }

    //Ending the timer for the entire program.
    finish_whole = clock();

    //Calculating time taken to run the entire program.
    time_for_program = ((float) (finish_whole - start_whole)) / CLOCKS_PER_SEC;

    cout << endl;

    //Printing the average time for multiplying and the time for entire program to run.
    cout << "Average time of multiplication = " << time_for_mul / iterations << endl;
    cout << "Time for running the entire program = " << time_for_program;

    return 0;

}
