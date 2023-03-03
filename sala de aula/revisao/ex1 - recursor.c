#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int pot(uint64_t base, uint64_t exp){
    uint64_t value = base;
    for(int i = 0; i < exp; i++){
        printf("funcao pot chamada com %d, %d e %d\n", base, exp, value);
        value = value*base;
    }
    return value;
}

int main(){
    printf("2^5 = %d", pot(2, 6));
    return 0;  
}