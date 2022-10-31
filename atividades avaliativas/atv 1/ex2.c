//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//implementação da stack dinamica
typedef struct{
    int *array;
    int maxSize;
    int atualSize;
} stack;

//inicia os valores de uma stack
stack createStack(){
    stack newStack;
    newStack.maxSize = 8; //valor inicial deve ser um resultado de f(x) = pow(2, x), com x pertencente aos inteiros
    newStack.array = (int*) malloc(sizeof(int)*newStack.maxSize);
    newStack.atualSize = 0;
    return newStack;
}

//adiciona um elemento de cima da stack
void stackAppend(stack* stack_, int newValue){
    if(stack_->atualSize + 1 == stack_->maxSize){
        //pesquisei e descobri que uma boa maneira de usar o realloc de maneira eficiente é sempre dobrando o espaço conforme se utiliza
        stack_->array = (int*) realloc(stack_->array, pow(stack_->maxSize, 2)*sizeof(int));
        stack_->maxSize += stack_->maxSize;
    }
    stack_->array[stack_->atualSize] = newValue;
    stack_->atualSize += 1;
}

//remove o elemento de cima da stack
void stackPop(stack* stack_){
    if(stack_->atualSize - 1 <= floor(stack_->maxSize/4)){
        //se a quantidade de elementos cair para 1/4 do espaço disponivel, faz realocagem para liberar memoria
        stack_->array = (int*) realloc(stack_->array, floor(stack_->maxSize/2)*sizeof(int));
        stack_->maxSize = floor(stack_->maxSize/2);
    }
    if(stack_->atualSize > 0){
        // free(stack_->array[stack_->atualSize]); //a memoria é liberada apenas quando ocorre a realocagem, em C não é possível liberar a memoria de um único elemento de um array, pois o array ocupa a memoria "em conjunto" (este espaço deve permanecer disponível para futuras alocagens, se não ficar disponivel, como o array vai alocar suas variaveis?)
        stack_->atualSize -= 1;
    }
}

//imprime informações de uma stack
void printStack(stack* stack_){
    printf("---------------------------------\n");
    printf("tamanho maximo = %d\n", stack_->maxSize);
    printf("tamanho atual = %d\n", stack_->atualSize);
    if(stack_->atualSize == 0){
        printf("esta stack nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < stack_->atualSize; i++){ //ittera entre os elementos da stack
            printf("elemento %d = %d\n", i + 1, stack_->array[i]);
        }
    }
    printf("---------------------------------\n");
}

//retorna o resultado de N fatorial (n!)
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
    while(1){ //loop eterno até a quebra
        printf("Digite um numero entre 5 e 20: ");
        scanf("%d", &nInput);
        if(nInput >= 5 && nInput <= 20){
            break; //quebra do loop pois preencheu as condições
        }
        printf("Voce n%co digitou um numero v%clido!\n", 198, 160);
    }
    stack fibonacciStack = createStack();
    for(int i = nInput - 1; i >= 0; i--){//adiciona todos os valores de fibonnaci a stack, na ordem requisitada (de cima para baixo)
        stackAppend(&fibonacciStack, fibonacci(i));
    }
    printStack(&fibonacciStack);
    return 1;
}