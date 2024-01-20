#include <stdlib.h>
#include "IntegerNodes.h"

/****************************************************************************************************************************************************************/
// STRUCT DEFINITIONS
/****************************************************************************************************************************************************************/

struct intStruct
{
    int intKeyValue;
};

/****************************************************************************************************************************************************************/
// PUBLIC FUNCTIONS
/****************************************************************************************************************************************************************/

intKey int_createkey(int input_key)
{
    intKey key = (intKey)malloc(sizeof(struct intStruct));
    key->intKeyValue = input_key;
    return key;
}

size_t int_size(void)
{
    size_t intKeySize = sizeof(struct intStruct);
    return intKeySize;
}

unsigned short int_compare(const intKey op1, const intKey op2)
{
    if (op1->intKeyValue > op2->intKeyValue)
        return 1;
    else
        return 0;
}