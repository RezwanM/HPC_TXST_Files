/******************************************************************************************************************************************************
** Rezwan Matin
** EE5321 – HW#2
** Filename: part_2.cpp
** Due: 2/6/19
**
** Objective:
** To multiply two 10,000 x 10,000 matrices whose elements are randomly generated, and to find the average of each element of the output, and to time the program.
**
*******************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
    //rx and cx are used for indexing rows and columns of Matrix X. Same for Matrix Y.
    int rx, cx, ry, cy;
    int i, j, k, l, m;

    //Declaring some more variables for our random function.
    int range, rnd;

    //clock_t is an arithmetic type representing clock tick counts.
    clock_t start_mul, finish_mul, start_whole, finish_whole;
    double time_for_program = 0, avg_time_for_mul = 0, time_for_mul = 0;

    start_whole = clock();

    //Declaring an array for storing average values of elements.
    int avg[10000][10000] = {0};

    //Defining range of the random value, avoiding floating point no.s since % only works with integers.
    range = (200 - (-200)) + 1;


    //Defining loop for running 100 iterations.
    for (l = 0; l <= 999; l++){

        //Defining Matrix X.
        int matX[10000][10000];
        cout << "Matrix X = ";
            for (rx = 0; rx < 10000; rx++){
                for (cx = 0; cx < 10000; cx++){
                //Generating the random number.
                rnd = -200 + rand() % range;
                //Storing the random number as an element of Matrix X.
                matX[rx][cx] = rnd;
                //Printing a space between each matrix element.
                cout << matX[rx][cx]<< "   ";
                }
            //Printing multiple spaces to align matrix elements.
            cout << endl << "           ";
            }
        //Start from new line for Matrix Y.
        cout << endl;

        //Defining Matrix Y.
        int matY[10000][10000];
        cout << "Matrix Y = ";
            for (ry = 0; ry < 10000; ry++){
                for (cy = 0; cy < 10000; cy++){
                //Generating the random number.
                rnd = -200 + rand() % range;
                //Storing the random number as an element of Matrix Y.
                matY[ry][cy] = rnd;
                //Printing a space between each matrix element.
                cout << matY[ry][cy]<< "   ";
                }
            //Printing multiple spaces to align matrix elements.
            cout << endl << "           ";
            }

        //Start from new line for Matrix Z.
        cout << endl;


        //Matrix Z will be the product of Matrix X and Matrix Y.
        int matZ[10000][10000];
        start_mul = clock();
        for (i = 0; i < rx; i++)
        {
            for (j = 0; j < cy; j++)
            {
                matZ[i][j] = 0;
                for (k = 0; k < ry; k++)
                {
                    //Multiplying corresponding elements and adding them.
                    matZ[i][j] += matX[i][k] * matY[k][j];
                }
            }
        }

        finish_mul = clock();

        //Calculating time for multiplying the two matrices once.
        time_for_mul = ((double) (finish_mul - start_mul)) / CLOCKS_PER_SEC;
        avg_time_for_mul = avg_time_for_mul + time_for_mul;

        //Storing elements for average calculation.
        for (rx = 0; rx < 10000; rx++){
            for (cx = 0; cx < 10000; cx++){
            avg[rx][cx] += matZ[rx][cx];
            }
        }

        //Printing out the elements of Matrix Z.
        cout << "Matrix Z = ";
        for (i = 0; i < rx; i++)
        {
            for (j = 0; j < cy; j++)
                cout << matZ[i][j] << "   ";
            //Printing multiple spaces to align matrix elements.
            cout << endl << "           ";
        }
        cout << endl;
    }

    //Calculating the average time for multiplying.
    avg_time_for_mul = avg_time_for_mul / 1000;

    //Printing out the average values.
        cout << "Average values = ";
        for (i = 0; i < rx; i++)
        {
            for (j = 0; j < cy; j++)
                cout << avg[i][j]/1000 << "   ";
            //Printing multiple spaces to align matrix elements.
            cout << endl << "                 ";
        }
        cout << endl;

    finish_whole = clock();

    //Calculating time taken to run the entire program.
    time_for_program = ((double) (finish_whole - start_whole)) / CLOCKS_PER_SEC;

    //Printing the average time for multiplying and the time for entire program to run.
    cout << "Average time of multiplication = " << avg_time_for_mul << endl;
    cout << "Time for running the entire program = " << time_for_program << endl;

    return 0;
}
