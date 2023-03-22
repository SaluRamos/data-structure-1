//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char state[20];
    char city[30];
    char street[30];
} address;

typedef struct{
    char name[60];
    address adrs;
    int salary;
    char civilState[20];
    int age;
    char sex[1];
} employee;

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

address createAddress(char *street, char *city, char *state){
    address newAddress;
    strcpy(newAddress.street, street);
    strcpy(newAddress.city, city);
    strcpy(newAddress.state, state);
    return newAddress;
}

employee createEmployee(char *name, address adrs, int salary, char *civilState, int age, char *sex){
    employee newEmployee;
    strcpy(newEmployee.name, name);
    newEmployee.adrs = adrs;
    newEmployee.salary = salary;
    strcpy(newEmployee.civilState, civilState);
    newEmployee.age = age;
    strcpy(newEmployee.sex, sex);
    return newEmployee;
}

void printEmployee(employee slave) {
    printf("{%s; {%s; %s; %s} ; %d; %s; %d; %s}\n", slave.name, slave.adrs.street, slave.adrs.city, slave.adrs.state, slave.salary, slave.civilState, slave.age, slave.sex);
}

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;
    if (argc > 1) {
        inputFile = fopen(strcat(argv[1], ".txt"), "r");
    } else {
        inputFile = fopen("funcionarios.txt", "r");
    }

    char name[60];
    int salary = 0;
    char civilState[20];
    int age = 0;
    char sex[2];
    char state[20];
    char city[30];
    char street[30];
    address employeeAddress;
    employee newEmployee;
    while(1){
        char *nextLine = readFileLine(inputFile, 200);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "{%[^;]; {%[^;]; %[^;]; %[^}]} ; %d; %[^;]; %d; %[^}]}", name, street, city, state, &salary, civilState, &age, sex);
        employeeAddress = createAddress(street, city, state);
        newEmployee = createEmployee(name, employeeAddress, salary, civilState, age, sex);
        printf("\n%s\n", nextLine);
        printEmployee(newEmployee);
    }




    fclose(inputFile);
    if(argc > 2){
        outputFile = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        outputFile = fopen("ARQUIVO.txt", "w+");
    }
    fclose(outputFile);
}