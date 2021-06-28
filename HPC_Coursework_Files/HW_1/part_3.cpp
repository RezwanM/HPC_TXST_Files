/******************************************************************************************************************************************************
** Rezwan Matin
** EE5321 – HW#1
** Filename: part_3.cpp
** Due: 1/30/19
**
** Objective:
** To multiply two 3x3 matrices whose elements are randomly generated, and to find the average of each element of the output, and to display the result.
**
*******************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    //rx and cx are used for indexing rows and columns of Matrix X. Same for Matrix Y.
    int rx, cx, ry, cy;
    int i, j, k, l, m;

    //Declaring some more variables for our random function.
    int range, rnd;

    //Declaring an array for storing average values of elements.
    int avg[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    //Defining range of the random value, avoiding floating point no.s since % only works with integers.
    range = (200 - (-200)) + 1;


    //Defining loop for running 100 iterations.
    for (l = 0; l <= 99; l++){

        //Defining Matrix X.
        int matX[3][3];
        cout << "Matrix X = ";
            for (rx = 0; rx < 3; rx++){
                for (cx = 0; cx < 3; cx++){
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
        int matY[3][3];
        cout << "Matrix Y = ";
            for (ry = 0; ry < 3; ry++){
                for (cy = 0; cy < 3; cy++){
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
        int matZ[3][3];
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

        //Storing elements for average calculation.
        for (rx = 0; rx < 3; rx++){
            for (cx = 0; cx < 3; cx++){
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

    //Printing out the average values.
        cout << "Average values = ";
        for (i = 0; i < rx; i++)
        {
            for (j = 0; j < cy; j++)
                cout << avg[i][j]/100 << "   ";
            //Printing multiple spaces to align matrix elements.
            cout << endl << "                 ";
        }
        cout << endl;

    return 0;
}
