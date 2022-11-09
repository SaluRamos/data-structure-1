#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define FNV_PRIME 1099511628211UL

typedef struct hashobj{
    int data;
    uint32_t hash;
    char key[100];
    struct hashobj *next;
} HashObject;

typedef struct hashtable{
    struct hashobj *values;
    uint64_t seed;
} HashTable;

HashTable createHashTable(uint64_t seed){
    struct hashtable newHashTable;
    newHashTable.seed = seed;
    newHashTable.values = (struct hashobj *) malloc(seed*sizeof(struct hashobj));
    for(int i = 0; i < seed; i++){
        struct hashobj newHashObject;
        newHashObject.data = -1;
        newHashObject.hash = NULL;
        strcpy(newHashObject.key, "");
        newHashObject.next = NULL;
        newHashTable.values[i] = newHashObject;
    }
    return newHashTable;
}

//algoritmos de hash
//para fazer buscas o ideal é não possuir colisões nem agrupamentos e ser rápido
//os algoritmos mais famosos para busca são: Flajolet-Martin, HyperLogLog

uint64_t fnv1a(struct hashtable *table, const char* key) {
    uint64_t hash = table->seed;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

uint64_t appendHashTable(struct hashtable *table, char *key, int data){
    uint64_t generatedHash = fnv1a(table, key);
    uint64_t appendIndex = generatedHash%table->seed;

    struct hashobj newHashObject;
    newHashObject.data = data;
    newHashObject.hash = generatedHash;
    strcpy(newHashObject.key, key);
    newHashObject.next = NULL;

    struct hashobj *appendLocal = table->values[appendIndex];

    while(1){
        if(appendLocal->next == NULL){
            appendLocal = newHashObject;
            break;
        }else{
            appendLocal = appendLocal->next;
        }
    };
    
    return appendIndex;
}



int main(){
    struct hashtable table = createHashTable(200);
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "a", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "b", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "aa", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "bb", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "aaa", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "bbb", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "aaaa", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "bbbb", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "aaaaa", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "testeloko", 100, 0));
    printf("teste = %" PRIu64 "\n", appendHashTable(&table, "saluu", 100, 0));
}