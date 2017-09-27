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
    int arraySize = 80; //Size of array x
    int *x = (int *) malloc(arraySize * sizeof(int)); //Allocate size of array x
    int *x_low = (int *) malloc(arraySize * sizeof(int)); //Allocate size of array x
    int *x_high = (int *) malloc(arraySize * sizeof(int)); //Allocate size of array x
    int *x_der = (int *) malloc(arraySize * sizeof(int)); //Allocate size of array x
    int *x_sqr = (int *) malloc(arraySize * sizeof(int)); //Allocate size of array x


    int *yl = (int *) malloc(3 * sizeof(int)); //Allocate size of array x
    int *yh = (int *) malloc(2 * sizeof(int)); //Allocate size of array x

    memset(x, 0, arraySize * sizeof(int)); //Set the values in array x to zero
    memset(x_low, 0, arraySize * sizeof(int)); //Set the values in array x to zero
    memset(x_high, 0, arraySize * sizeof(int)); //Set the values in array x to zero
    memset(x_der, 0, arraySize * sizeof(int)); //Set the values in array x to zero
    memset(x_sqr, 0, arraySize * sizeof(int)); //Set the values in array x to zero

    memset(yl, 0, 3 * sizeof(int)); //Set the values in array y to zero
    memset(yh, 0, 2 * sizeof(int)); //Set the values in array y to zero



    QRS_params qsr_params; // Instance of the made available through: #include "qsr.h"
    openfile("ECG.txt");   // Pointer to a file object;
    FILE *writeHighPass = fopen("highPassFilter.txt","w");
    FILE *writeDer = fopen("derivativeFilter.txt","w");
    FILE *writeSqr = fopen("squareFilter.txt","w");

    for (int position = 0 ; position < 10000 ; position++) {
        x[position%arraySize] = getNextData();

        x_low[position%arraySize] = lowPassFilter(x, yl, position%arraySize);
        x_high[position%arraySize] = highPassFilter(x_low, yh, position%arraySize);
        x_der[position%arraySize] = derivative(x_high, position%arraySize);
        x_sqr[position%arraySize] = square(x_der,position%arraySize);


        fprintf(writeHighPass,"%d \n", x_high[position%arraySize]);
        fprintf(writeDer,"%d \n", x_der[position%arraySize]);
        fprintf(writeSqr,"%d \n",x_sqr[position%arraySize]);
        peakDetection(&qsr_params); // Perform Peak Detection
    }

    for (int i = 0; i < arraySize; ++i) {
        printf("%d,",x_sqr[i]);
    }
    fclose(writeHighPass);
    return 0;
}
