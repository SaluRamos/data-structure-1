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
