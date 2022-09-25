#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#define maxQueueSize 10
#define lineLenght 100

//estrutura de casa
typedef struct{
    int id;
    char *owner;
    char *streat;
    int number;
} house;

//implementação das stacks
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
    // printf("tamanho maximo = %d\n", stack_->maxSize);
    // printf("tamanho atual = %d\n", stack_->atualSize);
    if(stack_->atualSize == 0){
        printf("esta stack nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < stack_->atualSize; i++){
            printf("elemento %d = %d\n", i + 1, stack_->array[i]);
        }
    }
    printf("---------------------------------\n");
}

//implementação da queue dinamica
typedef struct{
    house *array;
    int maxSize;
    int atualSize;
} queue;

//inicializa as variaveis da queue
queue createQueue(){
    queue newQueue;
    newQueue.maxSize = maxQueueSize;
    newQueue.array = (house *) malloc(sizeof(house)*newQueue.maxSize);
    newQueue.atualSize = 0;
    return newQueue;
}

//remove o elemento de baixo da queue
void queuePop(queue *queue_){
    if(queue_->atualSize > 0){
        for(int i = 0; i < queue_->atualSize - 1; i++){
            queue_->array[i] = queue_->array[i + 1];
        }
        queue_->atualSize -= 1;
    }
}

//adiciona um elemento em cima da queue
void queueAppend(queue *queue_, house newHouse){
    if(queue_->atualSize + 1 > queue_->maxSize){
        queuePop(queue_);
    }
    queue_->array[queue_->atualSize] = newHouse;
    queue_->atualSize += 1;
}

//imprime informações da queue
void printQueueArray(queue *queue_){
    printf("-----------------------\n");
    // printf("tamanho maximo = %d\n", queue_->maxSize);
    // printf("tamanho atual = %d\n", queue_->atualSize);
    if(queue_->atualSize == 0){
        printf("esta fila nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < queue_->atualSize; i++){
            house newHouse = queue_->array[i];
            printf("local %d: %d,'%s','%s',%d\n", i + 1, newHouse.id, newHouse.owner, newHouse.streat, newHouse.number);
        }
    }
    printf("-----------------------\n");
}

int len(char *string_){
    int size = 0;
    while(1){
        if(string_[size] != '\0'){
            size += 1;
        }
        else{
            break;
        }
    }
    return size;
}

char* replace(char *orig, char *rep, char *with){
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;
    if(!orig || !rep){
        return NULL;
    }
    len_rep = strlen(rep);
    if(len_rep == 0){
        return NULL;
    }
    if(!with){
        with = "";
    }
    len_with = strlen(with);
    ins = orig;
    for(count = 0; (tmp = strstr(ins, rep)); ++count){
        ins = tmp + len_rep;
    }
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if(!result){
        return NULL;
    }
    while(count--){
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}

house getNewHouse(FILE *f){
    char ch;
    char *line = (char *) malloc(sizeof(char)*lineLenght);
    for(int i = 0; i < lineLenght; i++){
        ch = fgetc(f);
        if(ch == '\n' || ch == EOF){
            line[i] = '\0';
            break;
        }else if(ch != '\n'){
            line[i] = ch;
        }
    }
    house newHouse;
    newHouse.id = -1;
    line = replace(line, "{", "");
    line = replace(line, "}", "");
    int totalChar = -1;
    for(int i = 0; i < 4; i++){
        char *content = (char *) malloc(sizeof(char)*lineLenght);
        int partialChar = 0;
        while(1){
            totalChar += 1;
            if(line[totalChar] != ';' && line[totalChar] != '\0'){
                content[partialChar] = line[totalChar];
                partialChar += 1;
            }else{
                break;
            }
        }
        content[partialChar] = '\0';
        switch(i){
            case 0:
                if(atoi(content) != 0){
                    newHouse.id = atoi(content);
                }
                break;
            case 1:
                newHouse.owner = content;
                break;
            case 2:
                newHouse.streat = content;
                break;
            case 3:
                newHouse.number = atoi(content);
                break;
        }
    }
    if(newHouse.id != -1){
        printf("novo local adicionado a fila: %d,'%s','%s',%d\n", newHouse.id, newHouse.owner, newHouse.streat, newHouse.number);
    }else{
        printf("nao existe novo local para ser adicionado a fila\n");
    }
    return newHouse;
}

int main(int argc, char *argv[]){
    FILE *fHouses;
    if(argc > 1){ //inicializa arquivo 1
        fHouses = fopen(strcat(argv[1], ".txt"), "r");
    }else{
        fHouses = fopen("visita.txt", "r");
    }
    if(NULL == fHouses){ //verifica se arquivo abriu corretamente
        printf("ARQUIVO NAO EXISTE");
        return -1;
    }
    queue houses = createQueue();
    //agente começa a visitar
    while(houses.atualSize < 10){
        //faz leitura do arquivo para carregar proxima casa
        house newHouse = getNewHouse(fHouses);
        if(newHouse.id == -1){
            break;
        }
        queueAppend(&houses, newHouse);
    }
    stack visited = createStack();
    stack notVisited = createStack();
    while(visited.atualSize < maxQueueSize && houses.atualSize > 0){
        char *input = (char *) malloc(sizeof(char)*lineLenght);
        printf("\n");
        printf("locais visitados = %d\n", visited.atualSize);
        printf("locais nao visitados = %d\n", notVisited.atualSize);
        printf("locais na fila de visita = %d\n", houses.atualSize);
        printf("A visita ao novo local foi concretizada (s/n)? ");
        gets(input);
        if(strcmp(input, "s") == 0 || strcmp(input, "S") == 0){
            stackAppend(&visited, houses.array[0].id);
        }else if(strcmp(input, "n") == 0 || strcmp(input, "N") == 0){
            stackAppend(&notVisited, houses.array[0].id);
            house newHouse = getNewHouse(fHouses);
            if(newHouse.id != -1){
                queueAppend(&houses, newHouse);
            }
        }else{
            printf("input incorreto!\n");
        }
        queuePop(&houses);
    }
    if(visited.atualSize < maxQueueSize){
        printf("\nA META DE 10 LOCAIS NAO FOI ALCANCADA\n");
    }else{
        printf("\nA META DE 10 LOCAIS FOI ALCANCADA\n");
    }
    printf("\nLISTA DE LOCAIS VISITADOS (POR ID):\n");
    printStack(&visited);
    printf("LISTA DE LOCAIS NAO VISITADOS (POR ID):\n");
    printStack(&notVisited);
    fclose(fHouses);
    return 1;
}