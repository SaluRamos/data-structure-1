//dynamic queue

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random.c"

typedef struct{
    int *array;
    int maxSize;
    int atualSize;
} queue;

//inicializa as variaveis da queue
queue createQueue(){
    queue newQueue;
    newQueue.maxSize = 8; //valor inicial deve ser um resultado de f(x) = pow(2, x), com x pertencente aos inteiros
    newQueue.array = (int*) malloc(sizeof(int)*newQueue.maxSize);
    newQueue.atualSize = 0;
    return newQueue;
}

//adiciona um elemento em cima da queue
void queueAppend(queue *queue_, int newValue){
    if(queue_->atualSize + 1 == queue_->maxSize){
        queue_->array = (int*) realloc(queue_->array, pow(queue_->maxSize, 2)*sizeof(int));
        queue_->maxSize += queue_->maxSize;
    }
    queue_->array[queue_->atualSize] = newValue;
    queue_->atualSize += 1;
}

//remove o elemento de baixo da queue
void queuePop(queue *queue_){
    if(queue_->atualSize - 1 <= floor(queue_->maxSize/4)){
        queue_->array = (int*) realloc(queue_->array, floor(queue_->maxSize/2)*sizeof(int));
        queue_->maxSize = floor(queue_->maxSize/2);
    }
    if(queue_->atualSize > 0){
        for(int i = 0; i < queue_->atualSize - 1; i++){
            queue_->array[i] = queue_->array[i + 1];
        }
        queue_->atualSize -= 1;
    }
}

//imprime informações da queue
void printQueueArray(queue *queue_){
    printf("-----------------------\n");
    printf("tamanho maximo = %d\n", queue_->maxSize);
    printf("tamanho atual = %d\n", queue_->atualSize);
    if(queue_->atualSize == 0){
        printf("esta fila nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < queue_->atualSize; i++){
            printf("elemento %d = %d\n", i + 1, queue_->array[i]);
        }
    }
    printf("-----------------------\n");
}

int main(void){
    queue aQueue = createQueue();
    printQueueArray(&aQueue);
    for(int i = 0; i < 10; i++){
        queueAppend(&aQueue, randInt(1, 100));
    }
    printQueueArray(&aQueue);
    for(int i = 0; i < 8; i++){
        queuePop(&aQueue);
    }
    printQueueArray(&aQueue);
    return 1;
}