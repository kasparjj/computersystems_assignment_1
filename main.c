#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change order, names arguments to fit your solution.


int main()
{
    int My;

    QRS_params qsr_params;                   // Instance of the made available through: #include "qsr.h"
    openfile("ECG.txt");                     // Pointer to a file object;

    int N = 100; //Size of array's

    int  *x = (int * ) malloc(N * sizeof(int)); //Allocate size of array x
    int  *y = (int * ) malloc(3 * sizeof(int)); //Allocate size of array x

    memset(x, 0, N * sizeof (int)); //Set the values in array x to zero
    memset(y, 0, 3 * sizeof (int)); //Set the values in array y to zero

    //for(int i = 0; i < 10; i++){
    //    printf("moveWin(%d, %d, %d): %d\n",getNextData(), x, y, moveWin(getNextData(), x, y));
    //}



    int x_low[N];

    //Run lowPassFilter function 33 times
    for(int i = 0;i < N; i++){
        //printf("*x[%d]: %d\n",i, x[i]);
        x_low[i] = lowPassFilter(getNextData(), x, y);
    }

    memset(x, 0, N * sizeof (int)); //Set the values in array x to zero
    memset(y, 0, N * sizeof (int)); //Set the values in array y to zero

    //Setup array
    int x_high[30];

    //run highPassFilter i times
    for(int i = 0; i < 30; i++){
        x_high[i] = highPassFilter(x_low[i], x, y);
    }

    memset(x, 0, N * sizeof (int)); //Set the values in array x to zero

    //Setup array
    int x_der[30];

    //run highPassFilter i times
    for(int i = 0; i < 30; i++){
        x_der[i] = derivative(x_high[i], x);
    }

    memset(x, 0, N * sizeof (int)); //Set the values in array x to zero

    //Setup array
    int x_sqr[30];

    //run Square i times
    for(int i = 0; i < 30; i++){
        x_sqr[i] = square(x_der[i], x);
    }

    memset(x, 0, N * sizeof (int)); //Set the values in array x to zero

    //Setup array
    int x_mwi[30];

    //run Square i times
    for(int i = 0; i < 30; i++){
        //printf("%d ",x_sqr[i]);
    }

    x_mwi[0] = moveWin(x_sqr, x);

    peakDetection(&qsr_params);              // Perform Peak Detection

    return 0;
}
