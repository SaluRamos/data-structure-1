//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct linkedList{
    node* head;
}linkedList;

linkedList* createlinkedList() {
    linkedList* list = malloc(sizeof(linkedList));
    list->head = NULL;
    return list;
}

void addElementToList(linkedList* list, int value){
    node* newNode = malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    if(list->head == NULL) {
        list->head = newNode;
    }else{
        node* current = list->head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(linkedList* list){
    node* current = list->head;
    while(current != NULL){
        printf("%d\n", current->data);
        current = current->next;
    }
}


void convertDecimalToHexadecimal(int decimal){
    linkedList* hexList = createlinkedList();
    //loop de divisão até quociente ser 0
    while(1){
        if(decimal / 16 > 0){
            //adiciona resto na pilha
            addElementToList(hexList, decimal % 16);
        }else{
            //adiciona quociente na pilha
            addElementToList(hexList, decimal);
            break;
        }
        decimal = floor(decimal / 16);
    }
    printList(hexList);
}

int main(int argc, char *argv[]){
    int userInput = 0;
    printf("Digite um decimal positivo: ");
    scanf("%d", &userInput);
    if(userInput < 0){
        printf("Input negativo!");
        return 0;
    }
    convertDecimalToHexadecimal(userInput);
}