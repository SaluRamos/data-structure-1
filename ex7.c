//dynamic queue

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct{
    int *array;
    int maxSize;
    int queueSize;
} queue;

queue createQueue(){
    queue newQueue;
    newQueue.maxSize = 10;
    newQueue.array = (int*) malloc(sizeof(int)*newQueue.maxSize);
    newQueue.queueSize = 0;
    return newQueue;
}

void queueAppend(queue *queue_, int newValue){
    if(queue_->queueSize + 1 == queue_->maxSize){
        queue_->array = (int*) realloc(queue_->array, pow(queue_->maxSize, 2)*sizeof(int));
        queue_->maxSize += queue_->maxSize;
    }
    queue_->array[queue_->queueSize] = newValue;
    queue_->queueSize += 1;
}

void queuePop(queue *queue_){
    if(queue_->queueSize - 1 <= floor(queue_->maxSize/4)){
        queue_->array = (int*) realloc(queue_->array, floor(queue_->maxSize/2)*sizeof(int));
        queue_->maxSize -= floor(queue_->maxSize/2);
    }
    if(queue_->queueSize > 0){
        for(int i = 0; i < queue_->queueSize - 1; i++){
            queue_->array[i] = queue_->array[i + 1];
        }
        queue_->queueSize -= 1;
    }
}

void printQueueArray(queue *queue_){
    printf("-----------------------\n");
    printf("tamanho maximo = %d\n", queue_->maxSize);
    printf("tamanho atual = %d\n", queue_->queueSize);
    if(queue_->queueSize == 0){
        printf("esta fila nao possui nenhum elemento\n");
    }else{
        for(int i = 0; i < queue_->queueSize; i++){
            printf("elemento %d = %d\n", i + 1, queue_->array[i]);
        }
    }
    printf("-----------------------\n");
}

int main(void){
    queue aQueue = createQueue();
    printQueueArray(&aQueue);
    for(int i = 0; i < 3; i++){
        queueAppend(&aQueue, 40);
    }
    printQueueArray(&aQueue);
    for(int i = 0; i < 10; i++){
        queueAppend(&aQueue, 40);
    }
    printQueueArray(&aQueue);
    for(int i = 0; i < 8; i++){
        queuePop(&aQueue);
    }
    printQueueArray(&aQueue);
    return 1;
}