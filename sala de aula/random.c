#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//e2e tested
void initializeRandom(){
    srand(time(NULL));
}

//e2e tested
int randInt(int min, int max){
    int r = 0;
    if(max < min){
        r = (rand() % (min-max+1)) + max;
    }else{
        r = (rand() % (max-min+1)) + min;
    }
    return r;
}

//e2e tested
double rand01(){
    return (rand() % 10001) / 10000.0;
}

double randDouble(double min, double max){
    return (rand01()*(max-min))+min;
}

//e2e tested
double randNormalDistribution(int iterators){
    double x = 0;
    for(int i = 0; i < iterators; i++){
        x += rand01();
    }
    return x/iterators;
}