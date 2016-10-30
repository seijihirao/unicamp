/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

/**
 * Manipulate a hash structure 
 * with the following commands:
 *
 * * insert [i %d %d]
 * * find [b %d]
 * * remove [r %d]
 * * finish [f]
 */
int main(){
    Hash *hashtable = hash_init(MAX_LENGTH);

    char cmd;
    do{
        scanf("%c", &cmd);
        if(cmd == 'i'){
            long key, value;
            scanf("%ld %ld", &key, &value);
            
            hash_insert(hashtable, key, value);
        }else if(cmd == 'b'){
            long key, value;
            scanf("%ld", &key);
                
            if(!hash_find(hashtable, key, &value)){
                printf("%ld nao existe\n", key);
            }else {
                printf("valor para %ld: %ld\n", key, value);
            }
        }else if(cmd == 'r'){
            long key;
            scanf("%ld", &key);
            
            if(!hash_remove(hashtable, key)){
                printf("%ld nao existe\n", key);
            }
        }
    }while(cmd != 'f');
    
    hash_destroy(hashtable);

    return 0;
}
