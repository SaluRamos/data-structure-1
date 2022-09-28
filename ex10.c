#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODE_ELEMENTS 100

//exercicio arvore

struct node{
    int data_element;
    struct node *elements[MAX_NODE_ELEMENTS];
    int atualSize;
};

//inicializa node
struct node *newNode(int data_element){
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->atualSize = 0;
    temp->data_element = data_element;
    for(int i = 0; i < MAX_NODE_ELEMENTS; i++){
        temp->elements[i] = NULL;
    }
    return temp;
}

void display(struct node *root){
    if(root != NULL){
        for(int i = 0; i < root->atualSize; i++){
            if(root->elements[i] != NULL){
                display(root->elements[i]);
            }
            printf("%d \n", root->data_element);
        }
    }
}

//funcionando
int stringCharAmount(char string[], char char_){
    int amount = 0;
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == char_){
            amount += 1;
        }
    }
    return amount;
}

//funcionando
int* splitPath(char *string){
    int pathDepth = stringCharAmount(string, ',') + 1;
    int *array = (int *) malloc(sizeof(int)*pathDepth);
    int atualArray = 0;
    for(int i = 0; i < pathDepth; i++){
        array[i] = 0;
    }

    int tempMaxSize = 5;
    char *temp = (char *) malloc(sizeof(char)*tempMaxSize);
    int atualTemp = 0;
    
    int stringLen = strlen(string);

    for(int i = 0; i < stringLen; i++){
        if(string[i] == ',' || i == (stringLen - 1)){
            if(i == (stringLen - 1)){
                temp[atualTemp] = string[i];
            }
            array[atualArray] = atoi(temp);
            temp[0] = '\0';
            // for(int j = 0; j < tempMaxSize; j++){
            //     temp[j] = NULL;
            // }
            atualTemp = 0;
            atualArray += 1;
        }else{
            temp[atualTemp] = string[i];
        }
    }
    return array;
}

//precisa de um argumento string 'path'
struct node* insert(struct node* node, int data_element, char path[]){
    if(node == NULL){
        return newNode(data_element);
    }else{
        int *array = splitPath(path);
        // node->elements[node->atualSize - 1] = insert(node->elements[node->atualSize - 1], data_element);
        // node->atualSize += 1;
    }
    return node; //c obriga a função a retornar um node
}

int main(){
    // struct node *root = NULL;

    int pathDepth = stringCharAmount("0,0,12", ',') + 1;
    printf("tamanho = %d\n", pathDepth);
    int *array = splitPath("0,0,12");
    for(int i = 0; i < pathDepth; i++){
        printf("%d\n", array[i]);
    }
    // root = insert(root, 10, "0");
    // insert(root, 20, "0,0");
    // printf("%d\n", root->data_element);
    // printf("chegou aqui");
    // display(root);

    return 1;
}