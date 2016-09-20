/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Node Struct
 * A and B represent next and previous, not in any particular order
 * types can be:
 * * d: dummy
 * * a: atom
 * * s: sentinel
 */
typedef struct Node Node;

struct Node{
    double value;
    char type;
    Node *A;
    Node *B;
};

typedef struct List List;

typedef struct List{
    Node *head;
    Node *tail;
} List;

/**
 * Initialize current list with 2 dummies and return its head
 * 
 * @param List* list
 *
 * @return List* list
 */
List *initList(List *list);

/**
 * free current list memory
 * 
 * @param List* list
 * @param int value
 */
void destroyList(List *list, int length);

/**
 * print list
 * 
 * @param List* list
 */
void printList(List *list);

/**
 * create atom node
 * 
 * @param double vale
 */
Node *createAtom(double value);

/**
 * insert node into list
 * 
 * @param List* list
 * @param Node* node
     * @param int pos - where to insert
 */
void insertNode(List *list, Node node, int pos);

/**
 *
 */
int main(){
    List *list;
    initList(list);

    char cmd = ' ';
    do{
        scanf("%c", &cmd);
        switch(cmd){
            case 'i':
                int pos;
                double value;
                
                insertNode(list, createAtom(value), pos);
                break;
            case 'p':
                
                break;
            case 'v':
                
                break;
        }
    }while(cmd != 't');
    
    printList(list);

    return 0;
}

/**
 * Functions
 */

List *initList(List *list){
    Node head = malloc(sizeof(struct Node));
    head->type = 'd';
    
    Node tail = malloc(sizeof(struct Node));
    tail->type = 'd';
    
    list = malloc(sizeof(struct List));
    list->head = head;
    list->tail = tail;
    list->head->B = tail;
    list->head->A = head;
    
    return list_head;
}

void destroyList(List *list){
    int i;
    Node *prev = list->head;
    Node *cur = prev->A == NULL ? prev->B : prev->A;
    while(cur != NULL){
        Node *aux = cur;
        cur = (cur->A == prev) ? cur->B : cur->A;
        free(prev);
        prev = aux;
    }
    free(prev);
}

void printList(List *list){
    int i;
    Node *prev = NULL;
    Node *cur = list->head;
    while(cur != NULL){
        Node *aux = cur;
        cur = (cur->A == prev) ? cur->B : cur->A;
        prev = aux;
        print("->%d", cur->value);
    }
    free(prev);
}

Node *createAtom(double value){
    Node *node = malloc(sizeof(struct Node));
    node->type = 'a';
    node->value = value;
    return node;
}

void insertNode(List *list, Node *node, int pos){
    int i;
    Node *prev = NULL;
    Node *cur = list->head;
    for(i = 0; i <= pos; i++){
        Node *aux = cur;
        cur = cur->A == prev ? cur->B : cur->A;
        prev = aux;
    }
    node->A = prev;
    node->B = cur;

    if(prev->A == cur){
        prev->A = node;
    }else{
        prev->B = node;
    }

    if(cur->A == prev){
        cur->A = node;
    }else{
        cur->B = node;
    }
}
