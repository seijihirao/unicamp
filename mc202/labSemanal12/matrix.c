/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include "matrix.h"

Coordinate *matrix_init(int length){
    Coordinate *matrix = malloc(length * sizeof(Coordinate));

    int i;
    for(i = 0; i < length; i++){
        matrix[i].line = -1;
        matrix[i].column = -1;
    }

    return matrix;
}

void matrix_add(Coordinate *matrix, int line, int column, int value){
    int i;
    for(i = 0;; i++){
        if(matrix[i].line == -1 && matrix[i].column == -1){
            matrix[i].line = line;
            matrix[i].column = column;
            matrix[i].value = value;
            break;
        }else if(matrix[i].line == line && matrix[i].column == column){
            matrix[i].value = value;
            break;
        }
    }
}

int matrix_compare(const void *a, const void *b){
    int line1 = ((const Coordinate*)a)->line;
    int column1 = ((const Coordinate*)a)->column;
    int line2 = ((const Coordinate*)b)->line;
    int column2 = ((const Coordinate*)b)->column;
    
    if(line1 < line2
    || (line1 == line2 && column1 < column2)){
        return -1;
    }
    if(line1 == line2 && column1 == column2){
        return 0;
    }
    if(line1 > line2
    || (line1 == line2 && column1 > column2)){
        return 1;
    }
    
    return 0;
}
	
CSR *matrix_toCSR(Coordinate *matrix, int num_coordinates){
    qsort(matrix, num_coordinates, sizeof(Coordinate), matrix_compare);
    
    CSR *csr = malloc(sizeof(CSR));
    csr->values_length = num_coordinates;
    csr->lines_length = matrix[num_coordinates-1].line + 1;
    csr->values = malloc(num_coordinates * sizeof(int));
    csr->line_pos = malloc(num_coordinates * sizeof(int));
    csr->line_cont = calloc(csr->lines_length, sizeof(int));

    int i;
    for(i = 0; i < num_coordinates; i++){
        csr->values[i] = matrix[i].value;
        csr->line_pos[i] = matrix[i].column;
        csr->line_cont[matrix[i].line]++;
        
    }
    for(i = 1; i < csr->lines_length; i++){
        csr->line_cont[i] += csr->line_cont[i-1];
    }
    
    return csr;
}

int matrix_get(CSR *csr, int line, int column){
    if(line > csr->lines_length){
        return 0;
    }
    int i;
    for(i = csr->line_cont[line-1]; i < csr->line_cont[line]; i++){
        if(csr->line_pos[i] == column){
            return csr->values[i];
        }
    }
    return 0;
}

void matrix_destroyCSR(CSR *csr){
    free(csr->values);
    free(csr->line_pos);
    free(csr->line_cont);
    free(csr);
}

void matrix_destroy(Coordinate *matrix){
    free(matrix);
}
