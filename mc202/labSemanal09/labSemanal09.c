/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/**
 * Reads a weighted tree in parenthesis notation
 * and prints the maximum weight
 */
int main(){
    while(getchar() != EOF){
        Node *tree = tree_mount();
        printf("%.3f\n", tree_maxWeight(tree));
        tree_destroy(tree);
        getchar();
    }
    return 0;
}
