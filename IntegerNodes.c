#include <stdio.h>
#include <stdlib.h>
#include "IntegerNodes.h"

/****************************************************************************************************************************************************************/
// STRUCT DEFINITIONS
/****************************************************************************************************************************************************************/

typedef struct intStruct *intKey;
struct intStruct
{
    int intKeyValue;
};

/****************************************************************************************************************************************************************/
// PUBLIC FUNCTIONS
/****************************************************************************************************************************************************************/

void *int_createkey(int input_key)
{
    intKey key = (intKey)malloc(sizeof(struct intStruct));
    if (key == NULL)
        return NULL;
    key->intKeyValue = input_key;
    return (void *)key;
}

void int_destroykey(void *key)
{
    intKey dead = (intKey)key;
    free(key);
}

size_t int_size(void)
{
    size_t intKeySize = sizeof(struct intStruct);
    return intKeySize;
}

int int_compare(const void *op1, const void *op2)
{
    if (((intKey)op1)->intKeyValue > ((intKey)op2)->intKeyValue)
        return 1;
    else
        return 0;
}

int int_equal(const void *op1, const void *op2)
{
    if (((intKey)op1)->intKeyValue == ((intKey)op2)->intKeyValue)
        return 1;
    else
        return 0;
}

void int_print(const void *key)
{
    printf("%d", ((intKey)key)->intKeyValue);
    return;
}