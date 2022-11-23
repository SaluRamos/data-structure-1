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
    for(int row = 0; row < dimension; row++){
        newGraph.edges[row] = (int *) malloc(dimension*sizeof(int));
    }
    for(int row = 0; row < dimension; row++){
        for(int col = 0; col < dimension; col++){
            newGraph.edges[row][col] = 0;
        }
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
    if(edge_weight == 0){
        edge_weight = 1;
    }
    g->edges[vertice_from][vertice_to] = edge_weight;
    g->amountEdges += 1;
}



void removeEdge(){

}



void printGraphMatrix(Graph *g){
    printf("--------------------------------\n");
    for(int row = 0; row < g->dimension; row++){
        for(int col = 0; col < g->dimension; col++){
            printf(" %d ", g->edges[row][col]);
        }
        printf("\n");
    }
    printf("--------------------------------");
}



void printGraphEdges(Graph *g){
    printf("--------------------------------\n");
    for(int row = 0; row < g->dimension; row++){
        for(int col = 0; col < g->dimension; col++){
            if(g->edges[row][col] != 0){
                printf("(%d) %d ---> %d\n", g->edges[row][col], row, col);
            }
        }
    }
    printf("--------------------------------");
}



void freeGraph(Graph *g){
    free(g->edges);
}



int main(void){

    Graph newGraph = createGraph(2);
    addEdge(&newGraph, 0, 1, 1);
    addEdge(&newGraph, 0, 1, 1);
    printGraphMatrix(&newGraph);
    printGraphEdges(&newGraph);
    freeGraph(&newGraph);
}