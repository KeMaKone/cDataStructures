// Tekijä Konsta Keski-Mattinen 2021.09.29

/*
funktio lyhimmät_polut(taulukko d)
   for i = 1 to n 
      for j = 1 to n 
         m(i,j) = d(i,j)
   for k = 1 to n 
      for i = 1 to n 
         for j = 1 to n 
            m(i,j) = min{m(i,j), m(i,k)+m(k,j)}
   return m
*/
#include <stdlib.h>
#include <stdio.h>
#define n 6

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void shortestPaths(int table[n][n]){
    for(int k=0; k < n; k++){
        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){
                table[i][j] = MIN(table[i][j], table[i][k]+table[k][j]);
            }
        }
    }
    return;
}

void print2DArray(int table[n][n]){
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            printf("%i ", table[i][j]);
        }
        printf("\n");
    }
    return;
}

int main(void){
    int table[n][n];
    //Lyödään alkuarvot
    for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){
                table[i][j] = 9999; //Käytännässä inf
            }
        } 
    table[0][1] = 4; //ab
    table[0][4] = 5; //ae
    table[1][2] = 6; //bc
    table[1][5] = 1; //bf
    table[2][3] = 1; //cd
    table[2][5] = 2; //cf
    table[3][4] = 2; //de
    table[3][5] = 4; //df
    //Lisäksi myös vastakkaiseen suuntaan
    table[1][0] = 4; //ba
    table[4][0] = 5; //ea
    table[2][1] = 6; //cb
    table[5][1] = 1; //fb
    table[3][2] = 1; //dc
    table[5][2] = 2; //fc
    table[4][3] = 2; //ed
    table[5][3] = 4; //fd

    //tulostetaan käsitelty lista
    printf("Alusttu lista:\n");
    print2DArray(table);
    shortestPaths(table);
    //tulostetaan lista algoritmin jälkeen
    printf("Käsitelty lista:\n");
    print2DArray(table);

    return 0;
}