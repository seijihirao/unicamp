/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/**
 * Read a series of preorder and inorder trees, 
 * and return its respoectives postorder trees.
 */
int main(){
    String pre_order, in_order;
    while(scanf(" %s", pre_order) != EOF){
        scanf(" %[^\n]s", in_order);
        Node *tree;
        int *pre_order_index = malloc(sizeof(int));
        pre_order_index[0] = 0;
        tree = constructTree(pre_order, in_order, 0, strlen(in_order)-1, pre_order_index);
        printTree(tree);
        printf("\n");
        destroyTree(tree);
        free(pre_order_index);
    }
    return 0;
}
