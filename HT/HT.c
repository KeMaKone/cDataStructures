//Tekijä Konsta Keski-Mattinen ZZZZ.YY.XX

/*
* Lukee tiedostosta avaimet
* Lisää luetut avaimet tasapainotettuun binääriseen hakupuuhun (linkitetty lista)
* Tulostaa syntyneen puurakenteen
* Hakee avaimen mukaisen tiedon puusta (hakee avaimen)
* Lisää yksittäisiä avaimia puuhun
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

typedef struct puusolmu_t {
  int luku;
  short tila; /* tasapainoilmaisin */
  struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;

void lisaa_solmu(puuosoitin *, int, int *);
void oikea_kierto(puuosoitin *, int *);
void vasen_kierto(puuosoitin *, int *);
void tulosta_puu(puuosoitin);
void hae_solmu(puuosoitin, int);
void poista_solmu(puuosoitin *, int, int *);
//Helperfunctions for main
void generateList(int [], int);
void addListToTree(puuosoitin *, int *, int []);
void searchListFromTree(puuosoitin *, int []);
void timeSearch(puuosoitin *, int [], int);

/* NOTES
 * puuosoitin *emo = pointer to rootnode
 * int *etp = pointer to unbalance integer
*/

void lisaa_solmu(puuosoitin *emo, int luku, int *etp){
  if(!(*emo)){
    *etp = 1;
    if(!(*emo = (puuosoitin)malloc(sizeof(puusolmu)))){
      perror("malloc");
      exit(1);
    }
    (*emo)->vasen = (*emo)->oikea = NULL;
    (*emo)->tila = 0;
    (*emo)->luku = luku;
  } else if(luku < (*emo)->luku){
    lisaa_solmu(&(*emo)->vasen, luku, etp);
    if(*etp){
      switch((*emo)->tila){
        case -1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = 1;
          break;
        case 1:
          vasen_kierto(emo, etp);
      }
    }
  } else if(luku > (*emo)->luku){
    lisaa_solmu(&(*emo)->oikea, luku, etp);
    if(*etp){
      switch((*emo)->tila){
        case 1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = -1;
           break;
        case -1:
          oikea_kierto(emo, etp);
      }
    }
  } else{
    *etp = 0;
    printf("Luku %d on jo puussa\n", luku);
  }
}

void poista_solmu(puuosoitin *emo, int luku, int *etp){

}

void vasen_kierto(puuosoitin *emo, int *etp){
  puuosoitin lapsi, lapsenlapsi;

  lapsi = (*emo)->vasen;
  if(lapsi->tila == 1){ /* LL-kierto */
    (*emo)->vasen = lapsi->oikea;
    lapsi->oikea = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else{ /* LR-kierto */
    lapsenlapsi = lapsi->oikea;
    lapsi->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = lapsi;
    (*emo)->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = *emo;
    switch(lapsenlapsi->tila){
      case 1:
        (*emo)->tila = -1;
        lapsi->tila = 0;
        break;
      case 0:
        (*emo)->tila = lapsi->tila = 0;
        break;
      case -1:
        (*emo)->tila = 0;
        lapsi->tila = 1;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}

void oikea_kierto(puuosoitin *emo, int *etp){
    puuosoitin lapsi, lapsenlapsi;

    lapsi = (*emo)->oikea;
    if(lapsi->tila == -1){ /* RR-kierto */
        (*emo)->oikea = lapsi->vasen;
        lapsi->vasen = *emo;
        (*emo)->tila = 0;
        (*emo) = lapsi;
    } else{ /* RL-kierto */
        lapsenlapsi = lapsi->vasen;
        lapsi->vasen = lapsenlapsi->oikea;
        lapsenlapsi->oikea = lapsi;
        (*emo)->oikea = lapsenlapsi->vasen;
        lapsenlapsi->vasen = *emo;
        switch(lapsenlapsi->tila){
        case 1:
            (*emo)->tila = -1;
            lapsi->tila = 0;
            break;
        case 0:
            (*emo)->tila = lapsi->tila = 0;
            break;
        case -1:
            (*emo)->tila = 0;
            lapsi->tila = 1;
        }
        *emo = lapsenlapsi;
    }
    (*emo)->tila = 0;
    *etp = 0;
}


/* Tulostus
* puun tulostus sivuttain.s
*/
void tulosta_puu(puuosoitin solmu){
  if(!solmu) return;
  tulosta_puu(solmu->vasen);
  printf("%d,%d ", solmu->luku, solmu->tila);
  tulosta_puu(solmu->oikea);
}


//Haku ilmoittaa löytyykö ja mistä vai ei
void hae_solmu(puuosoitin emo, int haettuArvo){
  if(emo->luku < haettuArvo){
    if((void*)emo->oikea == NULL){
      printf("Valitettavasti lukua %d ei tästä puusta löytynyt\n", haettuArvo);
      return;
    }
    hae_solmu(emo->oikea, haettuArvo);
  }else if(emo->luku > haettuArvo){
    if((void*) emo->vasen == NULL){
      printf("Valitettavasti lukua %d ei tästä puusta löytynyt\n", haettuArvo);
      return;
    }
    hae_solmu(emo->vasen, haettuArvo);
  } 
  printf("Haettu arvo %d löytyi puusta\n", haettuArvo);
  return;
}


//helper functions for main()
void generateList(int array[], int len){
    for(int i=0; i<len; i++){
        array[i] = rand();
    }
}

void addListToTree(puuosoitin *puu, int *etp, int array[]){
	for(int i = 0; array[i] != 0; i++){
      lisaa_solmu(puu, array[i], etp);
      tulosta_puu(*puu); // Tulostus: Puun rakentuminen vaihe vaiheelta
      printf("\n");
    }
}

void searchListFromTree(puuosoitin *puu, int array[]){
	for(int i = 0; array[i] != 0; i++){
      hae_solmu(*puu, array[i]);
    }
}

void timeSearch(puuosoitin *emo, int searchArray[], int len){
    clock_t begin = clock();
    searchListFromTree(emo, searchArray);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent searching %d keys from the current tree of size 15 was %f", len, time_spent);
}


/* Driver
* 
* Löytyykö puusta avaimet 6, 1, 10 ja 16?
* Löytyykö avaimet 10? ja 26? Entäpä avain 32?
*/
int main(){
    int etp = 0, i, luvut0[] = {2, 3, 4, 6, 8, 10, 12, 14, 30, 28, 0}, haettavat0[] = {6, 1, 10, 16, 0}, 
                  luvut1[] = {26, 24, 22, 20, 18, 16, 0},            haettavat1[] = {10, 26, 32, 0};
    puuosoitin puu = NULL;
  
    //Lisätään luvut 2, 4, 6, 8, 10, 12, 14, 30, 28
    addListToTree(&puu, &etp, luvut0);
    printf("\n");

    //Löytyykö puusta avaimet 6, 1, 10 ja 16?
    searchListFromTree(&puu, haettavat0);
    printf("\n");

    //Lisätään luvut 26, 24, 22, 20, 18, 16
    addListToTree(&puu, &etp, luvut0);
    printf("\n");

    //Löytyykö puusta avaimet 6, 1, 10 ja 16?
    searchListFromTree(&puu, haettavat1);
    printf("\n");

    printf("\n");
    //Testaa ohjelmaasi, kun avaimia on 10, 100, 1000, 10000, 100000 (tai vielä enemmän).
    int search10[10], search100[100], search1000[1000], search10000[10000], search100000[100000];
    generateList(search10, 10);
    generateList(search100, 100);
    generateList(search1000, 1000);
    generateList(search10000, 10000);
    generateList(search100000, 100000);
    timeSearch(&puu, search10, 10);
    timeSearch(&puu, search100, 100);
    timeSearch(&puu, search1000, 1000);
    timeSearch(&puu, search10000, 10000);
    timeSearch(&puu, search100000, 10000);
    printf("\n");
    return 0;
}