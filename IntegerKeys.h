#ifndef IntegerKeys
#define IntegerKeys

/*
    Creates a key of type int and returns a pointer to its struct, as a void pointer
    Returns NULL if memory allocation fails
*/
void *int_createkey(int input_key);

/*
    Destroys a struct that holds an int key using a (void) pointer to it
*/
void int_destroykey(void *key);

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

    The format has a newline in the end:
    printf("%d\n", ...);
*/
void int_print(const void *key);

#endif