#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct{
    char *name;
    char *sex;
    char *birthDay;
    int age;
    char *lastConsultation;
    int daysSinceLastConsultation;
} patient;

//abstrai adquirir a data atual no formato "dd/mm/YYYY" ou "%d/%m/%Y"
char* getAtualDate(){
    char atualDate[11];
    time_t rawtime = time(NULL);
    struct tm *ts = localtime(&rawtime);
    strftime(atualDate, sizeof(atualDate), "%d/%m/%Y", ts);
    return atualDate;
}

int daysFromDate(char* fromDate){
    char* atualDate = getAtualDate();
    return 0;
}

int getPatientAge(char* fromDate){
    char* atualDate = getAtualDate();
    return 0;
}

patient createPatient(char *info){
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
    newPatient.age = getPatientAge(birthDay);
    newPatient.daysSinceLastConsultation = daysFromDate(lastConsultation);
    return newPatient;
}

//mostra informações de um objeto paciente
void printPatient(patient *aPatient){
    printf("NOME: '%s', SEXO: '%s', NASCIMENTO: '%s', ULTIMA CONSULTA: '%s', IDADE: '%d'\n\n, DIAS DESDE ULTIMA CONSULTA: '%d'", aPatient->name, aPatient->sex, aPatient->birthDay, aPatient->lastConsultation, aPatient->age, aPatient->daysSinceLastConsultation);
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
        patients[atualLine] = createPatient(nextLine);
        printPatient(&patients[atualLine]);
        atualLine += 1;
        Sleep(10);
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