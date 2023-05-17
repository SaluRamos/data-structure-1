//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
// #include <windows.h>
#include <ctype.h>

typedef struct client{
    char name[61];
    char birthday[11]; //dd/mm/aaaa
    char condition[2]; //N, D ou H
}client;

client createClient(char* name, char* birthday, char* condition){
    client data;
    strcpy(data.name, name);
    strcpy(data.birthday, birthday);
    strcpy(data.condition, condition);
    return data;
}

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
        bool added = false; //controla se a posição foi encontrada ou não, se terminar o loop abaixo e não encontrar significa que a posição deve ser o final da lista
        bool isHead = true; //controla se a posição é a cabeça ou não
        while(current->next != NULL){
            //se for igual ou menor adiciona e encerra
            if(strcmp(value.name, current->data.name) <= 0){
                newNode->next = current;
                if(isHead == true){
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
            isHead = false;
            current = current->next; //pula de elemento
        }
        if(added == false){
            // printf("tail!\n");
            newNode->previous = list->tail;
            list->tail->next = newNode;
            list->tail = newNode;
        }
    }
}

//busca por um cliente nos cadastros pelo nome e retorna seu ponteiro
client* searchList(sortedDoublyLinkedList* list, char* name){
    node* current = list->head;
    while(current->next != NULL){
        if(strcmp(name, current->data.name) == 0){
            return &current->data;
        }
        current = current->next;
    }
    return NULL;
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

void stringToUpper(char* str) {
    while(*str){
        *str = toupper(*str);
        str++;
    }
}

void readRegister(sortedDoublyLinkedList* list){
    FILE *registersFile;
    registersFile = fopen("clientes.csv", "r");
    char name[61];
    char birthday[11];
    char condition[2];
    while(true){
        char *nextLine = readFileLine(registersFile, 72);
        if(strcmp(nextLine, "") == 0){ //verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "%60[^,],%10[^,],%1[^,]", name, birthday, condition);
        addElementToList(list, createClient(name, birthday, condition));
    }
    fclose(registersFile);
}

void createRegister(sortedDoublyLinkedList* list){
    char name[61] = "";
    char birthday[11] = "";
    char condition[2] = "";
    int day = 0;
    int month = 0;
    int year = 0;
    printf("Digite o nome completo: ");
    fgets(name, 61, stdin);
    name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
    stringToUpper(name);
    printf("Digite a data de nascimento: ");
    fgets(birthday, 11, stdin);
    birthday[strcspn(birthday, "\n")] = '\0'; //Remove o \n da string
    getchar(); //consumir o caractere de nova linha pendente no buffer
    printf("Digite a condicao de saude: ");
    fgets(condition, 2, stdin);
    condition[strcspn(condition, "\n")] = '\0'; //Remove o \n da string
    stringToUpper(condition);
    //etapa de verificação
    sscanf(birthday, "%d/%d/%d", &day, &month, &year);
    if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023){
        printf("data de aniversario invalida!\n");
    }else if(strcmp(condition, "H") != 0 && strcmp(condition, "D") != 0 && strcmp(condition, "N") != 0){
        printf("condicao de saude invalida!\n");
    }else{
        addElementToList(list, createClient(name, birthday, condition));
        printf("cadastro realizado com sucesso!\n");
    }
}

void searchRegister(sortedDoublyLinkedList* list){
    client* result;
    char name[61] = "";
    printf("Digite o nome completo: ");
    fgets(name, 61, stdin);
    name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
    stringToUpper(name);
    printf("Estamos verificando nosso sistema...\n");
    result = searchList(list, name);
    if(result == NULL){
        printf("Cadastro nao encontrado!\n");
    }else{
        printf("Cadastro encontrado!\n");
        printf("----------------------\n");
        printf("Nome: %s\n", result->name);
        printf("Data de nascimento: %s\n", result->birthday);
        printf("Condicao de saude: %s\n", result->condition);
    }
}

void updateRegister(sortedDoublyLinkedList* list){
    client* result;
    int selectedOption = 0;
    char name[61] = "";
    char birthday[11] = "";
    char condition[2] = "";
    int day = 0;
    int month = 0;
    int year = 0;
    printf("Digite o nome completo: ");
    fgets(name, 61, stdin);
    name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
    stringToUpper(name);
    printf("Estamos verificando nosso sistema...\n");
    result = searchList(list, name);
    if(result == NULL){
        printf("Cadastro nao encontrado!\n");
    }else{
        printf("Cadastro encontrado!\n");
        printf("--------------------------\n");
        printf("(1) Nome\n");
        printf("(2) Data de nascimento\n");
        printf("(3) Condicao de saude\n");
        printf("Oque deseja alterar? ");
        scanf("%d", &selectedOption);
        getchar(); //consumir o caractere de nova linha pendente no buffer
        switch (selectedOption){
            case 1:
                printf("Digite novo nome: ");
                fgets(name, 61, stdin);
                name[strcspn(name, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(name);
                strcpy(result->name, name);
                printf("Cadastro atualizado com sucesso!\n");
                break;
            case 2:
                printf("Digite nova data de nascimento: ");
                fgets(birthday, 11, stdin);
                birthday[strcspn(birthday, "\n")] = '\0'; //Remove o \n da string
                sscanf(birthday, "%d/%d/%d", &day, &month, &year);
                if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2023){
                    printf("data de aniversario invalida!\n");
                }else{
                    strcpy(result->birthday, birthday);
                    printf("Cadastro atualizado com sucesso!\n");
                }
                break;
            case 3:
                printf("Digite nova condicao de saude: ");
                fgets(condition, 2, stdin);
                condition[strcspn(condition, "\n")] = '\0'; //Remove o \n da string
                stringToUpper(condition);
                if(strcmp(condition, "H") != 0 && strcmp(condition, "D") != 0 && strcmp(condition, "N") != 0){
                    printf("condicao de saude invalida!\n");
                }else{
                    strcpy(result->condition, condition);
                    printf("Cadastro atualizado com sucesso!\n");
                }
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

//estrutura de "data" para facilitar calculos
typedef struct sTime{
    int day;
    int month;
    int year;
} sTime;

//abstrai adquirir a data atual no formato "dd/mm/YYYY" ou "%d/%m/%Y"
char* getAtualDate(){
    static char atualDate[11];
    time_t rawtime = time(NULL);
    struct tm *ts = localtime(&rawtime);
    strftime(atualDate, sizeof(atualDate), "%d/%m/%Y", ts);
    return atualDate;
}

sTime stringToSTime(char *dateString){
    sTime date;
    date.day = 0;
    date.month = 0;
    date.year = 0;
    sscanf(dateString, "%d/%d/%d", &date.day, &date.month, &date.year);
    return date;
}

int getPatientAge(char* _fromDate){
    sTime atualDate = stringToSTime(getAtualDate());
    sTime fromDate = stringToSTime(_fromDate);
    int age = atualDate.year - fromDate.year;
    if(age < 0){
        return 0;
    }
    if(fromDate.month <= atualDate.month && fromDate.day < atualDate.day && age > 0){
        age -= 1;
    }
    return age;
}

typedef struct queue{
    client *array;
    int start;
    int end;
    int atualSize;
    int maxSize;
} queue;

//inicializa as variaveis da queue
queue* createQueue(int maxSize){
    queue* newQueue = malloc(sizeof(queue));
    newQueue->array = (client*) malloc(sizeof(client)*maxSize);
    newQueue->start = 0;
    newQueue->end = 0; //o end não é onde esta o ultimo elemento, e sim onde vai ser adicionado o proximo elemento
    newQueue->atualSize = 0;
    newQueue->maxSize = maxSize;
    return newQueue;
}

//adiciona um elemento em cima da queue
void queueAppend(queue *queue_, client *newValue){
    if(queue_->atualSize + 1 <= queue_->maxSize){
        queue_->array[queue_->end] = *newValue;
        queue_->atualSize += 1;
        if(queue_->end + 1 >= queue_->maxSize){
            queue_->end = 0;
        }else{
            queue_->end += 1;
        }
    }
}

//remove o elemento de baixo da queue
client* queuePop(queue *queue_){
    if(queue_->atualSize > 0){
        queue_->atualSize -= 1;
        if(queue_->start + 1 > queue_->maxSize){
            queue_->start = 0;
            return &queue_->array[queue_->maxSize];
        }else{
            queue_->start += 1;
            return &queue_->array[queue_->start];
        }
    }
    return NULL;
}

//imprime informações da queue
void printQueue(queue *queue_, char info[]){
    printf("----------------------");
    if(strcmp(info, "") != 0){
        printf("\n%s", info);
    }
    if(queue_->atualSize == 0){
        printf("\nvazia!");
    }else{
        int place = 1;
        if(queue_->start < queue_->end){
            for(int i = queue_->start; i < queue_->end; i++){
                printf("\n%d - %s", place, queue_->array[i].name);
                place += 1;
            }
        }else{
            for(int i = queue_->start; i <= queue_->maxSize - 1; i++){
                printf("\n%d - %s", place, queue_->array[i].name);
                place += 1;
            }
            for(int i = 0; i < queue_->end; i++){
                printf("\n%d - %s", place, queue_->array[i].name);
                place += 1;
            }
        }
    }
    printf("\n----------------------\n");
}

typedef struct report{
    int totalCalls;
    int totalH;
    int totalD;
    int totalN;
} report;

report createReport(){
    report newReport;
    newReport.totalCalls = 0;
    newReport.totalD = 0;
    newReport.totalH = 0;
    newReport.totalN = 0;
    return newReport;
}

report createWaitQueue(queue *queue_, sortedDoublyLinkedList* list){
    report todayReport = createReport();
    client* result;
    FILE *waitQueueFile;
    waitQueueFile = fopen("DadosChegada.txt", "r");
    while(true){
        char *nextLine = readFileLine(waitQueueFile, 72);
        if(strcmp(nextLine, "") == 0){ //verifica se a linha é vazia
            break;
        }
        stringToUpper(nextLine);
        result = searchList(list, nextLine);
        if(result == NULL){
            printf("(%s) Cadastro nao encontrado!\n", nextLine);
        }else{
            int clientAge = getPatientAge(result->birthday);
            if(clientAge < 12){
                printf("(%s) Cliente possui menos de 12 anos de idade (%d anos, nascimento %s)\n", nextLine, clientAge, result->birthday);
            }else{
                queueAppend(queue_, result);
                todayReport.totalCalls += 1;
                if(strcmp(result->condition, "H") == 0){
                    todayReport.totalH += 1;
                }else if(strcmp(result->condition, "D") == 0){
                    todayReport.totalD += 1;
                }else{
                    todayReport.totalN += 1;
                }
                printf("(%s) Adicionado a fila de espera com sucesso!\n", nextLine);
            }
        }
    }
    fclose(waitQueueFile);
    return todayReport;
}

void nextBuffet(queue *waitQueue, queue *hQueue, queue *dQueue, queue *nQueue){
    client *nextClient = queuePop(waitQueue);
    if(nextClient == NULL){
        printf("Nao ha mais clientes na fila de espera!\n");
    }else if(strcmp(nextClient->condition, "H") == 0){
        if(hQueue->atualSize < hQueue->maxSize){
            queueAppend(hQueue, nextClient);
            printf("(%s) Cliente adicionado a fila de hipertensos!\n", nextClient->name);
        }else{
            printf("Nao ha espaco na fila de hipertensos!\n");
        }
    }else if(strcmp(nextClient->condition, "D") == 0){
        if(dQueue->atualSize < dQueue->maxSize){
            queueAppend(dQueue, nextClient);
            printf("(%s) Cliente adicionado a fila de diabeticos!\n", nextClient->name);
        }else{
            printf("Nao ha espaco na fila de diabeticos!\n");
        }
    }else{
        if(nQueue->atualSize < nQueue->maxSize){
            queueAppend(nQueue, nextClient);
            printf("(%s) Cliente adicionado a fila de saudaveis!\n", nextClient->name);
        }else{
            printf("Nao ha espaco na fila de saudaveis!\n");
        }
    }
}

void exitBuffet(queue *hQueue, queue *dQueue, queue *nQueue){
    char dName[61];
    char hName[61];
    char nName[61];
    if(dQueue->atualSize == 0){
        strcpy(dName, "Nenhum cliente");
    }else{
        strcpy(dName, dQueue->array[dQueue->start].name);
    }
    if(hQueue->atualSize == 0){
        strcpy(hName, "Nenhum cliente");
    }else{
        strcpy(hName, hQueue->array[hQueue->start].name);
    }
    if(nQueue->atualSize == 0){
        strcpy(nName, "Nenhum cliente");
    }else{
        strcpy(nName, nQueue->array[nQueue->start].name);
    }
    printf("(1) fila diabetico (%s)\n", dName);
    printf("(2) fila hipertenso (%s)\n", hName);
    printf("(3) fila saudavel (%s)\n", nName);
    printf("Qual dos clientes esta saindo? ");
    int selectedOption = 0;
    scanf("%d", &selectedOption);
    switch(selectedOption){
        case 1:
            queuePop(dQueue);
            printf("%s removido da fila!\n", dName);
            break;
        case 2:
            queuePop(hQueue);
            printf("%s removido da fila!\n", hName);
            break;
        case 3:
            queuePop(nQueue);
            printf("%s removido da fila!\n", nName);
            break;
        default:
            printf("opcao invalida\n");
            break;
    }
}

void generateReport(report todayReport){
    int todayDay = 0;
    int todayMonth = 0;
    int todayYear = 0;
    sscanf(getAtualDate(), "%d/%d/%d", &todayDay, &todayMonth, &todayYear);
    char filename[24];
    snprintf(filename, sizeof(filename), "Relatorio_%d_%d_%04d.txt", todayDay, todayMonth, todayYear);
    FILE *reportFile;
    reportFile = fopen(filename, "w");
    fprintf(reportFile, "Relatório do dia %d/%d/%d\n", todayDay, todayMonth, todayYear);
    fprintf(reportFile, "\n");
    fprintf(reportFile, "Total de atendimentos: %d\n", todayReport.totalCalls);
    fprintf(reportFile, "Hipertensos: %d\n", todayReport.totalH);
    fprintf(reportFile, "Diabeticos: %d\n", todayReport.totalD);
    fprintf(reportFile, "Saudaveis: %d\n", todayReport.totalN);
    fprintf(reportFile, "\n");
    int totalIncome = todayReport.totalH*50 + todayReport.totalD*55 + todayReport.totalN*40;
    fprintf(reportFile, "Total de entrada (R$): %d (%d + %d + %d)\n", totalIncome, todayReport.totalH*50, todayReport.totalD*55, todayReport.totalN*40);
    int totalCost = todayReport.totalD*35 + todayReport.totalH*30 + todayReport.totalN*25;
    fprintf(reportFile, "Total de custos de despesas (R$): %d (%d + %d + %d)\n", totalCost, todayReport.totalH*35, todayReport.totalD*30, todayReport.totalN*25);
    fprintf(reportFile, "Lucro (R$): %d", totalIncome - totalCost);
    fclose(reportFile);
}

int main(){

    sortedDoublyLinkedList* registers = createSortedDoublyLinkedList();
    readRegister(registers);
    queue* waitQueue = createQueue(1000);
    queue* dQueue = createQueue(15);
    queue* hQueue = createQueue(15);
    queue* nQueue = createQueue(15);
    report todayReport;
    int selectedOption = 0;

    while(true){
        printf("(1) Realizar novo cadastro\n");
        printf("(2) Buscar cadastro\n");
        printf("(3) Alterar dados do cadastro\n");
        printf("(4) Montar fila de espera\n");
        printf("(5) Proximo a ir ao buffet\n"); //tirar uma pessoa da fila de espera e colocá-la na fila do buffet correspondente à sua condição de saúde (se houver espaço no restaurante)
        printf("(6) Sair do restaurante\n"); //quando um cliente deixa o restaurante, avisar qual cliente está saindo e atualizar a fila repectiva
        printf("(7) Imprimir fila D\n");
        printf("(8) Imprimir fila H\n");
        printf("(9) Imprimir fila N\n");
        printf("(10) Imprimir fila de espera\n");
        printf("(11) Imprimir todas as filas\n");
        printf("(12) Imprimir lista de cadastro\n");
        printf("(13) Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &selectedOption);
        getchar(); //consumir o caractere de nova linha pendente no buffer
        printf("\n");
        switch(selectedOption){
            case 1:
                createRegister(registers);
                break;
            case 2:
                searchRegister(registers);
                break;
            case 3:
                updateRegister(registers);
                break;
            case 4:
                todayReport = createWaitQueue(waitQueue, registers);
                break;
            case 5:
                nextBuffet(waitQueue, hQueue, dQueue, nQueue);
                break;
            case 6:
                exitBuffet(hQueue, dQueue, nQueue);
                break;
            case 7:
                printQueue(dQueue, "fila de diabeticos");
                break;
            case 8:
                printQueue(hQueue, "fila de hipertensos");
                break;
            case 9:
                printQueue(nQueue, "fila de saudaveis");
                break;
            case 10:
                printQueue(waitQueue, "fila de espera");
                break;
            case 11:
                printQueue(waitQueue, "fila de espera");
                printQueue(dQueue, "fila de diabeticos");
                printQueue(hQueue, "fila de hipertensos");
                printQueue(nQueue, "fila de saudaveis");
                break;
            case 12:
                printList(registers);
                break;
            case 13:
                free(registers);
                free(waitQueue);
                free(hQueue);
                free(dQueue);
                free(nQueue);
                generateReport(todayReport);
                return 0;
                break;
            default:
                printf("opcao invalida\n");
                break;
        }
        printf("\n");
    }
}