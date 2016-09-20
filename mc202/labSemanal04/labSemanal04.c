/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/**
 * Remove all white spaces before and after the string 
 */
char *trim(char *str);

/**
 * Manipulate a queue of string based on the selected commands
 * * unshift {string} - adds a string to the start of the queue
 * * shift - removes the first element of the queue
 * * print-first - std prints first element of the queue
 * * push {string} - adds a string to the end of the queue
 * * pop - removes the last element of the queue
 * * print-last - std prints last element of the queue
 * * is-empty - prints 'yep' if is empty, 'nope' if not
 * * exit
 */
int main(){
	setbuf(stdout, NULL);	

    char cmd[12];
    Queue *queue = malloc(sizeof(queue));
    queue->i = 0;
    queue->length = 0;
    queue->max_length = 1;
    queue->value = malloc(sizeof(char *));
    do{
        scanf("%s", cmd);
        if(strcmp(cmd, "unshift") == 0){
            char buffer[5000];
            scanf("%[^\n]s", buffer);
            unshift(queue, trim(buffer));
        }else if(strcmp(cmd, "shift") == 0){
            shift(queue);        
        }else if(strcmp(cmd, "print-first") == 0){
            printFirst(queue);
        }else if(strcmp(cmd, "push") == 0){
            char buffer[5000];
            scanf("%[^\n]s", buffer);
            push(queue, trim(buffer));
        }else if(strcmp(cmd, "pop") == 0){
            pop(queue);
        }else if(strcmp(cmd, "print-last") == 0){
            printLast(queue);
        }else if(strcmp(cmd, "is-empty") == 0){
            if(isEmpty(queue) == 1){
                printf("yep\n");
            }else{
                printf("nope\n");
            }
        }
    }while(strcmp(cmd, "exit") != 0);
	
	free(queue->value);
	free(queue);	

    return 0;
}

/**
 * Functions
 */

char *trim(char *str){
    char *end;
    
    // Trim leading space
    while(*str == ' ') str++;
    
    if(*str != 0){
		// Trim trailing space
		end = str + strlen(str) - 1;
		while(end > str && *end == ' ') end--;
		
		// Write new null terminator
		*(end+1) = 0;
	}

    return str;
}
