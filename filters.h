#ifndef FILTERS_H
#define FILTERS_H


// Feel free to change return statement and arguments
int lowPassFilter(int *x,int *y, int position);
int highPassFilter(int *x_low, int *yh, int position);
<<<<<<< HEAD
int derivative(int x_high, int *x);
int square(int x_der, int *x);
int moveWin(int *x_sqr, int*x);
=======
int derivative(int *x_high, int position);
int square(int *x_der, int position);
int moveWin(int *x_sqr, int position);
>>>>>>> b8968e71a93b8c614d4afbbaf644d70eca4ab46f
// Implement additional filters
 
#endif // FILTERS_H