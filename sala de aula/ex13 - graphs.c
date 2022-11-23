#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>



typedef struct{
    int **edges;
    int amountEdges;
} Graph;



//declaração das funções
void raiseError(char description[], int statusCode);



void raiseError(char description[], int statusCode){
    printf("ERROR %d: '%s'", statusCode, description);
    exit(statusCode);
}


Graph createGraph(int amountEdges){
    Graph newGraph;
    newGraph.edges = (int *) malloc(pow(amountEdges, 2)*sizeof(int));
    newGraph.amountEdges = 0;
    return newGraph;

}


int main(void){

    Graph newEdge = createGraph(2);
    printEdge(&newEdge);

}