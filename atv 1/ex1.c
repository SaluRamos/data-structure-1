//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define baseStackSize 10

//stack estatica

typedef struct{
    int array[baseStackSize];
    int stackSize;
    int maxSize;
}stack;

void stackAppend(stack* stack_, int value){
    if(stack_->stackSize < stack_->maxSize){
        stack_->array[stack_->stackSize] = value;
        stack_->stackSize += 1;
    }
}

void stackPop(stack* stack_){
    if(stack_->stackSize > 0){
        free(stack_->array[stack_->stackSize]);
        stack_->stackSize -= 1;
    }
}

stack createStack(){
    stack newStack;
    newStack.maxSize = baseStackSize;
    newStack.stackSize = 0;
    return newStack;
}

//software

int main(int argc, char *argv[]){
    stack pares = createStack();
    stack impares = createStack();
    int input = 0;
    FILE *fInput;
    if(argc > 0){
        fInput = fopen(strcat(argv[1], ".txt"), "w+");
    }else{
        fInput = fopen("input.txt", "w+");
    }
    FILE *fPares;
    if(argc > 1){
        fPares = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        fPares = fopen("pares.txt", "w+");
    }
    FILE *fImpares;
    if(argc > 2){
        fImpares = fopen(strcat(argv[3], ".txt"), "w+");
    }else{
        fImpares = fopen("impares.txt", "w+");
    }
    for(int i = 0; i < 10; i++){
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &input);
        if(input % 2 == 0){
            stackAppend(&pares, input);
        }else{
            stackAppend(&impares, input);
        }
        fprintf(fInput, "%d\n", input);
    }
    fprintf(fInput, "\n");
    for(int i = 0; i < pares.stackSize; i++){
        fprintf(fInput, "%d\n", pares.array[i]);
        fprintf(fPares, "%d\n", pares.array[i]);
    }
    fprintf(fInput, "\n");
    for(int i = 0; i < impares.stackSize; i++){
        fprintf(fInput, "%d\n", impares.array[i]);
        fprintf(fImpares, "%d\n", impares.array[i]);
    }
    fclose(fInput);
    fclose(fPares);
    fclose(fImpares);
    return 1;
}