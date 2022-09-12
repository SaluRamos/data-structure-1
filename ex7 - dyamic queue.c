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
        queue_->array[queue_->queueSize] = newValue;
        queue_->queueSize += 1;
    }
}

void printQueueArray(queue *queue_){
    printf("-----------------------\n");
    for(int i = 0; i < N; i++){
        printf("%d = %d\n", i, queue_->array[i]);
    }
    printf("-----------------------\n");
}

int main(void){
    queue aQueue = createQueue(10);
    printQueueArray(&test);
    appendQueue(&test, 10);
    printQueueArray(&test);
    return 1;
}