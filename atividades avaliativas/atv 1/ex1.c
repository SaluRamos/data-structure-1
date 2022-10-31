//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define baseStackSize 10

//implementação da stack estatica
typedef struct{
    int array[baseStackSize];
    int stackSize;
    int maxSize;
}stack;

//inicializa valores da stack
stack createStack(){
    stack newStack;
    newStack.maxSize = baseStackSize;
    newStack.stackSize = 0;
    return newStack;
}

//adiciona elemento no topo da stack
void stackAppend(stack* stack_, int value){
    if(stack_->stackSize < stack_->maxSize){
        stack_->array[stack_->stackSize] = value;
        stack_->stackSize += 1;
    }
}

//remove elemento do topo da stack
void stackPop(stack* stack_){
    if(stack_->stackSize > 0){
        // free(stack_->array[stack_->atualSize]); //a memoria é liberada apenas quando ocorre a realocagem, em C não é possível liberar a memoria de um único elemento de um array, pois o array ocupa a memoria "em conjunto" (este espaço deve permanecer disponível para futuras alocagens, se não ficar disponivel, como o array vai alocar suas variaveis?)
        stack_->stackSize -= 1;
    }
}

//o primeiro argumento define o nome do arquivo de entrada
//o segundo argumento define o nome do arquivo de numeros pares
//o terceiro argumento define o nome do arquivo de numeros impares
//caso a quantidade de argumentos passados não seja suficiente, nomeia os arquivos com nome padrão
int main(int argc, char *argv[]){
    stack pares = createStack();
    stack impares = createStack();
    int input = 0;
    FILE *fInput; //inicializa arquivo 1
    if(argc > 1){
        fInput = fopen(strcat(argv[1], ".txt"), "w+");
    }else{
        fInput = fopen("input.txt", "w+");
    }
    FILE *fPares; //inicializa arquivo 2
    if(argc > 2){
        fPares = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        fPares = fopen("pares.txt", "w+");
    }
    FILE *fImpares; //inicializa arquivo 3
    if(argc > 3){
        fImpares = fopen(strcat(argv[3], ".txt"), "w+");
    }else{
        fImpares = fopen("impares.txt", "w+");
    }
    for(int i = 0; i < 10; i++){ //pede pelo input do usuario 10 vezes
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &input);
        if(input % 2 == 0){//verifica se o input é par ou impar e adiciona na stack correspondente
            stackAppend(&pares, input);
        }else{
            stackAppend(&impares, input);
        }
        fprintf(fInput, "%d\n", input); //salva no arquivo de entrada/input
    }
    fprintf(fInput, "\n");
    for(int i = 0; i < pares.stackSize; i++){ //escreve no arquivo dos numeros pares
        fprintf(fPares, "%d\n", pares.array[i]);
    }
    fprintf(fInput, "\n");
    for(int i = 0; i < impares.stackSize; i++){ //escreve no arquivo dos numeros impares
        fprintf(fImpares, "%d\n", impares.array[i]);
    }
    //fecha os arquivos
    fclose(fInput);
    fclose(fPares);
    fclose(fImpares);
    return 1;
}