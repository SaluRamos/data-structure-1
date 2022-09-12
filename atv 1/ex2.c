//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdlib.h>
#include <stdio.h>

//pilha dinamica

typedef struct{
    int *array;
    int stackSize;
    int maxSize;
}stack;

stack createStack(int stackLength){
    stack newStack;
    newStack.array = malloc(sizeof(int)*stackLength);
    newStack.maxSize = stackLength;
    newStack.stackSize = 0;
    return newStack;
}

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

void printStack(stack* stack_){
    printf("---------------------------------\n");
    if(stack_->stackSize == 0){
        printf("esta stack nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < stack_->stackSize; i++){
            printf("elemento %d = %d\n", i + 1, stack_->array[i]);
        }
    }
    printf("---------------------------------\n");
}

//exercicio

int fibonacci(int n){
    if(n < 2){
        return n;
    }
    else{
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(void){
    int nInput = 0;
    while(1){
        printf("Digite um numero entre 5 e 20: ");
        scanf("%d", &nInput);
        if(nInput >= 5 && nInput <= 20){
            break;
        }
        printf("Voce n%co digitou um numero v%clido!\n", 198, 160);
    }
    stack fibonacciStack = createStack(nInput);
    for(int i = nInput - 1; i > 0; i--){
        stackAppend(&fibonacciStack, fibonacci(i));
    }
    stackAppend(&fibonacciStack, 0);
    printStack(&fibonacciStack);
    return 1;
}