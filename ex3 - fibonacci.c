#include <stdio.h>
#include <stdlib.h>

//17 de agosto de 2022

int fibonacci(int n){
    if(n < 2){
        return n;
    }
    else{
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(void){
    int n = 0;
    printf("Informe a posicao do numero da sequencia de fibonacci: ");
    scanf("%d", &n);
    printf("resultado = %d", fibonacci(n));
    return 1;
}