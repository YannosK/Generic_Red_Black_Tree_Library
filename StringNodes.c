#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "StringNodes.h"

// #define NDEBUG
#include <assert.h>

/****************************************************************************************************************************************************************/
// STRUCT DEFINITIONS
/****************************************************************************************************************************************************************/

typedef struct stringStruct *stringKey;
struct stringStruct
{
    char *stringKeyValue;
};

/****************************************************************************************************************************************************************/
// PUBLIC FUNCTIONS
/****************************************************************************************************************************************************************/

void *string_createkey(char *input_key, size_t key_size)
{
    char *keyValue = (char *)malloc(key_size);
    if (keyValue == NULL)
        return NULL;

    stringKey key = (stringKey)malloc(sizeof(struct stringStruct));
    if (key == NULL)
        return NULL;

    key->stringKeyValue = keyValue;

    return (void *)key;
}
