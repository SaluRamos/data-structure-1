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
    newQueue.array = (int*) malloc(sizeof(int)*1);
    newQueue.maxSize = 10;
    newQueue.queueSize = 0;
    return newQueue;
}

void queueAppend(queue *queue_, int newValue){
    if(queue_->queueSize + 1 == queue_->maxSize){
        printf("realocando fila para %d\n", floor(pow(queue_->maxSize, 2)));
        queue_->array = (int*) realloc(queue_->array, floor(pow(queue_->maxSize, 2)));
    }
    queue_->array[queue_->queueSize] = newValue;
    queue_->queueSize += 1;
}

void queuePop(queue *queue_){
    if(queue_->queueSize - 1 <= floor(queue_->maxSize/4)){
        queue_->array = (int*) realloc(queue_->array, floor(queue_->maxSize/2));
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
    queueAppend(&aQueue, 10);
    queueAppend(&aQueue, 20);
    queueAppend(&aQueue, 30);
    printQueueArray(&aQueue);
    queuePop(&aQueue);
    queueAppend(&aQueue, 40);
    printQueueArray(&aQueue);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    queueAppend(&aQueue, 40);
    printQueueArray(&aQueue);
    return 1;
}