#include <stdio.h>
#include <stdlib.h>
#include "IntegerNodes.h"

// #define NDEBUG
#include <assert.h>

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
    assert(key != NULL);

    intKey dead = (intKey)key;
    free(key);
}

int int_compare(const void *op1, const void *op2)
{
    assert(op1 != NULL);
    assert(op2 != NULL);

    if (((intKey)op1)->intKeyValue > ((intKey)op2)->intKeyValue)
        return 1;
    else
        return 0;
}

int int_equal(const void *op1, const void *op2)
{
    assert(op1 != NULL);
    assert(op2 != NULL);

    if (((intKey)op1)->intKeyValue == ((intKey)op2)->intKeyValue)
        return 1;
    else
        return 0;
}

void int_print(const void *key)
{
    assert(key != NULL);

    printf("%d\n", ((intKey)key)->intKeyValue);
    return;
}