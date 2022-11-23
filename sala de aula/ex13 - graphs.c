#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <string.h>



typedef struct{
    int **edges;
    int dimension;
    int amountEdges;
} Graph;



void raiseError(char description[], int statusCode){
    printf("ERROR %d: '%s'", statusCode, description);
    exit(statusCode);
}



Graph createGraph(int dimension){
    Graph newGraph;
    newGraph.edges = (int **) malloc(dimension*sizeof(int *));
    for(int i = 0; i < dimension; i++){
        newGraph.edges[i] = (int *) malloc(dimension*sizeof(int));
    }
    newGraph.dimension = dimension;
    newGraph.amountEdges = 0;
    return newGraph;

}



void addEdge(Graph *g, int vertice_from, int vertice_to, int edge_weight){
    if(vertice_from > g->dimension || vertice_from < 0 || vertice_to > g->dimension || vertice_to < 0){
        char errorBuffer[100];
        sprintf(errorBuffer, "trying to add an edge out of the matrix space, dimension %d, edge %d->%d", g->dimension, vertice_from, vertice_to);
        raiseError(errorBuffer, 1);
    }
    g->amountEdges += 1;
}



void freeGraph(Graph *g){
    free(g->edges);
}



int main(void){

    Graph newGraph = createGraph(2);
    addEdge(&newGraph, 0, 3, 1);
    freeGraph(&newGraph);
}