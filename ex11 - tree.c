#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_NODE_ELEMENTS 100

//exercicio arvore

struct tree{
    int value; //valor do node
    struct tree *node[MAX_NODE_ELEMENTS]; //array de nodes
    int size; //quantidade de nodes atuais
};

//inicializa node
struct tree *newTree(int initial_value){
    struct tree *temp = (struct tree *) malloc(sizeof(struct tree));
    temp->size = 0;
    temp->value = initial_value;
    return temp;
}

//ittera entre os elementos de uma arvore
void itterTree(struct tree* tree_, int depth){
    if(tree_->size == 0){
        printf("%d ", tree_->value);
    }else{
        for(int i = 0; i < tree_->size; i++){
            printf("%d ", tree_->value);
        }
    }
    printf("\n\n");
}

//printa todos os paths
void printTree(struct tree *root){
    
}

//print um path
void print(char path[]){

}

//retorna quantidade de determinado char em uma string
int stringCharAmount(char string[], char char_){
    int amount = 0;
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == char_){
            amount += 1;
        }
    }
    return amount;
}

//retorna array de int de uma string com os padrões de uma string path (não existe objeto string path pela falta de suporte da linguagem)
int* splitPath(char *string){
    int pathDepth = stringCharAmount(string, ',') + 1;
    int *array = (int *) malloc(sizeof(int)*pathDepth);
    int atualArray = 0;
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
            atualTemp = 0;
            atualArray += 1;
        }else{
            temp[atualTemp] = string[i];
        }
    }
    return array;
}

//insere um elemento na árvore
struct tree* insert(struct tree* tree_, int new_value, char path[]){

    //verifica se o 'depth' existe
    //se existir, insere novo elemento na arvore


    if(tree_ == NULL){
        return newTree(new_value);
    }else{
        int pathDepth = stringCharAmount(path, ',') + 1;
        int *array = splitPath(path);
        // node->elements[node->atualSize - 1] = insert(node->elements[node->atualSize - 1], data_element);
        // node->atualSize += 1;
    }
    return node; //c obriga a função a retornar um node
}

int main(){
    struct node *root = NULL;

    root = insert(root, 10, "0");
    insert(root, 20, "0,0");
    // printf("%d\n", root->data_element);
    // printf("chegou aqui");
    display(root);

    return 1;
}