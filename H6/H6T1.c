#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* ptrNext; 
} Node;

Node* addNode(Node* ptrStart, int newNodeValue){
    Node* ptrNew;
    if((ptrNew = (Node*) malloc(sizeof(Node)))==NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }

    ptrNew->value=newNodeValue;
    ptrNew->ptrNext=NULL;
    
    if(ptrStart == NULL){
        ptrStart = ptrNew;
    } else {
        for(Node* ptrll = ptrStart;; ptrll=ptrll->ptrNext){
            if(ptrll->ptrNext == NULL){
                ptrll->ptrNext = ptrNew;
                break;
            }
        }
    }
    return ptrStart;
}

Node* removeNode(Node* ptrStart, int indexRemoved){
    Node* ptrll = ptrStart;

    if(indexRemoved == 0){
        free(ptrStart);
        return NULL;
    }

    //Siirretään ptr poistettavaa edeltävään
    for(int i=0; ptrll != NULL; ptrll=ptrll->ptrNext){
        i++;    //Jos seuraava on poistettava;
        if(i==indexRemoved){
            Node* ptrRemoved = ptrll->ptrNext;
            ptrll->ptrNext = ptrRemoved->ptrNext;
            free(ptrRemoved);
            break;
        }
    }

    return ptrStart;
}  

int listSize(Node* ptrll){
    int i = 0;
    while(ptrll->ptrNext != NULL){
        i++;
        ptrll = ptrll->ptrNext; 
    }
    return i;
}

void printList(Node* ptrll){
    for(; ptrll != NULL; ptrll=ptrll->ptrNext){
        printf("%d ", ptrll->value);
    }
    printf("\n");
}

void freeLL(Node* ptrll){
    Node* tmp;
    for(; ptrll != NULL;){
        tmp = ptrll;
        ptrll = ptrll->ptrNext;
        free(tmp);
    }
}

int main(){
    Node* linkedListPtr = NULL;
    linkedListPtr = addNode(linkedListPtr, 2);
    printList(linkedListPtr);
    addNode(linkedListPtr, 4);
    printList(linkedListPtr);
    addNode(linkedListPtr, 6);
    printList(linkedListPtr);
    addNode(linkedListPtr, 3);
    printList(linkedListPtr);
    addNode(linkedListPtr, 7);
    printList(linkedListPtr);
    addNode(linkedListPtr, 1);
    printList(linkedListPtr);
    addNode(linkedListPtr, 9);
    printList(linkedListPtr);
    removeNode(linkedListPtr, 6);
    printList(linkedListPtr);
    removeNode(linkedListPtr, listSize(linkedListPtr)-1);
    printList(linkedListPtr);
    freeLL(linkedListPtr);
    return 0;
}