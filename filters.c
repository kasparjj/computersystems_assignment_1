#include "filters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int l = 0; //Incrementation of array index
    int h = 0; //Incrementation of array index
    int d = 0; //Incrementation of array index
    int s = 0; //Incrementation of array index
    int w = 0; //Incrementation of array index
    int arraySize = 80;
    int N_y = 3;
    int N_x = 13;
    int ypos = 0;
    int yhpos = 0;


int lowPassFilter(int *x, int *y,int position) {

    //Low Pass equation
    int x_low = 2*y[((ypos-1)+3)%3] - y[((ypos-2)+3)%3]+(x[position]-2*(x[((position-6)+arraySize)%arraySize])+x[((position-12)+arraySize)%arraySize])/32;
    y[ypos%3] = x_low; //append x_low value to y[2]
    ypos++; //Increment ypos by 1
    return x_low;
}

int highPassFilter(int *x_low, int *yh, int position){

    //High Pass equation
    int x_high = yh[((yhpos-1)+2)%2]-(x_low[position]/32)+x_low[((position-16)+arraySize)%arraySize]-x_low[((position-17)+arraySize)%arraySize]+((x_low[((position-32)+arraySize)%arraySize])/32);
    yh[yhpos%2] = x_high;
    yhpos++; //Increment yhpos by 1
    return x_high;
}

int derivative(int *x_high, int position){

    //Derivative equation
    return (2*x_high[position]+x_high[((position-1)+arraySize)%arraySize]-x_high[((position-3)+arraySize)%arraySize]-2*x_high[((position-4)+arraySize)%arraySize])/8;


}

int square(int *x_der, int position){
    return pow(x_der[position],2);
}

int moveWin(int *x_sqr, int position){
    int sum = 0;
    for (int i = 0; i < 30; ++i) {
        sum += x_sqr[((position-i)+80)%80];
    }
    return sum/30;
}
