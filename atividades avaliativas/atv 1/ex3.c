//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdio.h>
#include <stdlib.h>
#define localMaxPallets 4
#define totalLocals 5

//implementação da stack estatica
typedef struct{
    int array[localMaxPallets];
    int stackSize;
    int maxSize;
}stack;

//inicializa as variaveis da stack
stack createStack(){
    stack newStack;
    newStack.maxSize = localMaxPallets;
    newStack.stackSize = 0;
    return newStack;
}

//adiciona um elemento em cima da stack
void stackAppend(stack* stack_, int value){
    if(stack_->stackSize < stack_->maxSize){
        stack_->array[stack_->stackSize] = value;
        stack_->stackSize += 1;
    }
}

//remove o elemento de cima da stack
void stackPop(stack* stack_){
    if(stack_->stackSize > 0){
        // free(stack_->array[stack_->atualSize]); //em C não é possível liberar a memoria de um único elemento de um array, pois o array ocupa a memoria "em conjunto" (este espaço deve permanecer disponível para futuras alocagens, se não ficar disponivel, como o array vai alocar suas variaveis?)
        stack_->stackSize -= 1;
    }
}

//imprime quantidade de pallets dos 5 locais gerenciados
void printPallets(stack* pallets){
    for(int i = 0; i < totalLocals; i++){
        printf("local %d = %d pallet(s)\n", i + 1, pallets[i].stackSize);
    }
}

//adiciona pallet no primeiro local com menos pallets
void addPallet(stack* pallets){
    int localWithLessPallets = -1; //variavel para armazenar o local com menos pallets
    int palletsOfLocalWithLessPallets = localMaxPallets; //variavel para armazenar quantos pallets possui o local com menos pallets
    for(int i = 0; i < totalLocals; i++){ //procura pelo local com menos pallets
        if(palletsOfLocalWithLessPallets > pallets[i].stackSize){
            palletsOfLocalWithLessPallets = pallets[i].stackSize;
            localWithLessPallets = i;
        }
    }
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    if(palletsOfLocalWithLessPallets < localMaxPallets){//se o local não estiver cheio, adiciona um novo pallet
        stackAppend(&pallets[localWithLessPallets], 1);
        printf("foi adicionado um pallet no local %d\n", localWithLessPallets + 1);
    }else{//se o local com menos pallets estiver cheio, não existe mais nenhum local para adicionar pallets
        printf("nenhum espa%co para adicionar um pallet\n", 135);
    }
    printPallets(pallets);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
}

//remove pallet do primeiro local com mais pallets
void removePallet(stack* pallets){
    int localWithMorePallets = -1;//variavel para armazenar o local com mais pallets
    int palletsOfLocalWithMorePallets = 0; //variavel para armazenar quantos pallets possui o local com mais pallets
    for(int i = 0; i < totalLocals; i++){ //procura pelo local com mais pallets
        if(palletsOfLocalWithMorePallets < pallets[i].stackSize){
            palletsOfLocalWithMorePallets = pallets[i].stackSize;
            localWithMorePallets = i;
        }
    }
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    if(palletsOfLocalWithMorePallets > 0){//se o local não estiver vazio, remove um pallet
        stackPop(&pallets[localWithMorePallets]);
        printf("foi removido um pallet no local %d\n", localWithMorePallets + 1);

    }else{//se o local com mais pallets estiver vazio, não existe mais nenhum local para remover pallets
        printf("nenhum pallet para ser removido\n");
    }
    printPallets(pallets);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
}

int main(void){
    stack pallets[totalLocals]; //stack que armazena stacks
    for(int i = 0; i < totalLocals; i++){
        pallets[i] = createStack(); //atribui stacks aos array dos pallets
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
    }while(input != 3); //enquanto a opção não for sair, não sai
    return 1;
}