#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//stack dinamica

typedef struct{
    int *array;
    int stackSize;
    int maxSize;
}stack; //o problema dessa estrutura é que não é possível definir o tipo armazenado nos arrays

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


//decimal para binario

char* decimalToBinary(int decimal){
    stack binaryNumber = createStack(ceil(log2(decimal)));
    int restFromDivision = 0;
    while(1){
        restFromDivision = decimal%2; //divide o decimal por 2 e salva o resto da divisão
        decimal = floor(decimal/2); //divide o decimal por 2 e salva o resultado arredondado para baixo
        stackAppend(&binaryNumber, restFromDivision); //adiciona o resto da divisão na pilha
        if(decimal <= 1){ //verifica se o resultado é menor ou igual a 1
            stackAppend(&binaryNumber, decimal); //adiciona o resultado ao final da pilha, concluindo a conversão de decimal para binario
            char *binaryString = malloc(sizeof(char)*(binaryNumber.stackSize + 1)); //faz alocagem da string que vai armazenar o binario
            int j = 0;
            for(int i = binaryNumber.stackSize; i > 0; i--){
                if(binaryNumber.array[i - 1] == 1){
                    binaryString[j] = '1';
                }else{
                    binaryString[j] = '0';
                }
                j += 1;
            }
            binaryString[j] = '\0';
            return binaryString;
        }
    }
}

//main

int main(void){
    int decimalInput = 0;
    do{
        printf("Digite um numero inteiro nao negativo: ");
        scanf("%d", &decimalInput);
    }while(decimalInput < 0);
    printf("o binario de %d %c %s", decimalInput, 130, decimalToBinary(decimalInput));
    return 1;
}