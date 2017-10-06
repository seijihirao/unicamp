#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <ctype.h>

/**
 * ERROR JUMP VARIABLES
 */
static jmp_buf error_mount;
static jmp_buf error_var;

/**
 * List Struct
 */
typedef struct List List;
struct List{
    char *key;
    float value;
    List *next;
};

/**
 * Add to list key and value
 *
 * @param List *list - list head, where element will be inserted
 * @param char *key
 * @param float value
 */
void list_add(List *list, char *key, float value);

/**
 * Get value from list 
 *
 * @param List *list - list head, where element will be inserted
 * @param char *key
 *
 * @return float value
 */
float list_get(List *list, char *key);

/**
 * Helper function to print list
 *
 * @param List *list - list head
 */
void list_print(List *list);

/**
 * Binary Object Struct
 */
typedef struct Bin Bin;
struct Bin{
    int line;
    char data_left[8];
    char data_right[8];
    Bin *next;
};

/**
 * Add to list key and value
 *
 * @param List *bin - binary object head, where element will be inserted
 * @param int line
 * @param char *data
 */
void binary_add_word(Bin *bin, List *list, float line, char *data);

/**
 * Add to list key and value
 *
 * @param List *bin - binary object head, where element will be inserted
 * @param int line
 * @param char *data
 */
void binary_add(Bin *bin, List *list, float line, int cmd, char *data);

/**
 * Helper function to print list
 *
 * @param List *list - list head
 */
void binary_print(Bin *bin);

/**
 * Get number of lines to add based on current line
 *
 * @param int cur_list - current line
 *
 * @return float - number of lines to add
 */
float get_num_lines(int cur_line);

/* Retorna:
 *  1 caso haja erro na montagem; 
 *  0 caso não haja erro.
 */
int emitirMapaDeMemoria() {
    // Create dictionary of instructions
    List *instructions = malloc(sizeof(struct List));
    instructions->key = "";
    instructions->value = 0;
    instructions->next = NULL;
    list_add(instructions, "LOAD",  0x01);
    list_add(instructions, "LOAD-", 0x02);
    list_add(instructions, "LOAD|", 0x03);
    list_add(instructions, "LOADmq", 0x0A);
    list_add(instructions, "LOADmq_mx", 0x09);
    list_add(instructions, "STOR", 0x21);
    list_add(instructions, "JUMP", 0x0D);
    list_add(instructions, "JMP+", 0x0F);
    list_add(instructions, "ADD", 0x05);
    list_add(instructions, "ADD|", 0x07);
    list_add(instructions, "SUB", 0x06);
    list_add(instructions, "SUB|", 0x08);
    list_add(instructions, "MUL", 0x0B);
    list_add(instructions, "DIV", 0x0C);
    list_add(instructions, "LSH", 0x14);
    list_add(instructions, "RSH", 0x15);
    list_add(instructions, "STORA", 0x12);


    List *list = malloc(sizeof(struct List));
    list->key = "";
    list->value = 0;
    list->next = NULL;
    int num_tokens = getNumberOfTokens();    

    /*
     * Reading rotules first
     */ 
    float cp = 0.0f;
    for(unsigned int i = 0; i < num_tokens; i++){
        //get line
        cp += get_num_lines(i);

        Token token = recuperaToken(i);

        //rotule found
        if(token.tipo == 2){
            token.palavra[strlen(token.palavra)-1] = '\0';
            list_add(list, token.palavra, cp);
        }

        //.set found
        else if(token.tipo == 5){
            Token token_prev = recuperaToken(i-1);
            if(token_prev.tipo == 1 && !strcmp(token_prev.palavra, ".set")) {
                Token token_next = recuperaToken(i+1);
                list_add(list, token.palavra, atoi(token_next.palavra));
            }
        }
    }
    
    /*
     * Mounting binary Object
     */
    Bin *bin = malloc(sizeof(struct Bin));
    bin->line = 0;
    bin->next = NULL;

    cp = 0;
    for(unsigned int i = 0; i < num_tokens; i++){
        //get line
        cp += get_num_lines(i);

        Token token = recuperaToken(i);
        
        //Instruction
        if(token.tipo == 0){
            // jump instructions can be sent to right instead of left
            if(!strcmp("JUMP", token.palavra) ||
                !strcmp("JMP+", token.palavra) ||
                !strcmp("STORA", token.palavra)){
                Token token_value = recuperaToken(i+1);
                
                int right_jump = ((int)cp == cp) ? 0 : 1;
                
                binary_add(bin, list, cp, 
                    (int)list_get(instructions, token.palavra) + right_jump, 
                    token_value.palavra);
            }
            
            // bit shift operations do not need param
            else if(!strcmp("LSH", token.palavra) ||
                !strcmp("RSH", token.palavra)){
                binary_add(bin, list, cp, 
                    (int)list_get(instructions, token.palavra), 
                    "0");
            }

            // everything else is ok
            else{
                Token token_value = recuperaToken(i+1);
                binary_add(bin, list, cp, 
                    (int)list_get(instructions, token.palavra), 
                    token_value.palavra);
            }
        
        //Directive 
        }else if(token.tipo == 1){

            // wfill
            if(!strcmp(".wfill", token.palavra)){
                Token token_num_lines = recuperaToken(i+1);
                Token token_value = recuperaToken(i+2);
                int num_lines;
                if(isalpha(token_num_lines.palavra[0])){
                    num_lines = (int)list_get(list, token_num_lines.palavra);
                }else {
                    num_lines = strtol(token_num_lines.palavra, NULL, 0);
                }
                for(int l = num_lines-1; l >= 0; l--){
                    binary_add_word(bin, list, cp-l, 
                        token_value.palavra);
                }
            }

            // word
            else if(!strcmp(".word", token.palavra)){
                Token token_value = recuperaToken(i+1);
                binary_add_word(bin, list, cp, 
                    token_value.palavra);
            }

            // org - just changes cp
            else if(!strcmp(".org", token.palavra)){
                Token token_value = recuperaToken(i+1);
                if(isalpha(token_value.palavra[0])){
                    cp = (int)list_get(list, token_value.palavra);
                }else {
                    cp = strtol(token_value.palavra, NULL, 0);
                }
            }
        }
    }
    
    // fill right if necessary
    if((int)cp != cp){
        binary_add(bin, list, cp+0.5f, 0, "0");
    }
    binary_print(bin->next);
    
    return 0;
    
    /**
     * Errors
     */ 
    setjmp(error_mount);
    fprintf(stderr, "Impossível montar o código!\n");
    return 1;
    
    setjmp(error_var);
    return 1;

}

/**
 *
 * FUNCTIONS
 *
 */

void list_add(List *list, char *key, float value) {
    while(list->next) {
        list = list->next;
    }
    list->next = malloc(sizeof(struct List));

    list = list->next;
    list->key = key;
    list->value = value;
    list->next = NULL;
}

float list_get(List *list, char *key) {
    while(list->next) {
        list = list->next;
        if(!strcmp(list->key, key)){
            return list->value;
        }
    }
    fprintf(stderr, "USADO MAS NÃO DEFINIDO: %s!\n", key);
    longjmp(error_var, 0);
    return 0.0f;
}

void list_print(List *list) {
    if(!list) {
        return;
    }
    while(list) {
        printf("%s: %.1f\n", list->key, list->value);
        list = list->next;
    }
}

void binary_add_word(Bin *bin, List *list, float line, char *data) {
    int int_data = 0;
    if(isalpha(data[0])){
        int_data = (int)list_get(list, data);
    }else {
        int_data = strtol(data, NULL, 0);
    }
    
    char *binary_data = malloc(11*sizeof(char));
    snprintf(binary_data, 11, "%010X", int_data);
    binary_data[10] = '\0';

    short is_set = 0;
    while(bin->next) {
        if(bin->line == (int)line){
            is_set = 1;
            break;
        }
        bin = bin->next;
    }
    bin->next = malloc(sizeof(struct Bin));
    
    bin = bin->next;
    bin->line = (int)line-1;
    char cmd[3];
    char value[4];
    
    // left
    strncpy(cmd, binary_data, 2);
    cmd[2] = '\0';
    binary_data += 2;
    strncpy(value, binary_data, 3);
    value[3] = '\0';
    snprintf(bin->data_left, 7, "%s %s", cmd, value);
    bin->data_left[7] = '\0';
    
    // right
    binary_data += 3;
    strncpy(cmd, binary_data, 2);
    cmd[2] = '\0';
    binary_data += 2;
    strncpy(value, binary_data, 3);
    value[3] = '\0';
    snprintf(bin->data_right, 7, "%s %s", cmd, value);
    bin->data_right[7] = '\0';

    if(!is_set){
        bin->next = NULL;
    }
}

void binary_add(Bin *bin, List *list, float line, int cmd, char *data) {
    int int_data = 0;
    if(isalpha(data[0])){
        int_data = list_get(list, data);
    }else {
        int_data = strtol(data, NULL, 0);
    }
    char binary_data[7];
    sprintf(binary_data, "%02X %03X", cmd, int_data);
    binary_data[6] = '\0';
    

    short is_set = 0;
    while(bin->next) {
        bin = bin->next;
        if(((int)line != line && bin->line == (int)line) ||
            ((int)line == line && bin->line == (int)line-1)){
            is_set = 1;
            break;
        }
    }
    if(!is_set){
        bin->next = malloc(sizeof(struct Bin));
        bin = bin->next;
        bin->next = NULL;
    }
    if((int)line != line){
        bin->line = (int)line;
        strncpy(bin->data_left, binary_data, 7);
        bin->data_left[8] = '\0';
    }else{
        bin->line = (int)line-1;
        strncpy(bin->data_right, binary_data, 7);
        bin->data_right[8] = '\0';
    }
}

void binary_print(Bin *bin) {
    if(!bin) {
        return;
    }
    while(bin) {
        printf("%03X %s %s\n", bin->line, bin->data_left, bin->data_right);
        bin = bin->next;
    }
}

float get_num_lines(int cur_line){
    Token token = recuperaToken(cur_line);

    float cp = 0.0f;
    if(token.tipo == 0){
        cp += 0.5f;
    }else if(token.tipo == 1){
        if(!strcmp(".org", token.palavra)){
            Token token_next = recuperaToken(cur_line+1);
            cp = atoi(token_next.palavra);
        }
        else if(!strcmp(".align", token.palavra)){
            Token token_next = recuperaToken(cur_line+1);
            int align = atoi(token_next.palavra);
            cp = (int)cp - ((int)cp % align) + align;
        }
        else if(!strcmp(".wfill", token.palavra)){
            if((int)cp != cp){
                longjmp(error_mount, 0);
            }
            Token token_next = recuperaToken(cur_line+1);
            cp += atoi(token_next.palavra);
        }
        else if(!strcmp(".word", token.palavra)){
            if((int)cp != cp){
                longjmp(error_mount, 0);
            }
            cp += 1;
        }
    }
    return cp;
}
