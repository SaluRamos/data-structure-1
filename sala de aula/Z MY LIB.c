#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeRandom(){
    srand(time(NULL));
}

int randInt(int min, int max){
    int r = 0;
    if(max < min){
        r = (rand() % (min-max+1)) + max;
    }else{
        r = (rand() % (max-min+1)) + min;
    }
    return r;
}

double rand01(){
    return (rand() % 10001) / 10000.0;
}

double randDouble(double min, double max){
    return (rand01()*(max-min))+min;
}

double randNormalDistribution(int iterators){
    double x = 0;
    for(int i = 0; i < iterators; i++){
        x += rand01();
    }
    return x/iterators;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;
    if(!orig || !rep){
        return NULL;
    }
    len_rep = strlen(rep);
    if(len_rep == 0){
        return NULL;
    }
    if(!with){
        with = "";
    }
    len_with = strlen(with);
    ins = orig;
    for(count = 0; tmp = strstr(ins, rep); ++count){
        ins = tmp + len_rep;
    }
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if(!result){
        return NULL;
    }
    while(count--){
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}
