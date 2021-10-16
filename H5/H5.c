// Tekijä Konsta Keski-Mattinen 2021.10.06
#include <stdio.h>

int fibonacci(int n){
    int fiboTable[n];
    
    fiboTable[0] = 0;
    fiboTable[1] = 1;

    for(int i = 2 ; i < n ; i++){
        fiboTable[i] = fiboTable[i-1] + fiboTable[i-2];
    }
    //Tulostetaan fiboTable
    printf("Sarja: ");
    for(int i = 0; i < n; i++){
        printf("%d ", fiboTable[i]);
    }

    return fiboTable[n-1];
}

int main(){
    int n = 10;
    printf("Kysytään mikä on %d:s fibonaccin sarjan luku...\n", n);
    printf("\n%d", fibonacci(n));
    return 0;
}