#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct{
    int *value;
    int atualSize;
    int maxSize;
} sortedList;

//inicia uma lista
sortedList startSortedList(){
    sortedList newSortedList;
    newSortedList.maxSize = 8;
    newSortedList.atualSize = 0;
    newSortedList.value = (int *) malloc(sizeof(int)*newSortedList.maxSize);
    return newSortedList;
}

//printa a lista ordenada
void printSortedList(sortedList *list){
    printf("lista: ");
    for(int i = 0; i < list->atualSize; i++){
        printf("%d ", list->value[i]);
    }
    printf("\n\n");
}

//retorna o index do elemento procurado
int binarySearchNearestFloorIndexSortedList(int array[], int arraySize, int target, int start, int end){
    if(end == -1){
        end = arraySize - 1; //define o final da lista
    }
    if(start >= end){
        return start; //elemento não esta na lista
    }
    int middle = floor((start + end)/2);
    if(target == array[middle]){
        return middle; //elemento foi encontrado
    }
    else if(target < array[middle]){
        return binarySearchNearestFloorIndexSortedList(array, arraySize, target, start, middle -1); //elemento esta na porção esquerda
    }
    return binarySearchNearestFloorIndexSortedList(array, arraySize, target, middle + 1, end); //elemento está na porção direita
}

void appendSortedList(sortedList *list, int newValue){
    int nearestIndex = 0;
    if(list->atualSize > 0){
        nearestIndex = binarySearchNearestFloorIndexSortedList(list->value, list->atualSize, newValue, 0, -1); //procura index a adicionar elemento
        printf("index a adicionar = %d\n", nearestIndex);
        if(list->atualSize + 1 > list->maxSize){ //realoca memoria
            list->value = (int *) realloc(list->value, pow(list->maxSize, 2)*sizeof(int));
            list->maxSize += list->maxSize;
        }
        for(int i = list->atualSize; i > nearestIndex; i--){ //joga elementos a frente
            list->value[i] = list->value[i - 1];
        }
    }
    list->value[nearestIndex] = newValue; //incrementa o valor desejado no index encontrado
    list->atualSize += 1;
    printf("adicionou elemento\n");
    printSortedList(list);
}

int main(void){
    sortedList newList;
    newList = startSortedList();

    appendSortedList(&newList, 10);
    appendSortedList(&newList, 5);
    appendSortedList(&newList, 13);
    appendSortedList(&newList, 2);
}