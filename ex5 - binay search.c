#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//22 de agosto de 2022

//retorna o tamanho de um array
int len(int array[]){
    int total_array_bytes = 0;
    for(int i = 0; i < 5; i++){
        total_array_bytes += sizeof(array[i]);
    }
    return total_array_bytes / sizeof(array[0]);
}

//retorna o index do elemento procurado
int binary_search(int array[], int target, int start, int end = -1){
    if(end == -1){
        end = len(array) - 1; //define o final da lista
    }
    if(start > end){
        return -1; //elemento não esta na lista
    }
    int middle = floor((start + end)/2);
    if(target == array[middle]){
        return middle; //elemento foi encontrado
    }
    else if(target < array[middle]){
        return binary_search(array, target, start, middle -1); //elemento esta na porção esquerda
    }
    return binary_search(array, target, middle + 1, end); //elemento está na porção direita
}

int main(void){
    int vector[5] = {12, 29, 31, 42, 53}; //precisa estar ordenada
    int target = 18;
    int index = binary_search(vector, target, 0, -1);
    printf("index do elemento procurado = %d\n", index);
}