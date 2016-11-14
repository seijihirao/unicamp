/**
 * NOME:RODRIGO SEIJI PIUBELI HIRAO
 * RA: 186837
 */

typedef struct{
    int key;
    int weight;
} Heap;

typedef struct{
    Heap *heap;
    int *augmented;
} AugmentedHeap;

/**
 * Inserts a key and weight to the heap
 */
short insert(AugmentedHeah *heap, int key, int weight);


