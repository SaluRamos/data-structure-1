#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int *array;
    int maxSize;
    int queueSize;
} queue;

queue createQueue(int queueSize_){
    queue newQueue;
    newQueue.array = malloc(sizeof(int)*queueSize_);
    newQueue.maxSize = queueSize_;
    newQueue.queueSize = 0;
    return newQueue;
}

void queueAppend(queue *queue_, int newValue){
    if(queue_->queueSize < queue_->maxSize){
        queue_->array[queue_->queueSize] = newValue;
        queue_->queueSize += 1;
    }
}

void queuePop(queue *queue_){
    if(queue_->queueSize > 0){
        free(queue_->array[queue_->queueSize]);
        queue_->queueSize -= 1;
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
    queue aQueue = createQueue(10);
    printQueueArray(&aQueue);
    queueAppend(&aQueue, 10);
    queueAppend(&aQueue, 20);
    printQueueArray(&aQueue);
    queuePop(&aQueue);
    return 1;
}