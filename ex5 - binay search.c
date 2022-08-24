#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//22 de agosto de 2022

int * createIntArray(int arraySize, int maxValue, int minValue){
    int* array;
    array = (int*) malloc(arraySize*sizeof(int));
    srand((unsigned)time(NULL));
    for(int i = 0; i < arraySize; i++){
        array[i] = (rand() % maxValue) + minValue;
        printf("elemento %d = %d\n", i + 1, array[i]);
    }
    return array;
}

int * reverseArray(){
    return 0;
}

def quick_sort(list_to_sort, start = 0, end = None):
    if end == None:
        end = len(list_to_sort) - 1
    if start < end:
        p = partition(list_to_sort, start, end)
        quick_sort(list_to_sort = list_to_sort, start = start, end = (p - 1))
        quick_sort(list_to_sort = list_to_sort, start = (p + 1), end = end)
    return list_to_sort

def partition(list_to_sort, start, end):
    pivot = list_to_sort[end]
    i = start
    for j in range(start, end):
        if list_to_sort[j] <= pivot:
            list_to_sort[j], list_to_sort[i] = list_to_sort[i], list_to_sort[j]
            i += 1
    list_to_sort[i], list_to_sort[end] = list_to_sort[end], list_to_sort[i]
    return i

//retorna o index do elemento procurado
int binarySearch(int array[], int arraySize, int target, int start, int end){
    if(end == -1){
        end = arraySize - 1; //define o final da lista
    }
    if(start > end){
        return -1; //elemento não esta na lista
    }
    int middle = floor((start + end)/2);
    if(target == array[middle]){
        return middle; //elemento foi encontrado
    }
    else if(target < array[middle]){
        return binarySearch(array, target, start, middle -1); //elemento esta na porção esquerda
    }
    return binarySearch(array, target, middle + 1, end); //elemento está na porção direita
}

int main(void){
    int arraySize = 0, minValue = 0, maxValue = 0;
    printf("Digite o tamanho do vetor aleatorio: ");
    scanf("%d", &arraySize);
    printf("Digite o valor maximo de cada elemento: ");
    scanf("%d", &maxValue);
    printf("Digite o valor minimo de cada elemento: ");
    scanf("%d", &minValue);
    if(minValue >= maxValue){
        printf("valor minimo maior que valor maximo!");
        return -1;
    }
    int* vector = createIntArray(arraySize, maxValue, minValue); //precisa estar ordenada
    // int target = 18;
    // int index = binarySearch(vector, target, 0, -1);
    // printf("index do elemento procurado = %d\n", index);
}