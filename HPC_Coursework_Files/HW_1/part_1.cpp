/*****************************************************
** Rezwan Matin
** EE5321 – HW#1
** Filename: part_1.cpp
** Due: 1/30/19
**
** Objective:
** To multiply two 3x3 matrices and display the result.
**
******************************************************/

#include <iostream>

using namespace std;

int main()
{
    //rx and cx are used for indexing rows and columns of Matrix X. Same for Matrix Y.
    int rx, cx, ry, cy;
    int i, j, k;

    //Defining Matrix X.
    float matX[3][3] = {{2.33, 4.53, -98.4}, {28.54, -75.6, 23.44}, {102.33, 3.3, -45.01}};
    cout << "Matrix X = ";
        for (rx = 0; rx < 3; rx++){
            for (cx = 0; cx < 3; cx++){
            //Printing a space between each matrix element.
            cout << matX[rx][cx]<< "   ";
            }
        //Printing multiple spaces to align matrix elements.
        cout << endl << "           ";
        }
    //Start from new line for Matrix Y.
    cout << endl;

    //Defining Matrix Y.
    float matY[3][3] = {{46.73, 43.6, 92.1}, {-2.233, -116.8, -11.4}, {156.8, 13.44, 67.8}};
    cout << "Matrix Y = ";
        for (ry = 0; ry < 3; ry++){
            for (cy = 0; cy < 3; cy++){
            //Printing a space between each matrix element.
            cout << matY[ry][cy]<< "   ";
            }
        //Printing multiple spaces to align matrix elements.
        cout << endl << "           ";
        }

    //Start from new line for Matrix Z.
    cout << endl;

    //Matrix Z will be the product of Matrix X and Matrix Y.
    float matZ[3][3];
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
