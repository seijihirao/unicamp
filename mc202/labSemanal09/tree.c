/**
 * NOME: RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include "tree.h"

Node *mountTree(){
    char cur_char;
    scanf("%c", &cur_char);
    
    //return null node
    if(cur_char == ')'){
        return NULL;
    }
    Node *subtree = malloc(sizeof(Node));

    //left node
    Edge *left = malloc(sizeof(Edge));
    left->node = mountTree();
    subtree->left = left;
    
    //cache node and edge values to use later depending on left and right nodes
    char values[32];
    scanf("%32[^(]", values);
    scanf("%c", &cur_char);
    
    //right node
    Edge *right = malloc(sizeof(Edge));
    right->node = mountTree();
    subtree->right = right;
    
    //sets node value and edge weights
    if(left->node && right->node){
        sscanf(values, "%f:%d:%f", &left->value, &subtree->value, &right->value);
    }else if(left->node){
        sscanf(values, "%f:%d", &left->value, &subtree->value);
    }else if(right->node){
        sscanf(values, "%d:%f", &subtree->value, &right->value);
    }else{
        sscanf(values, "%d", &subtree->value);
    }
    
    scanf("%c", &cur_char);

    return subtree;    
}

float tree_maxWeight(Node *tree){
    //return 0 if tree is empty
    if(!tree){
        return 0.0f;
    }

    float left_weight = tree->left->value + tree_maxWeight(tree->left->node);
    float right_weight = tree->right->value + tree_maxWeight(tree->right->node);
    
    return (left_weight > right_weight) ? left_weight : right_weight;
}

