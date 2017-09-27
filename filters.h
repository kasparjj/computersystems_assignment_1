#ifndef FILTERS_H
#define FILTERS_H


// Feel free to change return statement and arguments
int lowPassFilter(int *x,int *y, int position);
int highPassFilter(int *x_low, int *yh, int position);
int derivative(int x_high, int *x);
int square(int x_der, int *x);
int moveWin(int *x_sqr, int*x);
// Implement additional filters
 
#endif // FILTERS_H