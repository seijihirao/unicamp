/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 68501

typedef struct{
    long key;
    long value;
} Hash;

/**
 * Hash algorithm 1
 * 
 * @param long number
 *
 * @returns int - hashed number
 */
int sh1(long number);

/**
 * Hash algorithm 2
 * 
 * @param long number
 *
 * @returns int - hashed number
 */
int sh2(long number);

/**
 * Initializate hash with empty values
 *
 * @returns Hash hashtable
 */
Hash *hash_init(int size);

/**
 * Insert value with key on hash
 *
 * @param Hash* hashtable
 * @param long key
 * @param long value
 *
 * @returns short status
 * * 1 if success
 * * 0 if already exists
 * * -1 if couldn't add
 */
short hash_insert(Hash *hashtable, long key, long value);

/**
 * Finds value by key in hash
 *
 * @param Hash* hashtable
 * @param long key
 * @param long* value - value will be set here
 *
 * @returns short status
 * * 1 if success
 * * 0 if doesn't exists
 */
short hash_find(Hash *hashtable, long key, long *value);

/**
 * Removes node by key in hash
 *
 * @param Hash* hashtable
 * @param long key
 *
 * @returns short status
 * * 1 if success
 * * 0 if doesn't exists
 */
short hash_remove(Hash *hashtable, long key);

/**
 * Frees hash table from memory
 * 
 * @param Hash* hash
 */
void hash_destroy(Hash *hashtable);

