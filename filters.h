#ifndef FILTERS_H
#define FILTERS_H


// Feel free to change return statement and arguments
int* lowPassFilter(int *x);
int* highPassFilter(int *x);
int* derivative(int *x);
int* square(int *x);
int moveWin(int *x, int position);
// Implement additional filters
 
#endif // FILTERS_H