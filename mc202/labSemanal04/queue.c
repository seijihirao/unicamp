/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

void enlarge(Queue *queue){
    queue->max_length = queue->max_length * 2;
    char **new_queue = malloc(queue->max_length * sizeof(char *));

    int last_pos = queue->i + queue->length;
    if(last_pos == queue->max_length) last_pos -= queue->max_length;
    
    int i;
    for(i = 0; i < queue->length; i++){
        int old_pos = queue->i + i;
        if(old_pos >= queue->length) old_pos -= queue->length;

        new_queue[i] = queue->value[old_pos];
    }
	free(queue->value);

    queue->i = 0;
    queue->value = new_queue;
}

void printFirst(Queue *queue){
    if(queue->length == 0) return;

    printf("%s\n", queue->value[queue->i]);
}

void printLast(Queue *queue){
    if(queue->length == 0) return;

    int cur_pos = queue->i + queue->length - 1;
    if(cur_pos >= queue->max_length) cur_pos -= queue->max_length;
    printf("%s\n", queue->value[cur_pos]);
}

void push(Queue *queue, char *value){
    if(queue->length == queue->max_length)
        enlarge(queue);
    
    int cur_pos = queue->i + queue->length;
    if(cur_pos >= queue->max_length) cur_pos -= queue->max_length;
    queue->value[cur_pos] = malloc((strlen(value)+1) * sizeof(char));
    strcpy(queue->value[cur_pos], value);
    
    queue->length++;
}

void pop(Queue *queue){
    if(queue->length == 0) return;
    
    int cur_pos = queue->i + queue->length - 1;
    if(cur_pos >= queue->max_length) cur_pos -= queue->max_length;

    free(queue->value[cur_pos]);
    queue->length--;
}

void unshift(Queue *queue, char *value){
    if(queue->length == queue->max_length){
        enlarge(queue);
    }

    int cur_pos = queue->i - 1;
    if(cur_pos < 0) cur_pos = queue->max_length - 1;
    queue->value[cur_pos] = malloc((strlen(value)+1) * sizeof(char));
    strcpy(queue->value[cur_pos], value);

    queue->i = cur_pos;
    queue->length++;
}

void shift(Queue *queue){
    if(queue->length == 0) return;
    
    int cur_pos = queue->i + 1;
    if(cur_pos == queue->max_length) cur_pos = 0;
   	
	free(queue->value[queue->i]);
    queue->i = cur_pos;
    queue->length--;
}

short isEmpty(Queue *queue){
    if(queue->length == 0)
        return 1;
    else
        return 0;
}
