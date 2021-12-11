//Tekijä Konsta Keski-Mattinen 2021.12.08

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
void tulosta_puu(puuosoitin, int);
void hae_solmu(puuosoitin, int, int);
void generateList(int [], int);
void addListToTree(puuosoitin *, int *, int [], int);
void searchListFromTree(puuosoitin *, int [], int);
void timeSearch(puuosoitin *, int [], int);
int treeSize(puuosoitin);
void readFromFile(int []);
void findFile(char *);
int menu();

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
    printf("Number %d is already in the tree\n", luku);
  }
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

void tulosta_puu(puuosoitin solmu, int depth){
	if(!solmu) return;

	tulosta_puu(solmu->oikea, depth +1);
	printf("\n");
	for(int i = 0; i<depth; i++){
		printf(" ");
	}
	printf("%d\n", solmu->luku);
	printf("\n");

	tulosta_puu(solmu->vasen, depth + 1); 
}


//Haku ilmoittaa löytyykö ja mistä vai ei
void hae_solmu(puuosoitin emo, int haettuArvo, int printBool){
	if(!emo){
		if(printBool) printf("Unfortunately the number %d wasn't in this tree\n", haettuArvo);
	} else if(emo->luku == haettuArvo){
		if(printBool) printf("The number %d was in the tree\n", haettuArvo);
	}else if(emo->luku < haettuArvo){
		hae_solmu(emo->oikea, haettuArvo, printBool);
	} else if(emo->luku > haettuArvo){
		hae_solmu(emo->vasen, haettuArvo, printBool);
	} 
	return;
}

void generateList(int array[], int len){
    for(int i=0; i<len; i++){
        array[i] = rand();
    }
}

void addListToTree(puuosoitin *puu, int *etp, int array[], int printBool){
	for(int i = 0; array[i] != 0; i++){
    	lisaa_solmu(puu, array[i], etp);
		if(printBool){
			printf("\n");
			printf("Tree starts\n");
			tulosta_puu(*puu, 0); // Tulostus: Puun rakentuminen vaihe vaiheelta
			printf("Tree ends\n");
			printf("\n");
		}
	}
}

void searchListFromTree(puuosoitin *puu, int array[], int printBool){
	for(int i = 0; array[i] != 0; i++) hae_solmu(*puu, array[i], printBool);
}

void timeSearch(puuosoitin *emo, int searchArray[], int len){
	clock_t begin = clock();
	searchListFromTree(emo, searchArray, 0);
	clock_t end = clock();
	clock_t time_spent = (end - begin);
	int size = treeSize(*emo);
    printf("Processor time spent searching %d keys from the current tree of size %d was %ld\n", len, size, time_spent);
}

int treeSize(puuosoitin emo){
	if(!emo) return 0;
	return 1+treeSize(emo->vasen)+treeSize(emo->oikea);
}

void readFromFile(int array[]){
	char fileName[32];
	FILE *pFile;
	int i = 0;

	findFile(fileName);

	if((pFile = fopen(fileName, "r")) == NULL){
    perror("Error while reading file");
    return;
  }
	printf("Reading file... (MAX 100000)\n");
	while(fscanf(pFile, "%d", &array[i]) != EOF){
		i++;
	}
	array[i] = 0;
	array[i+1] ='\0';
	fclose(pFile);
}

void findFile(char *target){
    fflush(stdin); //tyhjennetään stdin
    printf("Give filename: ");
    scanf("%s", target);
}

int menu(){
	char searchAns = '0';

	fflush(stdin); //tyhjennetään stdin
	printf("Add tree from file Y/n? ");
	scanf("%c", &searchAns);

	if(searchAns == 'Y' || searchAns == 'y') return 1;
	return 0;
}


int main(){
	puuosoitin puu = NULL;
	int etp = 0;
	int menuChoise = menu();
	int luvut0[] = {2, 3, 4, 6, 8, 10, 12, 14, 30, 28, 0}, haettavat0[] = {6, 1, 10, 16, 0}, 
		luvut1[] = {26, 24, 22, 20, 18, 16, 0},            haettavat1[] = {10, 26, 32, 0};
	
	if(menuChoise){
		int array[100000];
		for(int i =0; i<100000;i++) array[i]=0;
		readFromFile(array);
		addListToTree(&puu, &etp, array, 1);
		tulosta_puu(puu, 0);
	} else {
		//Lisätään luvut 2, 4, 6, 8, 10, 12, 14, 30, 28
		addListToTree(&puu, &etp, luvut0, 1);
		printf("\n");
	}
	//Löytyykö puusta avaimet 6, 1, 10 ja 16?
	searchListFromTree(&puu, haettavat0, 1);
	printf("\n");

	//Lisätään luvut 26, 24, 22, 20, 18, 16
	addListToTree(&puu, &etp, luvut1, 1);
	printf("\n");

	//Löytyykö puusta avaimet 6, 1, 10 ja 16?
	searchListFromTree(&puu, haettavat1, 1);
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
	timeSearch(&puu, search100000, 100000);
	printf("\n");

	return 0;
}