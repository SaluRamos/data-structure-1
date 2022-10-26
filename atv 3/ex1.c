//Feito sozinho por: Salu Conteratto Ramos
//RA: 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //usado para: copiar strings, comparar strings, descobrir tamanho de strings e quebrar strings em partes a partir de um char
#include <time.h> //usado para descobrir data atual

//declara a estrutura de um paciente
typedef struct{
    char *name;
    char *sex;
    char *birthDay;
    int age;
    char *lastConsultation;
    int daysSinceLastConsultation;
} patient;

//estrutura de "data" para facilitar calculos
typedef struct{
    int day;
    int month;
    int year;
} sTime;

sTime stringToSTime(char *dateString){
    char *dateStringCopy = (char *) malloc(11);
    strcpy(dateStringCopy, dateString);
    sTime date;
    char *day = strtok(dateStringCopy, "/");
    date.day = atoi(day);
    char *month = strtok(NULL, "/");
    date.month = atoi(month);
    char *year = strtok(NULL, "/");
    date.year = atoi(year);
    return date;
}

//abstrai adquirir a data atual no formato "dd/mm/YYYY" ou "%d/%m/%Y"
char* getAtualDate(){
    char atualDate[11];
    time_t rawtime = time(NULL);
    struct tm *ts = localtime(&rawtime);
    strftime(atualDate, sizeof(atualDate), "%d/%m/%Y", ts);
    // free(rawtime);
    // free(ts);
    char *atualDateCopy = (char *) malloc(11);
    strcpy(atualDateCopy, atualDate);
    return atualDateCopy;
}

//faz a contagem de dias a partir de uma data
int daysFromDate(char* _fromDate){
    sTime atualDate = stringToSTime(getAtualDate());
    sTime fromDate = stringToSTime(_fromDate);
    int dayOfYearToInitialMonthDay[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int atualDateDayOfYear = dayOfYearToInitialMonthDay[atualDate.month - 1] + atualDate.day;
    int fromDateDayOfYear = dayOfYearToInitialMonthDay[fromDate.month - 1] + fromDate.day;
    int days = (atualDate.year - fromDate.year)*365;
    days += atualDateDayOfYear - fromDateDayOfYear;
    return days;
}

//descobre a idade do paciente a partir da data de nascimento
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

//inicializa um objeto do tipo Paciente a partir de uma linha do banco de dados
patient createPatientFromLine(char *info){
    patient newPatient;
    //atribui nome
    char *name = strtok(info, ",");
    memmove(name, name + 1, strlen(name));
    newPatient.name = name;
    //atribui sexo
    char *sex = strtok(NULL, ",");
    memmove(sex, sex + 1, strlen(sex));
    newPatient.sex = sex;
    //atribui data de nascimento
    char *birthDay = strtok(NULL, ",");
    memmove(birthDay, birthDay + 1, strlen(birthDay));
    newPatient.birthDay = birthDay;
    //atribui última consulta
    char *lastConsultation = strtok(NULL, ",");
    memmove(lastConsultation, lastConsultation + 1, strlen(lastConsultation));
    lastConsultation[strlen(lastConsultation) - 1] = '\0';
    newPatient.lastConsultation = lastConsultation;
    //atribui idade
    newPatient.age = getPatientAge(birthDay);
    //atribui dias desde última consulta
    newPatient.daysSinceLastConsultation = daysFromDate(lastConsultation);
    return newPatient;
}

//inicializa um objeto do tipo Paciente a partir de variaveis definidas
patient createPatient(char *name, char *sex, char* birthDay, int age, char *lastConsultation, int daysSinceLastConsultation){
    patient newPatient;
    newPatient.name = name;
    newPatient.sex = sex;
    newPatient.birthDay = birthDay;
    newPatient.lastConsultation = lastConsultation;
    newPatient.age = getPatientAge(birthDay);
    newPatient.daysSinceLastConsultation = daysFromDate(lastConsultation);
    return newPatient;
}

//mostra informações de um objeto paciente
void printPatient(patient *aPatient){
    printf("NOME: '%s', SEXO: '%s', NASCIMENTO: '%s', ULTIMA CONSULTA: '%s', IDADE: '%d', DIAS DESDE ULTIMA CONSULTA: '%d'\n\n", aPatient->name, aPatient->sex, aPatient->birthDay, aPatient->lastConsultation, aPatient->age, aPatient->daysSinceLastConsultation);
}























// node creation
struct Node {
  patient data;
  struct Node* next;
  struct Node* prev;
};

// insert node at the front
void insertFront(struct Node** head, patient data) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = (*head);
  newNode->prev = NULL;
  if ((*head) != NULL){
    (*head)->prev = newNode;
  }
  (*head) = newNode;
}

// insert a node after a specific node
void insertAfter(struct Node* prev_node, patient data) {
  if (prev_node == NULL) {
    printf("previous node cannot be null");
    return;
  }
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = prev_node->next;
  prev_node->next = newNode;
  newNode->prev = prev_node;
  if (newNode->next != NULL){
    newNode->next->prev = newNode;
  }
}

// insert a newNode at the end of the list
void insertEnd(struct Node** head, patient data) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  struct Node* temp = *head;
  if (*head == NULL) {
    newNode->prev = NULL;
    *head = newNode;
    return;
  }
  while (temp->next != NULL){
    temp = temp->next;
  }
  temp->next = newNode;
  newNode->prev = temp;
}

// print the doubly linked list
void displayList(struct Node* node) {
  struct Node* last;
  while (node != NULL) {
    
    last = node;
    node = node->next;
  }
  if (node == NULL){
    printf("NULL\n");
  }
}

//abstração para ler próxima linha de um arquivo
char* readFileLine(FILE *f){
    int lineLenght = 150;
    char ch;
    char *line = (char *) malloc(sizeof(char)*lineLenght);
    for(int i = 0; i < lineLenght; i++){
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

int main(int argc, char *argv[]){
    //inicializa arquivo de entrada e saída
    FILE *inputFile;
    FILE *outputFileAZ, *outputFileZA;
    if(argc > 1){
        inputFile = fopen(strcat(argv[1], ".txt"), "r");
    }else{
        inputFile = fopen("pacientes.txt", "r");
    }
    if(argc > 2){
        outputFileAZ = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        outputFileAZ = fopen("AZ.txt", "w+");
    }
    if(argc > 3){
        outputFileZA = fopen(strcat(argv[3], ".txt"), "w+");
    }else{
        outputFileZA = fopen("ZA.txt", "w+");
    }
    //declara variavel que contém todos os pacientes (lista duplamente encadeada)
    patient patients[40];
    //extração dos dados
    int atualLine = 0;
    while(1){
        char *nextLine = readFileLine(inputFile);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia, se for acabou o arquivo
            break;
        }
        patients[atualLine] = createPatientFromLine(nextLine);
        printPatient(&patients[atualLine]);
        atualLine += 1;
    }
    //funcionamento do software






    //fecha arquivos
    fclose(inputFile);
    fclose(outputFileAZ);
    fclose(outputFileZA);
    //limpa variaveis
    free(inputFile);
    free(outputFileAZ);
    free(outputFileZA);
    // free(patients);
}