/**
 * NOME: RODRIGO SEIJI PIUBELI HIRAO
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
 * Initializate tree with a value
 * 
 * @param int value
 *
 * @return pointer to tree
 */
Node *tree_init(int value);

/**
 * Adds node to tree
 * 
 * @param Node *node
 * @param int value
 *
 * @returns short added:
 * * 0 if added
 * * -1 if tree is empty (error)
 * * -2 if memory is full (error)
 * * -3 if element already exists (error)
 */
short tree_add(Node *node, int value);

/**
 * Removes node to tree
 * 
 * @param Node *node
 * @param int value
 *
 * @returns short removed:
 * * pointer to tree root if removed
 * * NULL if element does not exists
 */
Node *tree_remove(Node *node, int value);

/**
 * Searches if node exists in tree
 * 
 * @param Node *node
 * @param int value
 *
 * @returns short found:
 * * pointer if found
 * * NULL if element does not exists
 */
Node *tree_search(Node *node, int value);

/**
 * Gets minimum value from tree
 * 
 * @param Node *node
 *
 * @returns Node *minimum
 */
Node *tree_min(Node *node);

/**
 * Gets maximum value from tree
 * 
 * @param Node *node
 *
 * @returns Node *maximum
 */
Node *tree_max(Node *node);

/**
 * Gets number of nodes in a tree
 * 
 * @param Node *node
 *
 * @returns int length
 */
int tree_length(Node *node);

/**
 * Print tree's post-order
 * 
 * @param Node *node
 *
 * @returns short printed:
 * * 0 if printed
 * * -1 if tree is empty (error)
 */
short printPostOrder(Node *node);

/**
 * Print tree's in-order
 * 
 * @param Node *node
 *
 * @returns short printed:
 * * 0 if printed
 * * -1 if tree is empty (error)
 */
short printInOrder(Node *node);

/**
 * Print tree's pre-order
 * 
 * @param Node *node
 *
 * @returns short printed:
 * * 0 if printed
 * * -1 if tree is empty (error)
 */
short printPreOrder(Node *node);

/**
 * Print tree in width-order
 *
 * @param Node *node
 * @param int size - number of elements on tree
 *
 * @returns short printed:
 * * 0 if printed
 * * -1 if tree is empty (error)
 */
short printWidthOrder(Node *node);

/**
 * Destroy tree to free up memory
 * 
 * @param Node *node
 */
void tree_destroy(Node *node);
