#include <stdio.h>
#include <stdlib.h>
#define localMaxPallets 4
#define totalLocals 5

//stack dinamica

typedef struct{
    int array[localMaxPallets];
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
    newStack.maxSize = localMaxPallets;
    newStack.stackSize = 0;
    return newStack;
}

//pallets (para adicionar ou remover deve automaticamente selecionar o local)

void printPallets(stack* pallets){
    for(int i = 0; i < totalLocals; i++){
        printf("local %d = %d pallet(s)\n", i + 1, pallets[i].stackSize);
    }
}

void addPallet(stack* pallets){
    int localWithLessPallets = -1;
    int palletsOfLocalWithLessPallets = localMaxPallets;
    for(int i = 0; i < totalLocals; i++){
        if(palletsOfLocalWithLessPallets > pallets[i].stackSize){
            palletsOfLocalWithLessPallets = pallets[i].stackSize;
            localWithLessPallets = i;
        }
    }
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    if(palletsOfLocalWithLessPallets < localMaxPallets){
        stackAppend(&pallets[localWithLessPallets], 1);
        printf("foi adicionado um pallet no local %d\n", localWithLessPallets + 1);
    }else{
        printf("nenhum espa%co para adicionar um pallet\n", 135);
    }
    printPallets(pallets);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
}

void removePallet(stack* pallets){
    int localWithMorePallets = -1;
    int palletsOfLocalWithMorePallets = 0;
    for(int i = 0; i < totalLocals; i++){
        if(palletsOfLocalWithMorePallets < pallets[i].stackSize){
            palletsOfLocalWithMorePallets = pallets[i].stackSize;
            localWithMorePallets = i;
        }
    }
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    if(palletsOfLocalWithMorePallets > 0){
        stackPop(&pallets[localWithMorePallets]);
        printf("foi removido um pallet no local %d\n", localWithMorePallets + 1);

    }else{
        printf("nenhum pallet para ser removido\n");
    }
    printPallets(pallets);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
}

int main(void){
    stack pallets[totalLocals];
    for(int i = 0; i < totalLocals; i++){
        pallets[i] = createStack();
    }
    int input = 0;
    do{
        printf("1 - adicionar pallet\n2 - remover pallet\n3 - sair\nsua op%c%co: ", 135, 198);
        scanf("%d", &input);
        printf("\n");
        switch(input){
        case 1:
            addPallet(pallets);
            break;
        case 2:
            removePallet(pallets);
            break;
        case 3:
            printf("at%c a pr%cxima!", 130, 162);
            break;
        default:
            printf("input incorreto!\n\n");
            break;
        }
    }while(input != 3);
    return 1;
}