#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{

     clock_t start, fin;
     int i;
     double cpu_time_used;

     start = clock();
     for (i = 0; i<=100; i++){
     cout << "This is Sparta!" << endl; }
     fin = clock();
     cpu_time_used = ((double) (fin - start)) / CLOCKS_PER_SEC;
     cout << cpu_time_used << endl;
    return 0;
}
