#include <iostream>

using namespace std;

int main()
{
    int rx, cx, ry, cy; //rx and cx are used for indexing rows and columns of Matrix X. Same for Matrix Y.
    int i, j, k;
    float matX[3][3] = {{2.33, 4.53, -98.4}, {28.54, -75.6, 23.44}, {102.33, 3.3, -45.01}}; //Defining Matrix X.
    cout << "Matrix X = ";
        for (rx = 0; rx < 3; rx++){
            for (cx = 0; cx < 3; cx++){
            cout << matX[rx][cx]<< "   "; //Printing a space between each matrix element.
            }
        cout << endl << "           "; //Printing multiple spaces to align matrix elements.
        }

    cout << endl; //Start from new line for Matrix Y.

    float matY[3][3] = {{46.73, 43.6, 92.1}, {-2.233, -116.8, -11.4}, {156.8, 13.44, 67.8}}; //Defining Matrix Y.
    cout << "Matrix Y = ";
        for (ry = 0; ry < 3; ry++){
            for (cy = 0; cy < 3; cy++){
            cout << matY[ry][cy]<< "   "; //Printing a space between each matrix element.
            }
        cout << endl << "           "; //Printing multiple spaces to align matrix elements.
        }

    cout << endl; //Start from new line for Matrix Z.

    float matZ[3][3]; //Matrix Z will be the product of Matrix X and Matrix Y.
    for (i = 0; i < rx; i++)
    {
        for (j = 0; j < cy; j++)
        {
            matZ[i][j] = 0;
            for (k = 0; k < ry; k++)
            {
                matZ[i][j] += matX[i][k] * matY[k][j];
            }
        }
    }
    cout << "Matrix Z = ";
    for (i = 0; i < rx; i++)
    {
        for (j = 0; j < cy; j++)
            cout << matZ[i][j] << "   ";
        cout << endl << "           ";
    }
    return 0;
}
