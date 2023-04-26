//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#define queueMaxSize 15

typedef struct client{
    char name[61];
    char birthday[11]; //dd/mm/aaaa
    char condition[2]; //N, D ou H
}client;

typedef struct node{
    client data;
    struct node* next;
    struct node* previous;
}node;

typedef struct sortedDoublyLinkedList{
    node* head;
    node* tail;
}sortedDoublyLinkedList;

//cria uma lista
sortedDoublyLinkedList* createSortedDoublyLinkedList() {
    sortedDoublyLinkedList* list = malloc(sizeof(sortedDoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

//adiciona elemento a lista
void addElementToList(sortedDoublyLinkedList* list, client value){
    node* newNode = malloc(sizeof(node));
    newNode->data = value;
    if(list->head == NULL){
        newNode->next = NULL;
        newNode->previous = NULL;
        list->head = newNode;
        list->tail = newNode;
    }else{ //insertion sort
        client cache;
        node* current = list->head;
        while(current->next != NULL){
            if(strcmp(current->data.name,value.name) >= 0){//current igual ou maior
                cache = current->data;
                if(cache.name == NULL){    
                    current->data = value;
                }else{
                    current->data = cache;
                }
            }
            current = current->next;
        }
        if(cache.name != NULL){  
            newNode->data = cache;
        }
        current->next = newNode;  
        list->tail = newNode;
        current->next->previous = current;
    }
}

//imprime uma lista
void printList(sortedDoublyLinkedList* list){
    node* current = list->head;
    printf("----------------------\n");
    while(current != NULL){
        printf("%s, %s, %s\n", current->data.name, current->data.birthday, current->data.condition);
        current = current->next;
    }
    printf("----------------------\n");
}

//abstração para ler próxima linha de um arquivo
char* readFileLine(FILE *f, int lineMaxSize){
    char ch;
    char *line = (char *) malloc(sizeof(char)*lineMaxSize);
    for(int i = 0; i < lineMaxSize; i++){
        ch = fgetc(f);
        if(ch == '\n' || ch == EOF){
            line[i] = '\0';
            break;
        }else if(ch != '\n'){
            line[i] = ch;
        }
    }
    return line;
}












client createClient(char* name, char* birthday, char *condition){
    client data;
    strcpy(data.name, name);
    strcpy(data.birthday, birthday);
    strcpy(data.condition, condition);
    return data;
}


void readRegister(sortedDoublyLinkedList* list){
    FILE *registersFile;
    registersFile = fopen("clientes.csv", "r");
    char name[61];
    char birthday[11];
    char condition[2];
    while(1){
        char *nextLine = readFileLine(registersFile, 72);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "%60[^,],%10[^,],%1[^,]", name, birthday, condition);
        printf("adicionando nome %s\n", name);
        printList(list);
        addElementToList(list, createClient(name, birthday, condition));
        Sleep(1);
    }
}

void createRegister(){

}

void searchRegister(){

}

void updateRegister(){

}

void saveRegister(){

}


int main(){

    sortedDoublyLinkedList* registers = createSortedDoublyLinkedList();
    readRegister(registers);

    printf("(1) Realizar novo cadastro\n");
    printf("(2) Buscar cadastro\n");
    printf("(3) Alterar dados do cadastro\n");
    printf("(4) Sair\n\n");

    int selectedOption = 0;
    while(1){
        printf("Digite uma op%c%co: ", 135, 198);
        scanf("%d", &selectedOption);
        if(selectedOption > 0 && selectedOption < 5){
            break;
        }
    }
    
}