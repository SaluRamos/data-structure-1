#include <stdio.h>
#include <stdlib.h>

//24 de agosto de 2022

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

int * reverseArray(int* array, int arraySize){
    int* tempArray;
    tempArray = (int *) malloc(arraySize*sizeof(int));
    for(int i = 0; i < arraySize; i++){
        tempArray[i] = array[arraySize - i - 1];
    }
    return tempArray;
}

int partition(int* arrayToSort, int start, int end){
    int pivot = arrayToSort[end];
    int i = start;
    for(int j = start; j < end; j++){
        if(arrayToSort[j] <= pivot){
            int temp = arrayToSort[j];
            arrayToSort[j] = arrayToSort[i];
            arrayToSort[i] = temp;
            i += 1;
        }
    }
    int temp = arrayToSort[i];
    arrayToSort[i] = arrayToSort[end];
    arrayToSort[end] = temp;
    return i;
}

int * quickSort(int* arrayToSort, int arraySize, int start, int end){
    if(end == -1){
        end = arraySize - 1;
    }
    if(start < end){
        int p = partition(arrayToSort, start, end);
        quickSort(arrayToSort, arraySize, start, p - 1);
        quickSort(arrayToSort, arraySize, p + 1, end);
    }
    return arrayToSort;
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
    // vector = quickSort(vector, arraySize, 0, -1);
    vector = reverseArray(vector, arraySize);
    printf("---LISTA ORDENADA---\n");
    for(int i = 0; i < arraySize; i++){
        printf("elemento %d = %d\n", i + 1, vector[i]);
    }
}