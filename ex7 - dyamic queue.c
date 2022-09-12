#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int *array;
    int maxSize;
    int queueSize;
} queue;

queue createQueue(){
    queue newQueue;
    newQueue.array = (int*) malloc(sizeof(int)*1);
    newQueue.maxSize = 1;
    newQueue.queueSize = 0;
    return newQueue;
}

void queueAppend(queue *queue_, int newValue){
    if(queue_->queueSize + 1 == queue_->maxSize){
        queue_->array = (int*) realloc(queue_->array, queue_->queueSize + 1);
    }
    queue_->array[queue_->queueSize] = newValue;
    queue_->queueSize += 1;
    queue_->maxSize += 1;
}

void queuePop(queue *queue_){
    if(queue_->queueSize > 0){
        for(int i = 0; i < queue_->queueSize - 1; i++){
            queue_->array[i] = queue_->array[i + 1];
        }
        queue_->array = (int*) realloc(queue_->array, queue_->queueSize - 1);
        queue_->queueSize -= 1;
        queue_->maxSize -= 1;
    }
}

void printQueueArray(queue *queue_){
    printf("-----------------------\n");
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
    printQueueArray(&aQueue);
    return 1;
}