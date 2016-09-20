/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * List Struct
 */
typedef struct List List;

struct List{
    int value;
    int cont;
    List *next;
};

/**
 * Initialize current list with 0
 * 
 * @param List* list
 * @param int length
 *
 * @return List* list head
 */
List *initList(List *list, int length);

/**
 * free current list memory
 * 
 * @param List* list
 * @param int value
 */
void destroyList(List *list, int length);


/**
 * Faz 3 procuras em uma lista, seguindo os algoritmos `move to front`, `transpose` e `count`,
 * retornando seus custos.
 * Sendo custo a quantidade de iterações na procura do elemento da lista.
 */
int main(){
    //generic variables
    int i;

    /*
     * Input
     */
    int num_elements = 0;
    scanf("%d", &num_elements);

    int num_reads = 0;
    scanf("%d", &num_reads);
    int *reads = malloc(num_reads*sizeof(int));
    
    for(i = 0; i < num_reads; i++){
        scanf("%d", reads+i);
    }
    
    /*
     * Proccess
     */
    List *list = NULL;
    List *list_head = NULL;

    int move_to_front_cost = 0, transpose_cost = 0, count_cost = 0;
    
    /*
     * MOVE TO FRONT
     */
    list_head = initList(list, num_elements);

    for(i = 0; i < num_reads; i++){ 
        list = list_head;
        List *prev = NULL;

        for(;;){
            move_to_front_cost++;
            if(list->value == *(reads+i)){
                if(prev != NULL){
                    List *next = list->next; //auxiliar
                    list->next = list_head;
                    list_head = list;
                    prev->next = next;
                }
                break; //break é legal
            }
            prev = list;
            list = list->next;
        }
    }
    
    /*
     * TRANSPOSE
     */
    destroyList(list_head, num_elements);
    list_head = initList(list, num_elements);

    for(i = 0; i < num_reads; i++){
        list = list_head;
        List *prev = NULL;
        List *prev2 = NULL;

        for(;;){
            transpose_cost++;
            if(list->value == *(reads+i)){
                if(prev != NULL){
                    if(prev2 != NULL){
                        prev2->next = list;
                    }else{
                        list_head = list;
                    }
                    List *next = list->next; //auxiliar
                    list->next = prev;
                    prev->next = next;
                }
                break; //break é fofo
            }
            prev2 = prev;
            prev = list;
            list = list->next;
        }
    }
    
    /*
     * COUNT
     */
    destroyList(list_head, num_elements);
    list_head = initList(list, num_elements);

    for(i = 0; i < num_reads; i++){
        list = list_head;
        List *prev = NULL;
        List *last_prev = NULL;
        List *last_prev2 = NULL;
        List *not_last_prev = NULL;
        List *not_last_prev2 = NULL;
        
        for(;;){
            count_cost++;
            if(list->value == *(reads+i)){
                list->cont++;
                if(last_prev != NULL){
                    if(not_last_prev != NULL && not_last_prev->cont <= list->cont){
                        last_prev = not_last_prev;
                        last_prev2 = not_last_prev2;
                    }else if(last_prev->cont > list->cont){
                        break;
                    }

                    if(last_prev2 != NULL){
                        last_prev2->next = list;
                    }else{
                        list_head = list;
                    }
                    prev->next = list->next;
                    list->next = last_prev;
                }
                break; //break é vida
            }
            if(last_prev == NULL || list->cont < last_prev->cont){
                not_last_prev = last_prev;
                not_last_prev2 = last_prev2;
                last_prev2 = prev;
                last_prev = list;
            }
            prev = list;
            list = list->next;
        }
    }

    
    /*
     * Output
     */

    destroyList(list_head, num_elements);
    printf("%d %d %d\n", move_to_front_cost, transpose_cost, count_cost);
    return 0;
}

/**
 * Functions
 */

List *initList(List *list, int length){
    list = malloc(sizeof(struct List));
    list->value = 1;
    list->cont = 0;
    
    List *list_head = list;

    int i;
    for(i = 2; i <= length; i++){
        list->next = malloc(sizeof(struct List));
        list = list->next;
        list->value = i;
        list->cont = 0;
        list->next = NULL;
    }
    
    return list_head;
}

void destroyList(List *list, int length){
    int i;
    for(i = 1; i <= length; i++){
        List *cur = list;
        list = list->next;
        free(cur);
    }
}
