#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxFColumns 60
#define maxFLines 10

//implementação da queue dinamica
typedef struct{
    char **array;
    int maxSize;
    int atualSize;
} queue;

//inicializa as variaveis da queue
queue createQueue(){
    queue newQueue;
    newQueue.maxSize = maxFLines;
    newQueue.array = (char **) malloc(sizeof(char*)*newQueue.maxSize);
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
void queueAppend(queue *queue_, char newValue[]){
    if(queue_->atualSize + 1 > queue_->maxSize){
        queuePop(queue_);
    }
    int stringLength = (int) strlen(newValue);
    char *copyValue;
    copyValue = (char *) malloc(sizeof(char)*stringLength);
    strcpy(copyValue, newValue);
    queue_->array[queue_->atualSize] = copyValue;
    queue_->atualSize += 1;
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
            printf("elemento %d = '%s'\n", i + 1, queue_->array[i]);
        }
    }
    printf("-----------------------\n");
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
    char ch;
    char line[maxFColumns];
    queue houses = createQueue();
    while(1){
        for(int i = 0; i < maxFColumns; i++){
            ch = fgetc(fHouses);
            if(ch == '\n' || ch == EOF){
                line[i] = '\0';
                break;
            }else if(ch != '\n'){
                line[i] = ch;
            }
        }
        // printf("%s %d\n", line, (int) strlen(line));
        queueAppend(&houses, line);
        printQueueArray(&houses);
        if(ch == EOF){
            break;
        }
    }
    fclose(fHouses);
    return 1;
}