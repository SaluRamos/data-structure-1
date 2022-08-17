#include <stdio.h>
#include <stdlib.h>

//17 de agosto de 2022

int main(void){
    int number_of_vectors = 0;
    int *vector = NULL;
    int sum = 0;
    printf("Informe o tamanho do vetor: ");
    scanf("%d", &number_of_vectors);
    fflush(stdin);
    vector = malloc(number_of_vectors*sizeof(int));
    if(vector == NULL){
        printf("\nErro de alocacao do vetor");
        return 1;
    }
    for(int i = 0; i < number_of_vectors; i++){
        printf("Digite o elemento do vetor %d: ", i);
        scanf("%d", &vector[i]);
        fflush(stdin);
        sum += vector[i];
    }
    printf("Soma total = %d", sum);
    free(vector);
    return 0;
}