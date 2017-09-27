#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Main function for organizing the program execution.
// The functions and object predefined are just for inspiration.
// Please change order, names arguments to fit your solution.



int main(){
    int N = 72; //Size of array'
    int *x = (int *) malloc(N * sizeof(int)); //Allocate size of array x
    int *y = (int *) malloc(N * sizeof(int)); //Allocate size of array x
    memset(x, 0, N * sizeof(int)); //Set the values in array x to zero
    memset(y, 0, N * sizeof(int)); //Set the values in array y to zero

    int x_low[N];
    int x_high[N];
    int x_der[N];
    int x_sqr;
    int x_moveWin;

    QRS_params qsr_params;                   // Instance of the made available through: #include "qsr.h"
    openfile("ECG.txt");                     // Pointer to a file object;
    for (int i = 0 ; i < 5 ; i++) {
        //Run lowPassFilter function 33 times
        for (int i = 0; i < N; i++) {
            //printf("*x[%d]: %d\n",i, x[i]);
            x_low[i] = lowPassFilter(getNextData(), x, y);
        }


        //Setup array
        int x_high[30];

        //run highPassFilter i times
        for (int i = 0; i < 30; i++) {
            x_high[i] = highPassFilter(x_low[i], x, y);
        }


        //Setup array
        int x_der[30];

        //run highPassFilter i times
        for (int i = 0; i < 30; i++) {
            x_der[i] = derivative(x_high[i], x);
        }



        //Setup array
        int x_sqr[30];

        //run Square i times
        for (int i = 0; i < 30; i++) {
            x_sqr[i] = square(x_der[i], x);
        }



        //Setup array
        int x_mwi[30];

        //run Square i times
        for (int i = 0; i < 30; i++) {
            //printf("%d ",x_sqr[i]);
        }

        sum = moveWin(x_sqr, x);
        printf("%d",sum/30);
        for (int i = 0 ; i < (sum/30)/100 ; i++){
            printf(" ");
        }
        printf("*\n");
        peakDetection(&qsr_params);              // Perform Peak Detection
    }
    return 0;
}
