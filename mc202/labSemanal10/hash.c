/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include "hash.h"

int sh1(long number){
    return number % MAX_LENGTH;
}

int sh2(long number){
    return 1 + (number % (MAX_LENGTH-2));
}

Hash *hash_init(int length){
    Hash *hashtable = malloc(length*sizeof(Hash));

    int i;
    for(i = 0; i < length; i++){
        hashtable[i].key = -1;
        hashtable[i].value = 0;
    }
    
    return hashtable;
}

short hash_insert(Hash *hashtable, long key, long value){
    int hash_key = sh1(key);
    long init_key = hashtable[hash_key].key;
    do{
        if(hashtable[hash_key].key == -1 
        || hashtable[hash_key].key == -2){
            hashtable[hash_key].key = key;
            hashtable[hash_key].value = value;
            return 1;    
        }
        else if(hashtable[hash_key].key == key){
            hashtable[hash_key].key = key;
            hashtable[hash_key].value = value;
            return 0;
        }
        hash_key = sh1(hash_key + sh2(key));
    }while(init_key != hashtable[hash_key].key);
    return -1; 
}

short hash_find(Hash *hashtable, long key, long *value){
    int hash_key = sh1(key);
    long init_key = hashtable[hash_key].key;
    do{
        if(hashtable[hash_key].key == -1){
            return 0;
        }
        else if(hashtable[hash_key].key == key){
            *value = hashtable[hash_key].value;
            return 1;
        }
        hash_key = sh1(hash_key + sh2(key));
    }while(init_key != hashtable[hash_key].key);

    return 0;
}

short hash_remove(Hash *hashtable, long key){
    int hash_key = sh1(key);
    long init_key = hashtable[hash_key].key;
    
    do{
        if(hashtable[hash_key].key == -1){
            return 0;
        }
        else if(hashtable[hash_key].key == key){
            hashtable[hash_key].key = -2;
            return 1;
        }
        hash_key = sh1(hash_key + sh2(key));
    }while(init_key != hashtable[hash_key].key);

    return 0;
}

void hash_destroy(Hash *hashtable){
    free(hashtable);
}
