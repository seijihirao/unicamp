/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct{
    int i;
    int length;
    int max_length;
    char **value;
} Queue;

/**
 * Doubles the size of the jagged array
 * 
 * @param Queue queue
 */
void enlarge(Queue *queue);

/**
 * Prints array's first element, if array is not empty
 * 
 * @param Queue queue
 */
void printFirst(Queue *queue);

/**
 * Prints array's last element, if array is not empty
 * 
 * @param Queue queue
 */
void printLast(Queue *queue);

/**
 * Checks if array is empty
 * 
 * @param Queue queue
 *
 * @return short - 1 if is empty, 0 if not
 */
short isEmpty(Queue *queue);

/**
 * Adds an element to the start of the array
 * 
 * @param Queue queue
 * @param char *value
 */
void unshift(Queue *queue, char *value);

/**
 * Removes the first element from the array
 * 
 * @param Queue queue
 */
void shift(Queue *queue);

/**
 * Adds an element to the end of the array
 * 
 * @param Queue queue
 * @param char *value
 */
void push(Queue *queue, char *value);

/**
 * Removes the last element from the array
 * 
 * @param Queue queue
 */
void pop(Queue *queue);

#endif
