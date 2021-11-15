#include <stdio.h>
#include <stdlib.h>

#define E 7
#define V 5


typedef struct Edge {
    int weight;
    int src;
    int dest;
} Edge;

typedef struct Edgelist{
    Edge edge;
    struct Edgelist* pNext;
} Edgelist;


Edgelist* addEdge(Edgelist* el, int src, int dest, int weight){
    Edgelist* newNode = (Edgelist*) malloc(sizeof(Edgelist));
    newNode->edge.src = src;
    newNode->edge.dest= dest;
    newNode->edge.weight=weight;
    newNode->pNext=NULL;

    if(el == NULL){
        return newNode;
    }

    Edgelist* tmp = el;
    //Iterate to the last
    while(tmp->pNext != NULL){
        tmp = tmp->pNext;
    }
    tmp->pNext = newNode; 
    return el;
}


void* freeEdgelist(Edgelist* el){
    Edgelist* pTemp;
    while(el != NULL){
        pTemp = el;
        el = el->pNext;
        free(pTemp);
    }
    return NULL;
}

void swapEdge(Edgelist* edge0, Edgelist* edge1){
    Edge tmp;
    tmp.src = edge0->edge.src;
    tmp.dest = edge0->edge.dest;
    tmp.weight = edge0->edge.weight;

    edge0->edge.src = edge1->edge.src;
    edge0->edge.dest = edge1->edge.dest;
    edge0->edge.weight = edge1->edge.weight;

    edge1->edge.src = tmp.src;
    edge1->edge.dest = tmp.dest;
    edge1->edge.weight = tmp.weight;

}


void sortEdgelist(Edgelist* el){
    Edgelist* tmp0 = el;
    Edgelist* tmp1 = tmp0->pNext;
    while(tmp0->pNext != NULL){
        while(tmp1 != NULL){
            if(tmp0->edge.weight > tmp1->edge.weight){
                swapEdge(tmp0, tmp1);
            }
            tmp1 = tmp1->pNext;
        }
        tmp0 = tmp0->pNext;
        tmp1 = tmp0->pNext;
    }
}

int hasNewVertex(Edgelist* el, Edge edge){
    int edgeSrcInList=0;
    int edgeDestInList=0;
    Edgelist* tmp = el;
    while(tmp != NULL){
        if(edge.src == tmp->edge.src || edge.src == tmp->edge.dest){
            edgeSrcInList =1;
        }
        if(edge.dest == tmp->edge.dest || edge.dest == tmp->edge.src){
            edgeDestInList =1;
        }
        tmp = tmp->pNext;
    }
    return !(edgeSrcInList && edgeDestInList);
}

void printEdgelist(Edgelist* el){
    int sum =0;

    Edgelist* tmp = el;
    while(tmp != NULL){
        sum += tmp->edge.weight;
        printf("S:%d D:%d, W:%d\n", tmp->edge.src, tmp->edge.dest, tmp->edge.weight);
        tmp = tmp->pNext;
    }
    printf("SUM: %d\n", sum);
}

/* 
algorithm Kruskal(G) is
    F:= ∅
    for each v ∈ G.V do
        MAKE-SET(v)
    for each (u, v) in G.E ordered by weight(u, v), increasing do
        if FIND-SET(u) ≠ FIND-SET(v) then
            F:= F ∪ {(u, v)} ∪ {(v, u)}
            UNION(FIND-SET(u), FIND-SET(v))
    return F
*/
Edgelist* kruskal(Edgelist* el){
    sortEdgelist(el);
    Edgelist edgelistlist[E];
    Edgelist* f = NULL;
    Edgelist* iter = el;
    while(iter != NULL){
        if(hasNewVertex(f, iter->edge)){
            f = addEdge(f, iter->edge.src, iter->edge.dest, iter->edge.weight);
        }
        iter = iter->pNext;
    }
    return f;
}

int main(){
    Edgelist* el = NULL;
    el = addEdge(el, 1, 2, 4);
    addEdge(el, 1, 3, 5);
    addEdge(el, 2, 3, 6);
    addEdge(el, 2, 4, 9);
    addEdge(el, 3, 4, 6);
    addEdge(el, 3, 5,12);
    addEdge(el, 4, 5, 5);
    printf("Kokoverkko\n");
    printEdgelist(el);
    
    Edgelist* f = kruskal(el);
    printf("Kruskalin minimipuu\n");
    printEdgelist(f);

    freeEdgelist(el);
    freeEdgelist(f);
    return(0);
}