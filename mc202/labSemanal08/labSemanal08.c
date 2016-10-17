/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

/**
 * Operate through a tree.
 * Possible operations are:
 * * inserir x
 * * excluir x
 * * buscar x
 * * minimo
 * * maximo
 * * pos-ordem
 * * em-ordem
 * * pre-ordem
 * * largura
 * * terminar
 */
int main(){
    Node *tree;

    char cmd[10];
    do{
        scanf(" %s", cmd);
        if(strcmp(cmd, "inserir") == 0){
            int value;
            scanf("%d", &value);
            
            short result = tree_add(tree, value);
            if(result == -1){
                tree = tree_init(value);
            }
            else if(result == -2){
                printf("memoria insuficiente");
            }
            
        }
        else if(strcmp(cmd, "excluir") == 0){
            int value;
            scanf("%d", &value);
            
            tree = tree_remove(tree, value);
        }
        else if(strcmp(cmd, "buscar") == 0){
            int value;
            scanf("%d", &value);
            
            Node *result = tree_search(tree, value);
            if(!result){
                printf("nao pertence\n");
            }else{
                printf("pertence\n");
            }
        }
        else if(strcmp(cmd, "minimo") == 0){
            Node *min = tree_min(tree);
            if(min){
                printf("%d", min->value);
            }else{
                printf("vazia");
            }
            printf("\n");
        }
        else if(strcmp(cmd, "maximo") == 0){
            Node *max = tree_max(tree);
            if(max){
                printf("%d", max->value);
            }else{
                printf("vazia");
            }
            printf("\n");
        }
        else if(strcmp(cmd, "pos-ordem") == 0){
            if(printPostOrder(tree)){
                printf("vazia");
            }
            printf("\n");
        }
        else if(strcmp(cmd, "em-ordem") == 0){
            if(printInOrder(tree)){
                printf("vazia");
            }
            printf("\n");
        }
        else if(strcmp(cmd, "pre-ordem") == 0){
            if(printPreOrder(tree)){
                printf("vazia");
            }
            printf("\n");
        }
        else if(strcmp(cmd, "largura") == 0){
            if(printWidthOrder(tree)){
                printf("vazia");
            }
            printf("\n");
        }
    }while(strcmp(cmd, "terminar") != 0);
    tree_destroy(tree);
    return 0;
}
