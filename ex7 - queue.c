#include <stdlib.h>
#include <stdio.h>
#define N 8

typedef struct{
    int array[N];
} queue;

void appendQueue(queue *queue_, int new_value){
    int next_elem = 0;
    printf("oi 1 = %d\n", queue_->array[0]);
    printf("oi 2 = %d\n", queue_->array[1]);
    for(int i = 0; i < N; i++){
        next_elem = queue_->array[i];
        printf("next_elemento = %d\n", next_elem);
        if(i == 0){
            queue_->array[0] = new_value;
        }
        queue_->array[i + 1] = next_elem;
    }
}

int popQueue(queue queue_){
    return 0;
}

void printQueueArray(queue *queue_){
    printf("-----------------------\n");
    for(int i = 0; i < N; i++){
        printf("%d = %d\n", i, queue_->array[i]);
    }
    printf("-----------------------\n");
}

int main(void){
    queue test;
    test.array[0] = 1;
    test.array[1] = 2;
    test.array[2] = 3;
    test.array[3] = 4;
    test.array[4] = 5;
    test.array[5] = 6;
    test.array[6] = 7;
    test.array[7] = 8;
    printQueueArray(&test);
    appendQueue(&test, 10);
    printQueueArray(&test);
    return 1;
}