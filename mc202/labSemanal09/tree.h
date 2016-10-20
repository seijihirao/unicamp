/**
 * NOME: RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Edge Edge;

/**
 * Node object used in tree
 *
 * @prop int value
 * @prop Edge *left
 * @prop Edge *right
 */
struct Node{
    int value;
    Edge *left;
    Edge *right;
};

/**
 * Edge with weight object used in tree
 *
 * @prop int value
 * @prop Node *node
 */
struct Edge{
    float value;
    Node *node;
};


/**
 * Mount weighed tree from std scan
 *
 * @returns Node *tree
 */
Node *tree_mount();

/**
 *  Find larger weight from tree
 *
 * @params Node *tree
 *
 * @returns int max_weight
 */
float tree_maxWeight(Node *tree);

/**
 *  frees tree space on memory
 *
 * @params Node *tree
 */
void tree_destroy(Node *tree);

