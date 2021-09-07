#include <stdio.h>

void sortAlgorithm(int array[], int length){
    int acc;
    int j;
    for(int i = 0; i < length - 1; i++){
        j = i - 1;
        while((j>=0) && (array[j] > array[j+1])){
            acc = array[j + 1];
            array[j + 1] = array[j];
            array[j] = acc;
            j--;
        }
    }
    return;
}

int main(void) {
    int array[9];
    
    // syötteen luku
    for (int i = 0; i < 9; i++){
       scanf("%d", &array[i]);
    }

    // toteuta lisäysjärjestäminen tähän (voit halutessasi toteuttaa algoritmin myös erillisenä funktiona).
    sortAlgorithm(array, sizeof(array)/sizeof(array[0]));
    // järjestetyn listan tulostaminen (voit halutessasi muuttaa muuttujien nimiä)
    for (int i = 0; i < 9; i++) {
        printf("%d ", array[i]); 
    }

    return 0;
}

