#include "filters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

    int l = 0; //Incrementation of array index
    int h = 0; //Incrementation of array index
    int d = 0; //Incrementation of array index
    int s = 0; //Incrementation of array index
    int w = 0; //Incrementation of array index


int* lowPassFilter(int *x) {
    const int N_x = 13; //Length of x array
    const int N_y = 3; //Length of y array

    int kx = l % 13; //Loop index number in array x
    int ky = l % 3; //Loop index number in array y

    x[(N_x+(0-kx))%N_x] = input_data; //append input value to x[12]

    //Low Pass equation
    int x_low = 2*y[(N_y+(1-ky))%N_y]-y[(N_y+(2-ky))%N_y]+(x[(N_x+(0-kx))%N_x]-2*x[(N_x+(6-kx))%N_x]+x[(N_x+(12-kx))%N_x])/32;
    y[(N_y+(0-ky))%N_y] = x_low; //append x_low value to y[2]

    l += 1; //Increment i by 1

    return x_low;
}

int* highPassFilter(int *x){
    const int N_x = 33; //Length of x array
    const int N_y = 2; //Length of y array

    int kx = h % 33; //Loop index number in array x
    int ky = h % 2; //Loop index number in array y

    x[(N_x+(0-kx))%N_x] = x_low; //append x_low value to x[32]

    //High Pass equation
    int x_high = y[(N_y+(1-ky))%N_y]-(lowPassFilter(x)[(N_x+(0-kx))%N_x]/32)+lowPassFilter(x)[(N_x+(16-kx))%N_x]-lowPassFilter(x)[(N_x+(17-kx))%N_x]+(lowPassFilter(x)[(N_x+(32-kx))%N_x]/32);
    y[(N_y+(0-ky))%N_y] = x_high;

    h += 1; //Increment i by 1

    return x_high;
}

int* derivative(int *x){
    const int N_x = 5; //Length of x array

    int kx = d % 5; //Loop index number in array x

    x[(N_x+(0-kx))%N_x] = x_high; //append high_x value to x[4]

    //Derivative equation
    int x_der = (2*highPassFilter(x)[(N_x+(0-kx))%N_x]+highPassFilter(x)[(N_x+(1-kx))%N_x]-highPassFilter(x)[(N_x+(3-kx))%N_x]-2*highPassFilter(x)[(N_x+(4-kx))%N_x])/8;
    d += 1; //Increment i by 1

    return x_der;
}

int* square(int *x){

    const int N_x = 10; //Length of x array

    int kx = s % 10; //Loop index number in array x

    derivative(x)[(N_x+(0-kx))%N_x] = x_der; //append high_x value to x[4]

    //Derivative equation
    int x_sqr = pow(derivative(x)[(N_x+(0-kx))%N_x],2);
    s += 1; //Increment i by 1

    return x_sqr;
}

int moveWin(int *x,int position){
    int sum = 0;
    int N_x = 30; //Length of x array

    int kx; //Loop index number in array x

    for(int i = 0; i < N_x; i++){
        kx = w % N_x;

        sum += square(x)[((N_x+(0-kx))%N_x)]; //append sqr_x value to x[4]
        w++; //inncrement w by 1
    }

    int mwi = sum/N_x;
    return mwi;
}