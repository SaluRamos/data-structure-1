#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    FILE *inputFile;
    FILE *outputFileAZ, *outputFileZA;
    if(argc > 1){
        inputFile = fopen(strcat(argv[1], ".txt"), "r");
    }else{
        inputFile = fopen("pacientes.txt", "r");
    }



    return 0;
}