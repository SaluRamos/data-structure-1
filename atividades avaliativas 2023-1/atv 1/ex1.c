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












//função que inverte a posição de dois elementos
void swap(employee *a, employee *b){
    employee temp = *a;
    *a = *b;
    *b = temp;
}

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(employee arr[], int N, int i){
    // Find largest among root, left child and right child
    // Initialize largest as root
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // If left child is larger than root
    if (left < N && arr[left].salary > arr[largest].salary){
        largest = left;
    }
    // If right child is larger than largest
    // so far
    if (right < N && arr[right].salary > arr[largest].salary){
        largest = right;
    }
    // Swap and continue heapifying if root is not largest
    // If largest is not root
    if (largest != i){
        swap(&arr[i], &arr[largest]);
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(employee arr[], int N){
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--){
        heapify(arr, N, i);
    }
    // Heap sort
    for (int i = N - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        // Heapify root element to get highest element at
        // root again
        heapify(arr, i, 0);
    }
}

// A utility function to print array of size n
// void printArray(int arr[], int N)
// {
//     for (int i = 0; i < N; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
// }

// Driver's code
// int main()
// {
//     int arr[] = {12, 11, 13, 5, 6, 7};
//     int N = sizeof(arr) / sizeof(arr[0]);
//     // Function call
//     heapSort(arr, N);
//     printf("Sorted array is\n");
//     printArray(arr, N);
// }
















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
    address newEmployeeAddress;
    employee newEmployee;
    employee *employees; //alocação dinamica de structs

    while(1){
        char *nextLine = readFileLine(inputFile, 200);
        if(strcmp(nextLine, "") == 0){//verifica se a linha é vazia
            break;
        }
        sscanf(nextLine, "{%59[^;]; {%29[^;]; %29[^;]; %19[^}]} ; %d; %19[^;]; %d; %1[^}]}", name, street, city, state, &salary, civilState, &age, sex);
        newEmployeeAddress = createAddress(street, city, state);
        newEmployee = createEmployee(name, newEmployeeAddress, salary, civilState, age, sex);
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