#include <stdlib.h>
#include <stdio.h>

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

int main(void){
    stack myStack = createStack(10);
    printStack(&myStack);
    stackAppend(&myStack, 10);
    stackAppend(&myStack, 20);
    printStack(&myStack);
    stackPop(&myStack);
    printStack(&myStack);
    return 1;
}