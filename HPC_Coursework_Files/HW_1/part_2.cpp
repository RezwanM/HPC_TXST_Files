/***********************************************************************************************
** Rezwan Matin
** EE5321 – HW#1
** Filename: part_2.cpp
** Due: 1/30/19
**
** Objective:
** To multiply two 3x3 matrices whose elements are randomly generated, and to display the result.
**
************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
    //rx and cx are used for indexing rows and columns of Matrix X. Same for Matrix Y.
    int rx, cx, ry, cy;
    int i, j, k;

    //Declaring some more variables for our random function.
    int range, rnd;
    //Defining range of the random value, avoiding floating point no.s since % only works with integers.
    range = (200 - (-200)) + 1;


    //Initialize random seed. time(0) function counts the seconds since year 1970, which makes srand output 'random'.
    srand (time (0));

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
    //Printing out the elements of Matrix Z.
    cout << "Matrix Z = ";
    for (i = 0; i < rx; i++)
    {
        for (j = 0; j < cy; j++)
            cout << matZ[i][j] << "   ";
        //Printing multiple spaces to align matrix elements.
        cout << endl << "           ";
    }
    return 0;
}
