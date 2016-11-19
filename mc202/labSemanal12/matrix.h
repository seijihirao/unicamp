/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Matrix Coordinate
 *
 * @property int line
 * @property int column
 * @property int value
 */
typedef struct{
    int line;
    int column;
    int value;
} Coordinate;

/**
 * Matrix CSR
 * 
 * @property *values - vector of values
 * @property *line_pos - value column 
 * @property *line_cont - number of elements per line 
 */
typedef struct{
    int *values;
    int *line_pos;
    int *line_cont;
    int values_length;
    int lines_length;
} CSR;

/**
 * Initializate matrix coordinate list on memory
 *
 * @param int length
 *
 * @returns Coordinate *matrix - pointer to doordinate list
 */ 
Coordinate *matrix_init(int length);

/**
 * Adds coordinate to matrix
 *
 * @param Coordinate *matrix - coordinates vector
 * @param int line
 * @param int column
 * @param int value
 */
void matrix_add(Coordinate *matrix, int line, int column, int value);

/**
 * Compare 2 matrix coordinates
 *
 * @param const void *a
 * @param const void *b
 *
 * @returns int result
 * * -1 if b is larger
 * * 0 if both are the same
 * * +1 if a is larger
 */
int matrix_compare(const void *a, const void *b);

/**
 * Converts Matrix Coordinates to CSR
 *
 * @param Coordinate *matrix
 * @param int num_coordinates
 */
CSR *matrix_toCSR(Coordinate *matrix, int num_coordinates);

/**
 * Gets a value from a sparse matrix
 * 
 * @param CSR *csr
 * @param int line
 * @param int column
 *
 * @returns int value
 */
int matrix_get(CSR *csr, int line, int column);

/**
 * Frees matrix from memory
 *
 * @param CSR *csr
 */
void matrix_destroyCSR(CSR *csr);

/**
 * Frees matrix from memory
 *
 * @param Coordinate *matrix
 */
void matrix_destroy(Coordinate *matrix);
