#ifndef IntegerNodes
#define IntegerNodes

/*
    Creates a key of type int a returns a pointer to its struct, as a void pointer
    Returns NULL if memory allocation fails
*/
void *int_createkey(int input_key);

/*
    Returns the size of the integer key struct (basically the size of int key)
*/
size_t int_size(void);

/*
    A function that compares two integer keys

    Arguments:
    op1 : first opperand is a pointer to a struct of integer key, as a void pointer
    op2 : second opperand is a pointer to a struct of integer key, as a void pointer

    Returns:
    1 if op1 > op2
    0 if op2 >= op1
*/
int int_compare(const void *op1, const void *op2);

/*
    A function that compares two integer keys to see if they are equals

    Arguments:
    op1 : first opperand is a pointer to a struct of integer key, as a void pointer
    op2 : second opperand is a pointer to a struct of integer key, as a void pointer

    Returns:
    1 if op1 == op2
    0 if op2 != op1
*/
int int_equal(const void *op1, const void *op2);

/*
    A function that prints the key to the standard output
    It takes as an argument a (void) pointer to the key struct

    The format is plain, without newlines or tabs:
    printf("%d", ...);
*/
void int_print(const void *key);

#endif