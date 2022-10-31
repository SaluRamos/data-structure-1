//Salu Conteratto Ramos, RA 2150352
//Saulo Gabriel Gomes De Lira Fernando, RA 2104636

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//implementação da stack dinamica
typedef struct{
    bool *array; //utiliza booleanas para economizar espaço em memoria, visto que cada algarismo de um binario só pode assumir 0 e 1
    int maxSize;
    int atualSize;
} stack;

//inicia os valores de uma stack
stack createStack(){
    stack newStack;
    newStack.maxSize = 8; //valor inicial deve ser um resultado de f(x) = pow(2, x), com x pertencente aos inteiros
    newStack.array = (bool*) malloc(sizeof(bool)*newStack.maxSize);
    newStack.atualSize = 0;
    return newStack;
}

//adiciona um elemento de cima da stack
void stackAppend(stack* stack_, bool newValue){
    if(stack_->atualSize + 1 == stack_->maxSize){
        //pesquisei e descobri que uma boa maneira de usar o realloc de maneira eficiente é sempre dobrando o espaço conforme se utiliza
        stack_->array = (bool*) realloc(stack_->array, pow(stack_->maxSize, 2)*sizeof(bool));
        stack_->maxSize += stack_->maxSize;
    }
    stack_->array[stack_->atualSize] = newValue;
    stack_->atualSize += 1;
}

//remove o elemento de cima da stack
void stackPop(stack* stack_){
    if(stack_->atualSize - 1 <= floor(stack_->maxSize/4)){
        //se a quantidade de elementos cair para 1/4 do espaço disponivel, faz realocagem para liberar memoria
        stack_->array = (bool*) realloc(stack_->array, floor(stack_->maxSize/2)*sizeof(bool));
        stack_->maxSize = floor(stack_->maxSize/2);
    }
    if(stack_->atualSize > 0){
        // free(stack_->array[stack_->atualSize]); //a memoria é liberada apenas quando ocorre a realocagem, em C não é possível liberar a memoria de um único elemento de um array, pois o array ocupa a memoria "em conjunto" (este espaço deve permanecer disponível para futuras alocagens, se não ficar disponivel, como o array vai alocar suas variaveis?)
        stack_->atualSize -= 1;
    }
}

//converte numero inteiro decimal para stack de binario
stack decimalToBinary(int decimal){
    stack binaryNumber = createStack(ceil(log2(decimal)));
    int restFromDivision = 0;
    while(1){
        restFromDivision = decimal%2; //divide o decimal por 2 e salva o resto da divisão
        decimal = floor(decimal/2); //divide o decimal por 2 e salva o resultado arredondado para baixo
        stackAppend(&binaryNumber, (bool) restFromDivision); //adiciona o resto da divisão na pilha
        if(decimal <= 1){ //verifica se o resultado é menor ou igual a 1
            stackAppend(&binaryNumber, (bool) decimal); //adiciona o resultado ao final da pilha, concluindo a conversão de decimal para binario
            return binaryNumber;
        }
    }
}

//esta função converte a stack em formato de string (mais útil)
char* binaryStackToString(stack* stack_){
    char *binaryString = malloc(sizeof(char)*(stack_->atualSize + 1)); //faz alocagem da string que vai armazenar o binario
    int j = 0; //variavel que sobe os elementos da string
    for(int i = stack_->atualSize; i > 0; i--){
        if(stack_->array[i - 1] == true){//verifica se o elemento é 1 ou 0 e adiciona na string
            binaryString[j] = '1';
        }else{
            binaryString[j] = '0';
        }
        j += 1;
    }
    binaryString[j] = '\0'; //adiciona o char que representa fim da string
    return binaryString;
}

int main(void){
    int decimalInput = 0;
    do{
        printf("Digite um numero inteiro nao negativo: ");
        scanf("%d", &decimalInput);
    }while(decimalInput < 0);//loop enquanto o input não for válido (>= 0)
    printf("binario de %d = ", decimalInput);
    stack binaryNumber = decimalToBinary(decimalInput); //inicia a stack já convertendo decimal para binario
    printf("%s", binaryStackToString(&binaryNumber));
    return 1;
}