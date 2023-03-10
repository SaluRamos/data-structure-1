#include <stdio.h>
#include <stdlib.h>

//17 de agosto de 2022

typedef struct
{
    int x;
    int y;
} point;

void incrementPoint(point *v){
    (*v).x = (*v).x + 1; //método 1 de acessar atributos de uma struct ponteiro
    v -> y = (v -> y) + 1; //método 2 de acessar atributos de uma struct ponteiro
}

int main(void){
    point p1;
    p1.x = 3;
    p1.y = 5;
    incrementPoint(&p1);
    printf("Coordenadas de p1: x = %d, y = %d", p1.x, p1.y);
    return 1;
}