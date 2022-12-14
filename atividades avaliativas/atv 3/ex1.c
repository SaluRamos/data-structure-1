//Feito sozinho por: Salu Conteratto Ramos
//RA: 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //usado para descobrir data atual
#include <ctype.h> //função tolower()
#include <stdbool.h>

//declara a estrutura de um paciente
typedef struct{
    char name[60];
    char sex[2];
    char birthDay[11];
    char lastConsultation[11];
} patient;

//estrutura de "data" para facilitar calculos
typedef struct{
    int day;
    int month;
    int year;
} sTime;

sTime stringToSTime(char *dateString){
    sTime date;
    date.day = 0;
    date.month = 0;
    date.year = 0;
    sscanf(dateString, "%d/%d/%d", &date.day, &date.month, &date.year);
    return date;
}

//abstrai adquirir a data atual no formato "dd/mm/YYYY" ou "%d/%m/%Y"
char* getAtualDate(){
    char atualDate[11];
    time_t rawtime = time(NULL);
    struct tm *ts = localtime(&rawtime);
    strftime(atualDate, sizeof(atualDate), "%d/%m/%Y", ts);
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

//inicializa um objeto do tipo Paciente a partir de variaveis definidas
patient createPatient(char *name, char *sex, char* birthDay, char *lastConsultation){
    patient newPatient;
    //converte nome para lowercase
    char result[60] = "";
    for(int i = 0; name[i] != '\0'; i++){
        result[i] = tolower(name[i]);
    }
    //copia as variaveis
    strcpy(newPatient.name, result);
    strcpy(newPatient.sex, sex);
    strcpy(newPatient.birthDay, birthDay);
    strcpy(newPatient.lastConsultation, lastConsultation);
    return newPatient;
}

//mostra informações de um objeto paciente
void printPatient(patient aPatient){
    printf("NOME: '%s', SEXO: '%s', NASCIMENTO: '%s', ULTIMA CONSULTA: '%s'\n\n", aPatient.name, aPatient.sex, aPatient.birthDay, aPatient.lastConsultation);
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

struct node{
  patient data;
  struct node *previous;
  struct node *next;
};

struct node *head, *tail = NULL;

void addNode(patient data) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    newNode->data = data;
    if(head == NULL){
        head = tail = newNode;
        head->previous = NULL;
        tail->next = NULL;
    }
    else{
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
        tail->next = NULL;
    }
}

void azsortList() {
    struct node *current = NULL, *index = NULL;
    patient temp;
    if(head == NULL){
        return;
    }
    else {
        for(current = head; current->next != NULL; current = current->next) {
            for(index = current->next; index != NULL; index = index->next) {
                if(strcmp(current->data.name, index->data.name) > 0) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
            }
        }
    }
}

void zasortList() {
    struct node *current = NULL, *index = NULL;
    patient temp;
    if(head == NULL){
        return;
    }
    else {
        for(current = head; current->next != NULL; current = current->next) {
            for(index = current->next; index != NULL; index = index->next) {
                if(strcmp(current->data.name, index->data.name) < 0) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
            }
        }
    }
}

void display() {
    struct node *current = head;
    printf("\n\n");
    if(head == NULL) {
        printf("EMPTY\n\n");
        return;
    }
    while(current != NULL) {
        printf("%s -> ", current->data.name);
        current = current->next;
    }
    printf("\n\n");
}

void option1(){
    char name[60];
    char sex[2];
    char birthDay[11];
    char lastConsultation[11];
    patient newPatient;
    printf("Digite o nome: ");
    gets(name);
    printf("Digite o sexo: ");
    gets(sex);
    printf("Digite data de nascimento: ");
    gets(birthDay);
    printf("Digite data de ultima consulta: ");
    gets(lastConsultation);
    newPatient = createPatient(name, sex, birthDay, lastConsultation);
    addNode(newPatient);
    display();
}

void option2(){
    printf("Digite nome para buscar: ");
    char name[60];
    gets(name);
    struct node *current = head;
    bool finded = false;
    if(head == NULL) {
        printf("EMPTY\n\n");
    }
    else{
        while(current != NULL){
            if(strcmp(current->data.name, name) == 0){
                finded = true;
                break;
            }
            current = current->next;
        }
    }
    if(finded == false){
        printf("Nome n%co encontrado!\n", 198);
    }
    else{
        printf("idade: %d anos\n", getPatientAge(current->data.birthDay));
        printf("ultima consulta: %d dias atr%cs\n", daysFromDate(current->data.lastConsultation), 160);
    }
}

void option3(FILE *file){
    struct node *current = head;
    while(current != NULL){
        fwrite(current->data.name, 1, strlen(current->data.name), file);
        if(current->next != NULL){
            fwrite("\n", 1, 1, file);
        }
        current = current->next;
    }
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
    //extração dos dados do arquivo de pacientes
    char name[60];
    char sex[2];
    char birthDay[11];
    char lastConsultation[11];
    patient newPatient;
    while(1){
        char *nextLine = readFileLine(inputFile, 150);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "<%[^,], %1[MF], %10[0-9/], %10[0-9/]>", name, sex, birthDay, lastConsultation);
        newPatient = createPatient(name, sex, birthDay, lastConsultation);
        addNode(newPatient);
    }
    fclose(inputFile);
    //funcionamento do software
    int option = 0;
    do{
        option = 0;
        printf("1 - Adicionar novo paciente\n");
        printf("2 - Pesquisar nome (retorna idade e dias desde ultima consulta)\n");
        printf("3 - Sair\n");
        printf("OQUE DESEJA FAZER? ");
        scanf("%d", &option);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //descuga o C por conta de usar o gets mais a frente
        printf("\n");
        switch(option){
            case 1:
                option1();
                break;
            case 2:
                option2();
                break;
            case 3:
                azsortList();
                option3(outputFileAZ);
                zasortList();
                option3(outputFileZA);
                printf("AT%c LOGO!", 144);
                break;
            default:
                printf("OP%c%cO N%cO EXISTE!\n", 128, 199, 199);
        }
        printf("\n");
    }while(option != 3);
    //fecha arquivos
    fclose(outputFileAZ);
    fclose(outputFileZA);
    return 0;
}