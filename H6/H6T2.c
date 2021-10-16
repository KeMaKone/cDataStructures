#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* ptrLeftChild;
    struct Node* ptrRightChild; 
} Node;


Node* getNextUnfilledNode(Node* ptrStart, int value){
    Node* ptrReturn = NULL;
    if(ptrStart->ptrRightChild == NULL){
        ptrReturn = ptrStart;
    } else if (ptrStart->value < value){
        ptrReturn = getNextUnfilledNode(ptrStart->ptrRightChild, value);
    } else {
        ptrReturn = getNextUnfilledNode(ptrStart->ptrLeftChild, value);
    }
    return ptrReturn;
}

Node* addNode(Node* ptrStart, int newNodeValue){
    Node* ptrNew;
    if((ptrNew = (Node*) malloc(sizeof(Node)))==NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(33333);
    }

    ptrNew->value=newNodeValue;
    ptrNew->ptrLeftChild = NULL;
    ptrNew->ptrRightChild = NULL;
    
    if(ptrStart == NULL){
        ptrStart = ptrNew;
    } else {
        Node* ptrUnfilled = getNextUnfilledNode(ptrStart, newNodeValue);
        if(ptrUnfilled->ptrLeftChild == NULL){
            ptrUnfilled->ptrLeftChild = ptrNew;
        } else {
            if(ptrUnfilled->ptrLeftChild->value > newNodeValue){
                ptrUnfilled->ptrRightChild = ptrUnfilled->ptrLeftChild;
                ptrUnfilled->ptrLeftChild = ptrNew;
            } else {
                ptrUnfilled->ptrRightChild = ptrNew;
            }
        }
    }
    return ptrStart;
}

Node* freeBinTree(Node* ptrStart){
    if(ptrStart->ptrLeftChild != NULL){
        freeBinTree(ptrStart->ptrLeftChild);
    }
    if(ptrStart->ptrRightChild != NULL){
        freeBinTree(ptrStart->ptrRightChild);
    }
    free(ptrStart);
    return NULL;
}

void printBinTreeBuilder(Node* ptrStart){
    if(ptrStart->ptrLeftChild != NULL){
        printBinTreeBuilder(ptrStart->ptrLeftChild);
    }
    
    printf("%d,",ptrStart->value);

    if(ptrStart->ptrRightChild != NULL){
        printBinTreeBuilder(ptrStart->ptrRightChild);
    }
}

void printBinTree(Node* ptrStart){
    printBinTreeBuilder(ptrStart);
    printf("\n");
}

Node* findValue(Node* ptrStart, int value){
    Node* ptrReturn = NULL;

    if(ptrStart == NULL){
        return NULL;
    }

    if(ptrStart->value == value){
        ptrReturn = ptrStart;
    } else if (ptrStart->value < value){
        ptrReturn = findValue(ptrStart->ptrRightChild, value);
    } else {
        ptrReturn = findValue(ptrStart->ptrLeftChild, value);
    }
    return ptrReturn;
}

int main(){
    int targetValue = 16;
    Node* binTreePtr = NULL;

    printf("Ensimmäinen puu syötteellä: 25, 23, 28, 16, 44, 24, 27\n");
    binTreePtr = addNode(binTreePtr, 25);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 23);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 28);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 16);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 44);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 24);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 27);
    printBinTree(binTreePtr);
    printf("Pointer of value %d is %p\n", targetValue, findValue(binTreePtr, targetValue));
    binTreePtr = freeBinTree(binTreePtr);
    
    printf("\nToinen puu syötteellä: 44, 28, 27, 23, 16, 24, 25\n");
    binTreePtr = addNode(binTreePtr, 44);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 28);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 27);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 23);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 16);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 24);
    printBinTree(binTreePtr);
    addNode(binTreePtr, 25);
    printBinTree(binTreePtr);
    printf("Pointer of value %d is %p\n", targetValue, findValue(binTreePtr, targetValue));
    binTreePtr = freeBinTree(binTreePtr);
    
    return 0;
}

/*
FILOSOFINEN ONGELMA
    Epäsopivassa avainten järjestyksessä voidaan hyvin joutua tilanteeseen,
    jossa yksi polku on paljon pidempi kuin muut.
*/