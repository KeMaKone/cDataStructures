// Tekijä Konsta Keski-Mattinen 2021.10.06
#include <stdio.h>

#define n 21

int fibonacci(){
    int fiboTable[n];
    
    fiboTable[0] = 1;
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
// Käytetään fibonaccia koska tarkemman tarkastelun jälkeen voi todeta, että on vain kaksi mahdollista siirtymää seuraavaan silmukkaan n-1 ja n-2.
int main(){
    printf("Kysytään mikä on %d:s fibonaccin sarjan luku...\n", n-1);
    printf("\n%d", fibonacci());
    return 0;
}