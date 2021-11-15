#include <stdio.h>
#include <stdlib.h>

#define E 18
#define V 10

#define inf 999


typedef struct Node {
    int id;
    int distance;
    struct Node* pNext;
} Node;

Node* addNode(Node* pOld, int id, int distance){
    Node* pNew;
    if((pNew = (Node*) malloc(sizeof(Node)))==NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }

    pNew->id=id;
    pNew->distance=distance;
    pNew->pNext=pOld;

    return pNew;
}

Node* removeNode(Node* pRemoved){
    Node* tmp = pRemoved->pNext;
    free(pRemoved);
    if(tmp == NULL){
        return NULL;
    }
    return tmp;
}

Node* freeLL(Node* pll){
    Node* tmp;
    for(; pll != NULL;){
        tmp = pll;
        pll = pll->pNext;
        free(tmp);
    }
    return NULL;
}


void printList(Node* pll){
    for(; pll != NULL; pll=pll->pNext){
        printf("%d ", pll->distance);
    }
    printf("\n");
}


/*
keko.push((0,alku))
while not keko.empty()
    solmu = keko.pop().tunnus
    if kasitelty[solmu]
        continue
    kasitelty[solmu] = true
    for kaari in verkko[solmu]
        nyky = etaisyys[kaari.loppu]
        uusi = etaisyys[solmu]+kaari.paino
        if uusi < nyky
            etaisyys[kaari.loppu] = uusi
            keko.push((uusi,kaari.loppu))
*/
Node* dijkstran(Node* graph[]){
    int handeleds[V] = {0,0,0,0,0,0,0,0,0,0};
    int distances[V] = {0,25,6,inf,inf,inf,inf,inf,inf,inf};
    Node* stack; 
    Node* tmp;

    stack = addNode(NULL, 1, 0);
    while(stack != NULL){
        int nodeId = stack->id-1; 
        stack = removeNode(stack);
        printf("stack id %d\n", nodeId);
        if(handeleds[nodeId]){
            printf("skip");
            continue;
        }
        handeleds[nodeId] = 1;
        tmp = graph[nodeId];
        while(tmp != NULL){
            int currentDistance = distances[tmp->id-1];
            int newDistance = distances[nodeId]+tmp->distance;
            if(newDistance<currentDistance){
                distances[tmp->id-1] = newDistance;
                stack = addNode(stack, tmp->id, newDistance);
            }
        }

    }
    return stack;
}

int main(){
    Node* n1 = addNode(NULL,2,25);
    addNode(n1,3,6);
    Node* n2 = addNode(NULL,4,10);
    addNode(n2,5,3);
    Node* n3 = addNode(NULL,4,7);
    addNode(n3,6,25);
    Node* n4 = addNode(NULL,5,12);
    addNode(n4,6,15);
    addNode(n4,7,4);
    addNode(n4,8,15);
    addNode(n4,9,20);
    Node* n5 = addNode(NULL,8,2);
    Node* n6 = addNode(NULL,9,25);
    Node* n7 = addNode(NULL,8,8);
    addNode(n7,9,13);
    addNode(n7,10,15);
    Node* n8 = addNode(NULL,10,5);
    Node* n9 = addNode(NULL,10,1);
    Node* n10 = addNode(NULL,10,0);

    Node* graph[V] = {n1,n2,n3,n4,n5,n6,n7,n8,n9,n10};

    Node* head = dijkstran(graph);
    printList(head);
    freeLL(head);
    return 0;
}