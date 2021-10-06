// Tekijä Konsta Keski-Mattinen 2021.10.06
#include <stdio.h>


#define n 5
#define true 1 
#define false 0

int rowCounter = 1;

void arrayPrinter(int arr[]){
    printf("%d: ", rowCounter++);
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* PSEUDO
procedure haku(k)
    if k == n
        print(luvut)
    else
        for i = 1 to n
            if not mukana[i]
                mukana[i] = true
                luvut[k] = i
                haku(k+1)
                mukana[i] = false
*/

void search(int k, int luvut[], int mukana[]){
    if(k==n){
        arrayPrinter(luvut);
    } else {
        for(int i = 0; i < n; i++){
            if(mukana[i] == false){
                mukana[i] = true;
                luvut[k] = i + 1;
                search(k+1, luvut, mukana);
                mukana[i] = false;
            }
        }
    }
}

int main(){
    int luvut[n] = {0,0,0,0,0};
    int mukana[n] = {0,0,0,0,0};
    search(0, luvut, mukana);
    return 0;
}