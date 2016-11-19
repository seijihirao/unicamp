/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/**
 * Read and Write (in CRS) a matrix
 */
int main(){
    int num_coordinates;
    scanf("%d", &num_coordinates);
    Coordinate *matrix = matrix_init(num_coordinates);
    
    int line, column;
    /*
     * Reads matrix coordinates
     */
    int i;
    for(i = 0; i < num_coordinates; i++){
            int value;
            scanf("%d %d %d", &line, &column, &value);
            matrix_add(matrix, line, column, value);
    }
    
    //Converting coordinates vector to CSR
    CSR *csr = matrix_toCSR(matrix, num_coordinates);
    matrix_destroy(matrix);
    
    /*
     * Writes matrix coordinates in CRS
     */ 
    scanf("%d %d", &line, &column);
    while(line != -1 && column != -1){
        printf("(%d,%d) = %d\n", 
            line, 
            column, 
            matrix_get(csr, line, column));
        scanf("%d %d", &line, &column);
    }
    
    matrix_destroyCSR(csr);
    
    return 0;
}
