/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

#include "bitsvector.h"

ByteVector *create(int size){
    ByteVector *bits_vector;
    bits_vector = malloc(sizeof(struct ByteVector));
    bits_vector->value = calloc((size/CHAR_BIT)+1, 1);
    bits_vector->length = size;
    return bits_vector;
}

short add(ByteVector *bits_vector, int number){
    if(number < 1 || number > bits_vector->length) return 0;

    bits_vector->value[BITSLOT(number)] |= BITMASK(number);
    return 1;
}

short rem(ByteVector *bits_vector, int number){
    if(number < 1 || number > bits_vector->length) return 0;
    
    bits_vector->value[BITSLOT(number)] &= (~BITMASK(number));
    return (isIn(bits_vector, number)) ? 1 : 0;
}

short isIn(ByteVector *bits_vector, int number){
    unsigned int slot = BITSLOT(number);
    unsigned char mask = BITMASK(number);
    
    return bits_vector->value[slot] & mask;
}

short rank(ByteVector *bits_vector, int number){
    if(number < 1 || number > bits_vector->length) return -1;

    return rangecount(bits_vector, 1, number);    
}

int sel(ByteVector *bits_vector, int pos){
    if(pos < 1 || pos > bits_vector->length) return -1;

    int i, cont = 0;
    for(i = 1; cont != pos; i++){
        if(isIn(bits_vector, i)){
            cont++;
        }
        if(i > bits_vector->length){
            return 0;
        }
    }
    return i-1;
}

int rangecount(ByteVector *bits_vector, int start, int end){
    if(start < 1 || start > bits_vector->length) return -1;
    if(end < 1 || end > bits_vector->length) return -1;

    int i, cont = 0;
    for(i = start; i <= end; i++){
        if(isIn(bits_vector, i)){
            cont++;
        }
    }
    return cont;
}

void print(ByteVector *bits_vector){
    unsigned long int i;
    unsigned long int printed = 0;
    printf("S = {");
    for(i = 1; i <= bits_vector->length; i++){
        if(isIn(bits_vector, i)){
            printf("%lu", i);
            printed++;
            if(printed != rangecount(bits_vector, 1, bits_vector->length)){
                printf(",");
            }
        }
    }
    printf("}\n");
}

void destroy(ByteVector *bits_vector){
    if(bits_vector != NULL){
        free(bits_vector->value);
        free(bits_vector);
    }
}

