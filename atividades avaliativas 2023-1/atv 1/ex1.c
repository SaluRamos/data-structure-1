//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    char* state;
    char* city;
    char* street;
} address;



typedef struct{
    char* name;
    address adrs; //endereço, address
    float salary;
    char* civilState;
    int age;
    char* sex; //M ou F
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



address createAddress(char* street,char* city, char* state){
    address newAddress;
    strcpy(newAddress.street, street);
    strcpy(newAddress.city, city);
    strcpy(newAddress.state, state);
    return newAddress;
}


employee createEmployee(char* name, address adrs, float salary, char* civilState, int age, char* sex){
    employee newEmployee;
    strcpy(newEmployee.name, name);
    newEmployee.adrs = adrs;
    newEmployee.salary = salary;
    strcpy(newEmployee.civilState, civilState);
    newEmployee.age = age;
    newEmployee.sex = sex;
    // strcpy(newEmployee.sex, sex);
    return newEmployee;
}

void printEmployee(employee slave){
    //{nome; {rua; cidade; estado} ; salario ; estado civil ; idade; sexo}
    printf("{%s}; {%s; %s; %s}; %f; %s; %d; %c}\n", slave.name, slave.adrs.street, slave.adrs.city, slave.adrs.state, slave.salary, slave.civilState, slave.age, slave.sex);
}

int main(int argc, char *argv[]){
    FILE *inputFile;
    FILE *outputFile; //ordem decrescente
    if(argc > 1){
        inputFile = fopen(strcat(argv[1], ".txt"), "r");
    }else{
        inputFile = fopen("funcionarios.txt", "r");
    }





    char name[60];
    float salary;
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
        employeeAddress = createAddress(&street, &city, &state);
        newEmployee = createEmployee(&name, employeeAddress, salary, &civilState, age, &sex);
        printEmployee(newEmployee);
        // addNode(newEmployee);
    }




    fclose(inputFile);
    if(argc > 2){
        outputFile = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        outputFile = fopen("ARQUIVO.txt", "w+");
    }
    fclose(outputFile);
}