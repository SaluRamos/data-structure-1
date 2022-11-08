#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "md5/md5.c"

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

//algoritmos de hash
//para fazer buscas o ideal é não possuir colisões e ser rápido
//para uso de senhas é ideal ser irreversível e velocidade nem muito lenta nem muito rápida
//alguns algoritmos de hash: md4, md5, sha-1, sha-256, Whirlpool, bcrypt, argon2

uint64_t fnv1a(struct hashtable *table, const char* key) {
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

    printf("teste = %d\n", appendHashTable(&table, "a", 100));
    printf("teste = %d\n", appendHashTable(&table, "b", 100));
    printf("teste = %d\n", appendHashTable(&table, "c", 100));
    printf("teste = %d\n", appendHashTable(&table, "d", 100));
    printf("teste = %d\n", appendHashTable(&table, "e", 100));
    printf("teste = %d\n", appendHashTable(&table, "bolao", 100));
    printf("teste = %d\n", appendHashTable(&table, "salu", 100));
    printf("teste = %d\n", appendHashTable(&table, "bar", 100));
    printf("teste = %d\n", appendHashTable(&table, "foo", 100));
    printf("teste = %d\n", appendHashTable(&table, "lokao", 100));
    print_hash(md5String("teste"));
}