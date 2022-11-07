#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define FNV_PRIME 1099511628211UL

typedef struct hashobj{
    int data;
    uint32_t hash;
    char key[100];
    struct hashobj *next;
} HashObject;

typedef struct hashtable{
    struct hashobj values[100];
    unsigned long seed;
} HashTable;

HashTable createHashTable(unsigned long seed){
    struct hashtable newHashTable;
    newHashTable.seed = seed;
    return newHashTable;
}

static uint64_t fnv1a(struct hashtable *table, const char* key) {
    uint64_t hash = table->seed;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

int appendHashTable(struct hashtable *table, char *key, int data){
    uint64_t generatedHash = fnv1a(table, key);
    int appendIndex = generatedHash%table->seed;
    // struct hashobj newHashObject;
    // newHashObject.data = data;
    // newHashObject.hash = generatedHash;
    // strcpy(newHashObject.key, key);
    // if(table->values[appendIndex] == NULL){
    //     table->values[appendIndex] = newHashObject;
    // }
    return appendIndex;
}


int main(){

    struct hashtable table = createHashTable(16);
    // int values[12] = {100, 40, 6, 0, 17, 15, 4, 25, 63, 48, 96, 2};
    
    printf("teste = %d\n", appendHashTable(&table, "bar", 100));
    printf("teste = %d\n", appendHashTable(&table, "bar", 100));
    printf("teste = %d\n", appendHashTable(&table, "foo", 100));
    printf("teste = %d\n", appendHashTable(&table, "foo", 100));

}