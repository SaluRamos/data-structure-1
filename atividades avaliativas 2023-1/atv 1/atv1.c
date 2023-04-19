//Salu Conteratto Ramos, RA 2150352

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define totalEmployees 10



//definição da estrutura de um endereço
typedef struct{
    char state[20];
    char city[30];
    char street[30];
} address;



//definição da estrutura de um empregado
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



//inicializa um endereço
address createAddress(char *street, char *city, char *state){
    address newAddress;
    strcpy(newAddress.street, street);
    strcpy(newAddress.city, city);
    strcpy(newAddress.state, state);
    return newAddress;
}



//inicializa um empregado
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



//função secundaria do heapSort
//altera a posição dos elementos
void swap(employee *a, employee *b){
    employee temp = *a;
    *a = *b;
    *b = temp;
}



//função secundaria do heapSort
void heapify(employee arr[], int N, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < N && arr[left].salary > arr[largest].salary){
        largest = left;
    }
    if(right < N && arr[right].salary > arr[largest].salary){
        largest = right;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}



//função principal do heapSort
void heapSort(employee arr[], int N){
    for(int i = N / 2 - 1; i >= 0; i--){
        heapify(arr, N, i);
    }
    for(int i = N - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}



int main(int argc, char *argv[]) {
    //leitura dos parametros argc e argv
    //configuração dos arquivos de entrada e saida
    FILE *inputFile;
    FILE *outputFile;
    if (argc > 1) {
        inputFile = fopen(strcat(argv[1], ".txt"), "r");
    } else {
        inputFile = fopen("funcionarios.txt", "r");
    }
    if(argc > 2){
        outputFile = fopen(strcat(argv[2], ".txt"), "w+");
    }else{
        outputFile = fopen("ARQUIVO.txt", "w+");
    }
    //declaração das variaveis para leitura dos dados
    char name[60];
    int salary = 0;
    char civilState[20];
    int age = 0;
    char sex[2];
    char state[20];
    char city[30];
    char street[30];
    address newEmployeeAddress;
    employee newEmployee;
    employee employees[totalEmployees];
    int atualLine = 0;
    //leitura dos dados
    while(1){
        char *nextLine = readFileLine(inputFile, 200);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "{%59[^;]; {%29[^;]; %29[^;]; %19[^}]} ; %d; %19[^;]; %d; %1[^}]}", name, street, city, state, &salary, civilState, &age, sex);
        newEmployeeAddress = createAddress(street, city, state);
        newEmployee = createEmployee(name, newEmployeeAddress, salary, civilState, age, sex);
        employees[atualLine] = newEmployee;
        atualLine += 1;
    }
    //ordenação dos dados
    heapSort(employees, totalEmployees);
    printf("funcionarios por ordem descrescente de salario:\n");
    for(int i = totalEmployees - 1; i >= 0; i--){
        //printa no console os funcionarios
        printf("%s, %d, %d, %s\n", employees[i].name, employees[i].salary, employees[i].age, employees[i].sex);
        //salva no arquivo de saida os funcionarios
        fprintf(outputFile, "%s, %d, %d, %s\n", employees[i].name, employees[i].salary, employees[i].age, employees[i].sex);
    }
    fclose(inputFile);
    fclose(outputFile);
}