#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char type; //Directed=1, NotDirected=2, Weighted=3, Alone=4
} EdgeType;

typedef struct{
    char from; //define origem da aresta
    char to; //define destino da aresta
    EdgeType type; //define se é direcionado ou não
    int weight; //define peso da aresta
} Edge;

typedef struct{
    EdgeType *edge; //lista de arestas/vértices
    int amountEdges; //elementos contidos em edge[]
} Graph;



//declaração das funções
void raiseError(char description[], int statusCode);
EdgeType createEdgeType(char type);
char* edgeTypeString(EdgeType *edgeType);
Edge createEdge(char from, char to, char type, int weight);
void printEdge(Edge *edge);



void raiseError(char description[], int statusCode){
    //Documentation
    //-1 = edgeType does not exist.
    printf("ERROR: '%s', STATUS CODE: %d", description, statusCode);
    exit(statusCode);
}



EdgeType createEdgeType(char type){
    EdgeType newEdgeType;
    newEdgeType.type = type;
    edgeTypeString(&newEdgeType);
    return newEdgeType;
}



char* edgeTypeString(EdgeType *edgeType){
    switch(edgeType->type){
        case 1:
            return "Directed";
            break;
        case 2:
            return "NotDirected";
            break;
        case 3:
            return "Weighted";
            break;
        case 4:
            return "Alone";
            break;
        default:
            raiseError("edgeType does not exist.", -1);
            return "";
            break;
    }
}



Edge createEdge(char from, char to, char type, int weight){
    Edge newEdge;
    newEdge.from = from;
    newEdge.to = to;
    newEdge.type = createEdgeType(type);
    newEdge.weight = weight;
    // printf("tamanho = %lld\n", sizeof(newEdge));
    return newEdge;
}



void printEdge(Edge *edge){
    printf("%c, %c, %s, %d\n", edge->from, edge->to, edgeTypeString(&edge->type), edge->weight);
}



int main(void){

    Edge newEdge = createEdge('A', 'B', 3, 0);
    printEdge(&newEdge);

}