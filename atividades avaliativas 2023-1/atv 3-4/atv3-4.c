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
        client cache;
        bool appendFirst = false;
        node* current = list->head;
        while(current->next != NULL){
            if(strcmp(current->data.name, value.name) > 0){//current igual ou maior
            //salva o atual
            //aplica novo valor
                if(appendFirst == false){    
                    cache = current->data;
                    current->data = value;
                    appendFirst = true;
                }else{
                    client cache2;
                    cache2 = current->data;
                    current->data = cache;
                    cache = cache2;
                }
            }
            current = current->next;
        }
        if(appendFirst == true){  
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








char* removeAccents(char* str){
    const char* withAccents = "áéíóúàèìòùâêîôûãõçÁÉÍÓÚÀÈÌÒÙÂÊÎÔÛÃÕÇ";
    const char* noAccents = "aeiouaeiouaeiouaocaeiouaeiouaeiouaoc";
    char* p = str;
    while(*p != '\0') {
        char* assent = strchr(withAccents, *p);
        if(assent != NULL){
            *p = noAccents[assent - withAccents];
        }
        p++;
    }
    return str;
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
    //remove acentos
    removerAcentos(lowerstr1);
    removeAccents(lowerstr2);
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

    compareStringAZ("teÁTe", "Loo");

    // sortedDoublyLinkedList* registers = createSortedDoublyLinkedList();
    // readRegister(registers);

    // printf("(1) Realizar novo cadastro\n");
    // printf("(2) Buscar cadastro\n");
    // printf("(3) Alterar dados do cadastro\n");
    // printf("(4) Sair\n\n");

    // int selectedOption = 0;
    // while(1){
    //     printf("Digite uma op%c%co: ", 135, 198);
    //     scanf("%d", &selectedOption);
    //     if(selectedOption > 0 && selectedOption < 5){
    //         break;
    //     }
    // }
    
}