/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitsvector.h"

/**
 * Operate with bits vectors.
 * Possible operations are:
 * * create n
 * * add i
 * * remove i
 * * in i
 * * rank i
 * * select i
 * * rangecount j k
 * * print
 * * exit
 */
int main(){
    ByteVector *vector;
    char cmd[11];    
    do{
        scanf(" %s", cmd);
        if(strcmp(cmd, "create") == 0){
            int number = 0;
            scanf("%d", &number);
            destroy(vector);
            vector = create(number);
        }
        else if(strcmp(cmd, "add") == 0){
            int number = 0;
            scanf("%d", &number);
            
            add(vector, number);
        }
        else if(strcmp(cmd, "remove") == 0){
            int number = 0;
            scanf("%d", &number);

            rem(vector, number);
        }
        else if(strcmp(cmd, "in") == 0){
            int number = 0;
            scanf("%d", &number);
    
            printf("belongs(%d) = %s\n", number, (isIn(vector, number) ? "true" : "false"));
        }
        else if(strcmp(cmd, "rank") == 0){
            int number = 0;
            scanf("%d", &number);
    
            int result = rank(vector, number);

            if(result >= 0){
                printf("rank(%d) = %d\n", number, result);
            }
        }
        else if(strcmp(cmd, "select") == 0){
            int pos = 0;
            scanf("%d", &pos);
            
            int result = sel(vector, pos);
            
            if(result >= 0){
                printf("select(%d) = %d\n", pos, result);
            }
        }
        else if(strcmp(cmd, "rangecount") == 0){
            int start = 0, end = 0;
            scanf("%d", &start);
            scanf("%d", &end);
            
            int result = rangecount(vector, start, end);

            if(result >= 0){
                printf("rangecount(%d,%d) = %d\n", start, end, result);
            }
        }
        else if(strcmp(cmd, "print") == 0){
            print(vector);
        }
    }while(strcmp(cmd, "exit") != 0);
    
    destroy(vector);
    
    return 0;
}
