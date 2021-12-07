#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

/*
*Procedure piiperneljä returns reaali
*k=0
*for i=1 to M do
*  x = satunnainen(0,1)
*  y = satunnainen(0,1)
*  if x^2 + y^2 < 1 then k = k + 1
*return k/M
*/
double piper4(int M){
    int k,i = 0;
    double x,y;
    for(;i<M;i++){
        x = (double)rand() / (double)RAND_MAX;
        y = (double)rand() / (double)RAND_MAX; 
        if(pow(x,2) + pow(y,2) < 1) k++;
    }
    return (double)k/(double)M;
}

int main(){
    int input;
    float output;
    float error;
    srand(time(0));

    for(int i=0; i<6; i++){
        input = rand();
        output = piper4(input);
        error = fabs(PI-4*output);
        printf("Testataan arvolla %d, vastaus: %f, ero oikeasta: %f\n", input, output, error);
    }
}