//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <regex.h>
// #include <windows.h>
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
    newNode->next = NULL;
    newNode->previous = NULL;
    if(list->head == NULL){
        // printf("primeiro elemento!\n");
        newNode->next = NULL;
        newNode->previous = NULL;
        list->head = newNode;
        list->tail = newNode;
    }else{ //insertion sort
        node* current = list->head;
        bool added = false;
        int atual = 0;
        while(current->next != NULL){
            //se for igual ou menor adiciona e encerra
            if(strcmp(value.name, current->data.name) <= 0){
                newNode->next = current;
                if(atual == 0){
                    // printf("head\n");
                    list->head = newNode;
                }else{
                    // printf("meio\n");
                    newNode->previous = current->previous;
                    current->previous->next = newNode;
                }
                current->previous = newNode;
                added = true;
                break;
            }
            current = current->next; //pula de elemento
            atual++;
        }
        if(added == false){
            // printf("tail!\n");
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
        // printf("%s, %s, %s (next: %s, previous: %s, head: %s, tail: %s)\n", current->data.name, current->data.birthday, current->data.condition, current->next->data.name, current->previous->data.name, list->head->data.name, list->tail->data.name);
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
        addElementToList(list, createClient(name, birthday, condition));
        // printf("adicionando nome %s\n", name);
    }
    // printList(list);
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
    printf("(4) Montar fila de espera\n"); //realizar a leitura de DadosChegada.txt, verificar quais clientes ir˜ao para fila de espera, quais entrarão imediatamente no restaurante e quais não serão servidos
    printf("(5) Próximo a ir ao buffet\n"); //tirar uma pessoa da fila de espera e colocá-la na fila do buffet correspondente à sua condição de saúde (se houver espaço no restaurante)
    printf("(6) Sair do restaurante\n"); //quando um cliente deixa o restaurante, avisar qual cliente está saindo e atualizar a fila repectiva
    printf("(7) Imprimir fila D\n");
    printf("(8) Imprimir fila H\n");
    printf("(9) Imprimir fila N\n");
    printf("(10) Imprimir fila de espera\n");
    printf("(11) Imprimir todas as filas\n");
    printf("(12) Sair\n\n");

    regex_t regex;
    int reti;
    int selectedOption = 0;
    while(1){
        printf("Digite uma op%c%co: ", 135, 198);
        scanf("%d", &selectedOption);
        getchar(); //consumir o caractere de nova linha pendente no buffer
        printf("\n");
        char name[61] = "";
        char birthday[11] = "";
        char condition = 'A';
        switch(selectedOption){
            case 1:
                printf("Digite o nome completo: ");
                fgets(name, 61, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove o \n da string
                regcomp(&regex, "/^[a-zA-Z ]+$/m", 0);
                reti = regexec(&regex, name, 0, NULL, 0);
                printf("resultado regex %d, input = '%s'\n", reti, name);
                char errbuf[100];
                regerror(reti, &regex, errbuf, sizeof(errbuf));
                fprintf(stderr, "Erro ao executar a expressão regular: %s\n", errbuf);
                if(regexec(&regex, name, 0, NULL, 0) != 0){
                    printf("vish\n");
                }
                regfree(&regex);
                printf("Digite a data de nascimento: ");
                fgets(birthday, 11 ,stdin);
                birthday[strcspn(birthday, "\n")] = '\0'; // Remove o \n da string
                printf("Digite a condição de saúde: ");
                scanf(" %c", &condition); //espaço antes de %c para ignorar caracteres em branco
                printf("voce digitou, %s, %s, %c\n", name, birthday, condition);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                free(registers);
                return 0;
                break;
            default:
                printf("comando inválido\n");
                break;
        }
        printf("\n");
    }
}