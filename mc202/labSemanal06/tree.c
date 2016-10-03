/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

Node *constructTree(String pre_order, String in_order, int in_order_start, int in_order_end, int *pre_order_index){
    // this node doesn't exist
    if(in_order_start > in_order_end){
        return NULL;
    }
    
    // gets in order index
    char value = pre_order[*pre_order_index];
    int in_order_index;
    for(in_order_index = 0; in_order_index < strlen(in_order); in_order_index++){
        if(in_order[in_order_index] == value){
            break;
        }
    }

    // create node
    Node *node = malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    (*pre_order_index)++;
    // node has no children
    if(in_order_start == in_order_end){
        return node;
    }
    node->left = constructTree(pre_order, in_order, in_order_start, in_order_index - 1, pre_order_index);
    node->right = constructTree(pre_order, in_order, in_order_index + 1, in_order_end, pre_order_index);

    return node;
}

void printTree(Node *node){
    if(!node){
        return;
    }
    printTree(node->left);
    printTree(node->right);

    printf("%c", node->value);
}

void destroyTree(Node *node){
    if(!node){
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);

    free(node);
}

