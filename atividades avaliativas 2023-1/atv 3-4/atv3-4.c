//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>
#include <ctype.h>

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
        node* current = list->head;
        bool added = false;
        while(current->next != NULL){
            printf("teste\n");
            //se for igual ou menor adiciona e encerra
            if(strcmp(value.name, current->data.name) <= 0){
                newNode->next = current;
                newNode->previous = current->previous;
                current->previous->next = newNode;
                current->previous = newNode;
                added = true;
                break;
            }
            current = current->next; //pula de elemento
        }
        if(added == false){
            newNode->previous = list->tail;
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }
}

//imprime uma lista
void printList(sortedDoublyLinkedList* list){
    node* current = list->head;
    printf("----------------------\n");
    while(current != NULL){
        printf("%s, %s, %s (next: %s, previous: %s, head: %s, tail: %s)\n", current->data.name, current->data.birthday, current->data.condition, current->next->data.name, current->previous->data.name, list->head->data.name, list->tail->data.name);
        current = current->next;
    }
    printf("----------------------\n");
    Sleep(500);
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






int compareStringAZ(char str1[], char str2[]){
    //transforma caracteres das strings em minusculas
    char lowerstr1[strlen(str1)];
    for(int i = 0; i < strlen(str1); i++) {
        lowerstr1[i] = tolower(str1[i]);
    }
    lowerstr1[strlen(str1)] = '\0';
    char lowerstr2[strlen(str2)];
    for(int i = 0; i < strlen(str2); i++) {
        lowerstr2[i] = tolower(str2[i]);
    }
    lowerstr2[strlen(str2)] = '\0';
    //descobre string de menor tamanho
    int maxCompare = 0;
    int sizestr1 = strlen(str1);
    int sizestr2 = strlen(str2);
    if(sizestr1 > sizestr2){
        maxCompare = sizestr2;
    }else{
        maxCompare = sizestr1;
    }
    printf("%d, %s, %s\n", maxCompare, lowerstr1, lowerstr2);
    //1, str1 > str2
    //0, str1 = str2
    //-1, str1 < str2
    // if(result == 0) {
    //     if(sizestr1 < sizestr2) {
    //         result = -1;
    //     } else if(sizestr1 > sizestr2) {
    //         result = 1;
    //     }
    // }
    return 0;
}

client createClient(char* name, char* birthday, char *condition){
    client data;
    //"!\#$%&'()*+,-./0123456789:;<=>?@[\\]^_`{|}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"; caracteres proibidos para nome
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
        addElementToList(list, createClient(name, birthday, condition));
        printf("nome adicionado\n");
        printList(list);
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
        switch(selectedOption){
            case 1:
                break;
                break;
            case 2:
                break;
                break;
            case 3:
                break;
                break;
            case 4:
                break;
                break;
            default:
                break;

        }
    }
    
}