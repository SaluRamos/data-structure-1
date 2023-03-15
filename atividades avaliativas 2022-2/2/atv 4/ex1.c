//Feito sozinho por: Salu Conteratto Ramos
//RA: 2150352

#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


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

void removeAccents(char str[]){
    char banned[] = "ÁÀÃÂÇáàãâçÉÊéêÍíÑÓÔÕñóôõÚÜúü";
    char sub[] =  "AAAACaaaacEEeeIiNOOOnoooUUuu";
    for(int i = 0; i < strlen(str) - 1; i++){
        for(int j = 0; j < 28; j++){
            if(str[i] == banned[j]){
                printf("substituindo %d (%c) por %d (%c) pois é igual a %d (%c)\n", i, str[i], j, sub[j], j, banned[j]);
                str[i] = sub[j];
            }
        }
    }
}

void printTreeAZ(struct node *ptr, int level){
    if(ptr == NULL)
        return;
    else
    {
        printTreeAZ(ptr->lchild, level + 1);
        printf("termo '%s' página %d\n", ptr->info, ptr->page);
        printTreeAZ(ptr->rchild, level + 1);
    }
}



int main(int argc, char *argv[]){

    SetConsoleOutputCP(CP_UTF8);

    char teste[] = "lokoç";
    removeAccents(teste);
    printf("%s\n", teste);
    return 0;

    int choice;
    char key[200];
    int keyPage = 0;
    struct node *root = NULL;
    FILE *remissivoFile;

    if(argc > 1){
        printf("sim\n");
        remissivoFile = fopen(strcat(argv[1], ".csv"), "r");
    }else{
        remissivoFile = fopen("remissivo.csv", "r");
    }
    if(remissivoFile == NULL){
        printf("ARQUIVO NAO ENCONTRADO");
        exit(1);
    }

    while(1){
        char *nextLine = readFileLine(remissivoFile, 210);

        if(strcmp(nextLine, "") == 0){ //verifica se a linha é vazia
            break;
        }

        char *token = strtok(nextLine, ",");
        char info[200];
        strcpy(info, token);
        token = strtok(NULL, ",");
        int page = atoi(token);

        root = insert(root, info, page);

    }

    while (1)
    {
        printf("\n");
        printf("1.Inserir novo termo\n");
        printf("2.Pesquisar termo\n");
        printf("3.Mostrar em ordem alfabética\n");
        printf("4.Sair\n");

        printf("\nOque deseja? ");
        scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //desbuga o C por conta de usar o gets mais a frente
        switch (choice){
        case 1:
            printf("Digite termo a ser adicionado: ");
            gets(key);
            printf("Digite página a ser adicionada: ");
            keyPage = 0;
            scanf("%d", &keyPage);
            root = insert(root, key, keyPage);
            break;
        case 2:
            printf("Digite termo a ser procurado: ");
            gets(key);
            keyPage = binarySearch(root, key);
            if(keyPage == 0){
                printf("Termo não encontrado\n");
            }
            else{
                printf("a página é %d\n", keyPage);
            }
            break;
        case 3:
            printf("\n");
            printTreeAZ(root, 0);
            break;
        case 4:
            exit(1);
            break;
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}