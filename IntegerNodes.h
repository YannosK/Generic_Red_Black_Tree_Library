#ifndef IntegerNodes
#define IntegerNodes

/*
    Pointer to a struct that contains a key, of type int
*/
typedef struct intStruct *intKey;

/*
    Creates a key of type int a returns a pointer to its struct
*/
intKey int_createkey(int input_key);

/*
    Returns the size of the integer key struct (basically the size of int key)
*/
size_t int_size(void);

/*
    A function that compares two integer keys

    Arguments:
    op1 : first opperand is a pointer to a struct of integer key
    op2 : second opperand is a pointer to a struct of integer key

    Returns:
    1 if op1 > op2
    0 if op2 >= op1
*/
unsigned short int_compare(const intKey op1, const intKey op2);

#endif