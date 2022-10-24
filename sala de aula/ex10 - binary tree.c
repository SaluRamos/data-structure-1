#include <stdio.h>
#include <stdlib.h>

//exercicio arvore binaria

struct node{
    int data_element;
    struct node *left, *right;
};

//inicializa node
struct node *newNode(int data_element){
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->data_element = data_element;
    temp->left = temp->right = NULL;
    return temp;
}

void displayNode(struct node *root){
    if(root != NULL){
        displayNode(root->left);
        printf("%d \n", root->data_element);
        displayNode(root->right);
    }
}

struct node* insertToNode(struct node* node, int data_element){
    if(node == NULL){
        return newNode(data_element);
    }
    if(data_element < node->data_element){
        node->left = insertToNode(node->left, data_element);
    }else if (data_element > node->data_element){
        node->right = insertToNode(node->right, data_element);
    }
    return node; //c obriga a função a retornar um node
}

int main(){
    struct node *root = NULL;

    root = insertToNode(root, 5);
    insertToNode(root, 7);
    insertToNode(root, 3);
    displayNode(root);

    return 1;
}