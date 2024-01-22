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
    size_t stringKeySize;
};

/****************************************************************************************************************************************************************/
// PUBLIC FUNCTIONS
/****************************************************************************************************************************************************************/

void *string_createkey(char *input_key, size_t key_size)
{
    char *key_value = (char *)malloc(sizeof(char) * key_size);
    if (key_value == NULL)
        return NULL;

    stringKey key = (stringKey)malloc(sizeof(struct stringStruct));
    if (key == NULL)
        return NULL;

    key->stringKeyValue = key_value;
    key->stringKeySize = key_size;

    return (void *)key;
}

void string_destroykey(void *key)
{
    assert(key != NULL);

    stringKey dead = (stringKey)key;
    char *dead_value = dead->stringKeyValue;

    free(dead_value);
    free(dead);
}

size_t string_size(void)
{
    size_t stringKeySize = sizeof(struct stringStruct);
    return stringKeySize;
}

int string_compare(const void *op1, const void *op2)
{
    assert(op1 != NULL && op2 != NULL);

    stringKey str1 = (stringKey)op1;
    stringKey str2 = (stringKey)op2;

    char *s1 = str1->stringKeyValue;
    char *s2 = str2->stringKeyValue;

    if (strcmp(s1, s2) < 0)
        return 1;
    else
        return 0;
}

int string_equal(const void *op1, const void *op2)
{
    assert(op1 != NULL && op2 != NULL);

    stringKey str1 = (stringKey)op1;
    stringKey str2 = (stringKey)op2;

    char *s1 = str1->stringKeyValue;
    char *s2 = str2->stringKeyValue;

    if (strcmp(s1, s2) == 0)
        return 1;
    else
        return 0;
}

void string_print(const void *key)
{
    assert(key != NULL);

    printf("%s", ((stringKey)key)->stringKeyValue);
    return;
}
