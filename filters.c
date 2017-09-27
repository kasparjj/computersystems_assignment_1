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

    /*printf("xpos: %d \t x: %d\n -12reads/outputs: %d/%d \t -6reads/outputs: %d/%d \t x_low: %d\n",position,x[position],((position-12)+arraySize)%arraySize,x[((position-12)+arraySize)%arraySize],((position-6)+arraySize)%arraySize,x[((position-6)+arraySize)%arraySize],x_low);
    printf("ypos: %d\t y1: %d \t y2: %d\n",ypos%3,y[((ypos-1)+3)%3],y[((ypos-2)+3)%3]);
    */

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

int derivative(int x_high, int *x){
    const int N_x = 5; //Length of x array

    int kx = d % 5; //Loop index number in array x

    x[(N_x+(0-kx))%N_x] = x_high; //append high_x value to x[4]

    //Derivative equation
    int x_der = (2*x[(N_x+(0-kx))%N_x]+x[(N_x+(1-kx))%N_x]-x[(N_x+(3-kx))%N_x]-2*x[(N_x+(4-kx))%N_x])/8;
//    printf("x_der: %4i \t\t\t\t\t x[%i]: %4i \t x[%i]: %4i \t x[%i]: %4i \t x[%i]: %4i\n",
//           x_der,
//           (N_x+(0-kx))%N_x, x[(N_x+(0-kx))%N_x],
//           (N_x+(1-kx))%N_x, x[(N_x+(1-kx))%N_x],
//           (N_x+(3-kx))%N_x, x[(N_x+(3-kx))%N_x],
//           (N_x+(4-kx))%N_x, x[(N_x+(4-kx))%N_x]);

    d += 1; //Increment i by 1

    return x_der;
}

int square(int x_der, int *x){

    const int N_x = 10; //Length of x array

    int kx = s % 10; //Loop index number in array x

    x[(N_x+(0-kx))%N_x] = x_der; //append high_x value to x[4]

    //Derivative equation
    int x_sqr = pow(x[(N_x+(0-kx))%N_x],2);
//    printf("x_sqr: %4i \t\t\t\t\t x[%i]: %4i\n", x_sqr, (N_x+(0-kx))%N_x, x[(N_x+(0-kx))%N_x]);

    s += 1; //Increment i by 1

    return x_sqr;
}

int moveWin(int *x_sqr, int *x){
    int sum = 0;
    int N_x = 30; //Length of x array

    int kx = 0; //Loop index number in array x

    for(int i = 1; i <= N_x; i++){
        sum += x_sqr[((N_x+(0-kx))%N_x)]; //append sqr_x value to x[4]
        kx++;
    }

    int mwi = sum/N_x;


    //Derivative equation
    //int x_mwi = (x[(N_x+(0-kx))%N_x])/N_x;
    //printf("x_mwi: %4i \t\t\t\t\t x[%i]: %4i\n", x_mwi, (N_x+(0-kx))%N_x, x[(N_x+(0-kx))%N_x]);


    return mwi;
}
