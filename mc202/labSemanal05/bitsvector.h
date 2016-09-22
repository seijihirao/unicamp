/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

#ifndef BITSVECTOR
#define BITSVECTOR
#define CHAR_BIT 8

#define BITSLOT(i) ((i-1) / CHAR_BIT)
#define BITMASK(i) (1 << ((i-1) % CHAR_BIT))

typedef struct ByteVector{
    unsigned char *value;
    unsigned long int length;
} ByteVector;

/**
 * Create a bit vector
 * 
 * @param int size - vector size in bits
 *
 * @return bits vector
 */
ByteVector *create(int size);

/**
 * Add a number to the bit vector
 *
 * @param ByteVector *bits_vector
 * @param int number - number to be added
 *
 * @return 1 if added, 0 if not
 */
short add(ByteVector *bits_vector, int number);


/**
 * Removes a number from the bit vector
 *
 * @param ByteVector *bits_vector
 * @param int number - number to be removed
 *
 * @return 1 if removed, 0 if not
 */
short rem(ByteVector *bits_vector, int number);

/**
 * Checks if the number is inside the vector
 *
 * @param ByteVector *bits_vector
 * @param int number - number to check if exists
 *
 * @return 1 if present, 0 if not
 */
short isIn(ByteVector *bits_vector, int number);

/**
 * Gets count of numbers inside lower than selected number
 *
 * @param ByteVector *bits_vector
 * @param int number - number to select
 *
 * @return count of numbers lower than selected
 */
short rank(ByteVector *bits_vector, int number);

/**
 * selects i-nth present number
 *
 * @param ByteVector *bits_vector
 * @param int pos - i
 *
 * @return i-nth number
 */
int sel(ByteVector *bits_vector, int pos);

/**
 * Count number of present elements in the interval
 *
 * @param ByteVector *bits_vector
 * @param int start
 * @param int end
 *
 * @return number count
 */
int rangecount(ByteVector *bits_vector, int start, int end);

/**
 * Prints to stdout current bits vector
 * `S = {i,j,k,...}`
 *
 * @param ByteVector *bits_vector
 */
void print(ByteVector *bits_vector);

/**
 * Destroy current bits vector
 *
 * @param ByteVector *bits_vector
 */
void destroy(ByteVector *bits_vector);

# endif
