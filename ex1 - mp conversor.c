#include <stdio.h>
#include <stdlib.h>

//15 de agosto de 2022

void converter(float milhas, float *km_p, float *mps_p){
    float c1 = 1.609;
    float c2 = 3.6;
    printf("milhas = %f\n", milhas);
    *km_p = milhas*c1;
    *mps_p = *km_p/c2;
}

int main(void){
    float milhas = 2;
    float km = 0;
    float mps = 0;
    converter(milhas, &km, &mps);
    printf("km = %f\nmps = %f", km, mps);
    return 1;
}
