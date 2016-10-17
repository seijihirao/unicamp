/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

Node *tree_init(int value){
    Node *tree = malloc(sizeof(Node));
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

short tree_add(Node *node, int value){
    //empty node/tree
    if(!node){
        return -1;
    }

    //it should be right
    if(value > node->value){
        //found position
        if(!(node->right)){
            Node *new_node = malloc(sizeof(Node));
            if(!new_node){
                return -2; // no memory
            }
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->value = value;

            node->right = new_node;
            return 0; // success
        }
        //go right
        else{
            return tree_add(node->right, value);
        }
    }
    //it should be left
    else if(value < node->value){
        //found position
        if(!(node->left)){
            Node *new_node = malloc(sizeof(Node));
            if(!new_node){
                return -2; //no memory
            }
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->value = value;

            node->left = new_node;
            return 0; // success
        }
        //go left
        else{
            return tree_add(node->left, value);
        }
    }

    return -3; // already exists
}

Node *tree_remove(Node *node, int value){
    if(!node){
        return NULL; // don't exists
    }
    // go right
    if(value > node->value){
        node->right = tree_remove(node->right, value);
    }
    //go left
    else if(value < node->value){
        node->left = tree_remove(node->left, value);
    }
    //found!
    else{
        // 2 childs
        if(node->left && node->right){
            Node *max = tree_max(node->left);
            node->value = max->value;
            node->left = tree_remove(node->left, max->value);
        }
        // 1 child
        else if(node->left || node->right){
            if(node->left){
                Node *aux = node->left;
                free(node);
                node = aux;
            }
            else if(node->right){
                Node *aux = node->right;
                free(node);
                node = aux;
            }
        }
        // no child
        else{
            free(node);
            node = NULL;
        }
    }
    
    return node;
}

Node *tree_search(Node *node, int value){
    if(!node){
        return NULL; // don't exists
    }
    // go right
    if(value > node->value){
        return tree_search(node->right, value);
    }
    //go left
    else if(value < node->value){
        return tree_search(node->left, value);
    }
    
    return node; // found!
}

Node *tree_min(Node *node){
    if(!node){
        return NULL;
    }
    if(!(node->left)){
        return node;
    }
    return tree_min(node->left);
}

Node *tree_max(Node *node){
    if(!node){
        return NULL;
    }
    if(!(node->right)){
        return node;
    }
    return tree_max(node->right);
}

int tree_length(Node *node){
    if(!node){
        return 0;
    }
    return tree_length(node->left) + tree_length(node->right) + 1;
}

short printPostOrder(Node *node){
    if(!node){
        return -1;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    printf("%d ", node->value);
    return 0;
}

short printInOrder(Node *node){
    if(!node){
        return -1;
    }
    printInOrder(node->left);
    printf("%d ", node->value);
    printInOrder(node->right);
    return 0;
}

short printPreOrder(Node *node){
    if(!node){
        return -1;
    }
    printf("%d ", node->value);
    printPreOrder(node->left);
    printPreOrder(node->right);
    return 0;
}

short printWidthOrder(Node *node){
    if(!node){
        return -1;
    }
    int size = tree_length(node);
    Node **queue = malloc(size * sizeof(Node *));
    int start = 0, end = 1;
    queue[0] = node;
    Node *aux;
    for(start = 0; start < size; start++){
        aux = queue[start];
        printf("%d ", aux->value);
        if(aux->left){
            queue[end++] = aux->left;
        }
        if(aux->right){
            queue[end++] = aux->right;
        }
    }
    free(queue);
    return 0;
}

void tree_destroy(Node *node){
    if(!node){
        return;
    }
    tree_destroy(node->left);
    tree_destroy(node->right);

    free(node);
}

