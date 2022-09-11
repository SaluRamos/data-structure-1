#include <stdlib.h>
#include <stdio.h>
#define baseStackSize 10

//stack dinamica

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

int main(int argc, char ** argv){
    stack pares = createStack();
    stack impares = createStack();
    int input = 0;
    FILE *fInput;
    fInput = fopen("input.txt", "w+");
    FILE *fParesInput;
    fParesInput = fopen("pares.txt", "w+");
    FILE *fImparesInput;
    fImparesInput = fopen("impares.txt", "w+");
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
    for(int i = 0; i < pares.stackSize; i++){
        fprintf(fParesInput, "%d\n", pares.array[i]);
    }
    for(int i = 0; i < impares.stackSize; i++){
        fprintf(fImparesInput, "%d\n", impares.array[i]);
    }
    fclose(fInput);
    fclose(fParesInput);
    fclose(fImparesInput);
    return 1;
}