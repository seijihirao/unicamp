/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Obligatory String
 */
#define STRING_SIZE 1000
typedef char String[STRING_SIZE];

/**
 * Node object used in tree
 *
 * @prop int value
 * @prop Node *left
 * @prop Node *right
 */
typedef struct Node Node;

struct Node{
    int value;
    Node *left;
    Node *right;
};

/**
 * Construct tree from its pre-order and in-order vectors.
 *
 * @return Node - constructed tree object's root
 */
Node *constructTree(String pre_order, String in_order, int in_order_start, int in_order_end, int *pre_order_index);

/**
 * Print tree's post-order
 * 
 * @param Node *node
 */
void printPostOrder(Node *node);

/**
 * Print tree in width-order
 *
 * @param Node *node
 * @param int size - number of elements on tree
 */
void printWidthOrder(Node *node, int size);

/**
 * Destroy tree to free up memory
 * 
 * @param Node *node
 */
void destroyTree(Node *node);
