#ifndef StringNodes
#define StringNodes

/*
    Creates a key of type string and returns a pointer to its struct, as a void pointer
    Returns NULL if memory allocation fails

    Arguments:
    input_key   : the inputed string to be made a key
    key_size    : the size of that string - it is needed
*/
void *string_createkey(char *input_key, size_t key_size);

/*
    Destroys a struct that holds an string key using a (void) pointer to it

    It frees both the memory of the key container struct and also the memoery allocated for the string value
*/
void string_destroykey(void *key);

/*
    A function that compares two string keys.
    The comparison is alphabetical

    Arguments:
    op1 : first opperand is a pointer to a struct of string key, as a void pointer
    op2 : second opperand is a pointer to a struct of string key, as a void pointer

    Returns:
    1 if op1 > op2, which means that op1 has greated alphabetical order
    0 if op2 >= op1, which means that op1 has greated alphabetical order, or the strings are identical
*/
int string_compare(const void *op1, const void *op2);

/*
    A function that compares two string keys to see if they are equals

    Arguments:
    op1 : first opperand is a pointer to a struct of string key, as a void pointer
    op2 : second opperand is a pointer to a struct of string key, as a void pointer

    Returns:
    1 if op1 == op2
    0 if op2 != op1
*/
int string_equal(const void *op1, const void *op2);

/*
    A function that prints the key to the standard output
    It takes as an argument a (void) pointer to the key struct

    The format has a newline in the end
*/
void string_print(const void *key);

#endif