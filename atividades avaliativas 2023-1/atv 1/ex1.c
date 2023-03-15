//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char state[20]; //alteração: usar um array de caracteres para guardar o estado
    char city[30]; //alteração: usar um array de caracteres para guardar a cidade
    char street[30]; //alteração: usar um array de caracteres para guardar a rua
} address;

typedef struct {
    char name[60]; //alteração: usar um array de caracteres para guardar o nome
    address adrs;
    int salary;
    char civilState[20]; //alteração: usar um array de caracteres para guardar o estado civil
    int age;
    char sex[1]; //alteração: usar um array de caracteres para guardar o sexo e definir tamanho 2 para incluir o caractere de terminação de string '\0'
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

address createAddress(char *street, char *city, char *state) {
    address newAddress;
    strcpy(newAddress.street, street);
    strcpy(newAddress.city, city);
    strcpy(newAddress.state, state);
    return newAddress;
}

employee createEmployee(char *name, address adrs, int salary, char *civilState, int age, char *sex) { //alteração: corrigir o tipo do parâmetro salary de float para int
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
    printf("{%s}; {%s; %s; %s}; %d; %s; %d; %s}\n", slave.name, slave.adrs.street, slave.adrs.city, slave.adrs.state, slave.salary, slave.civilState, slave.age, slave.sex);
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
    int salary;
    char civilState[20];
    int age;
    char sex[1];
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
        //{nome; {rua; cidade; estado} ; salario ; estado civil ; idade; sexo}
        sscanf(nextLine, "{%[^;]; {%[^;]; %[^;]; %[^}]}; %[0-9]; %[^;]; %[0-9]; %1[MF]}", name, street, city, state, salary, civilState, age, sex);
        employeeAddress = createAddress(street, city, state);
        newEmployee = createEmployee(name, employeeAddress, salary, civilState, age, sex);
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