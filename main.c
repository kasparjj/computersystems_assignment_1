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
    int *y = (int *) malloc(3 * sizeof(int)); //Allocate size of array x
    memset(x, 0, arraySize * sizeof(int)); //Set the values in array x to zero
    memset(y, 0, arraySize * sizeof(int)); //Set the values in array y to zero


    int x_low[arraySize];
    int x_high[arraySize];
    int x_der[arraySize];
    int x_sqr[arraySize];
    int x_moveWin;

    QRS_params qsr_params; // Instance of the made available through: #include "qsr.h"
    openfile("ECG.txt");   // Pointer to a file object;
    for (int position = 0 ; position < 5 ; position++) {
        x[position%arraySize] = getNextData();

        for (int i = 0; i < arraySize-13; i++) {
            x_low[i] = lowPassFilter(x, y, position%arraySize);
        }
        for (int i = 0 ; i < arraySize ; i++){
            printf("%d ", x_low[i]);
        }
/*

        //run highPassFilter i times
        for (int i = 0; i < arraySize-(13); i++) {
            x_high[i] = highPassFilter(x_low[i], x, y);
        }

        //run highPassFilter i times
        for (int i = 0; i < arraySize-(13+33); i++) {
            x_der[i] = derivative(x_high[i], x);
        }

        //run Square i times
        for (int i = 0; i < arraySize-(13+33+5); i++) {
            x_sqr[i] = square(x_der[i], x);
        }
*/

        peakDetection(&qsr_params); // Perform Peak Detection
    }
    return 0;
}
