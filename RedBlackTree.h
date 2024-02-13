#ifndef RedBlackTree
#define RedBlackTree

/*
    Pointer to the sentinel structs of each red-black tree
    These structs have the definitive characteristics of the tree
*/
typedef struct sentinel *handler;

/*
    Creates a new red-black tree

    returns a pointer to the sentinel struct of the red-black tree it created
    returns NULL if memory allocation failed
*/
handler rbt_create(void);

/*
    Destroys a red-black tree

    returns 0 if it destroys a tree
    returns 1 if it did not destroy the tree, because it wasn't empty
*/
unsigned int rbt_destroy(handler tree);

/*
    A function where a key is inputed and it finds a node that has such a keyv
    It uses a temporary key to find the key we want to delete
    It is responsible to free the memory of the temporary key


    Arguments:
    tree    : a pointer to the sentinel struct of the tree
    key     : a (void) pointer to the struct that holds a key.
    compare : a pointer to a function that compares keys to see if key1 > key2, taking pointers to their structs as inputs
    equal   : a pointer to a function that compares keys to see if they are equal, taking pointers to their structs as inputs
    destroykey  : a pointer to a function that destroys the container of the inserted key, to avoid memory leaks

    Returns:
    NULL if no equal key was found
    the pointer to the key struct it found
*/
void *rbt_keyfind(handler tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key));

/*
    Red-Black Tree Node Insertion
    If the insertion fails it is responsible to free the memory allocated to the inserted key

    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    key         : a (void) pointer to the struct that holds the key that we want inserted in the new node
    compare     : a pointer to a function that compares keys to see if key1 > key2, taking pointers to their structs as inputs
    equal       : a pointer to a function that compares keys to see if they are equal, taking pointers to their structs as inputs
    destroykey  : a pointer to a function that destroys the container of the inserted key, to avoid memory leaks

    Returns:
    0 if the node was added succesfully
    1 when the node already exists
    2 when there is no memory left on heap
*/
int rbt_insert(handler *tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key));

/*
    Red-Black Tree Node Deletion
    In order to find the proper key of the node to delete, insert a temporary key with equal value with the key you wish to delete in the second argument
    It is responsible to free the memory soon-to-be-deleted node's key struct

    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    temp_key    : a (void) pointer to the struct that holds a temporary key, in order to find the actual key of the node we wish to delete
    compare     : a pointer to a function that compares keys to see if key1 > key2, taking pointers to their structs as inputs
    equal       : a pointer to a function that compares keys to see if they are equal, taking pointers to their structs as inputs
    destroykey  : a pointer to a function that destroys the container of the inserted key, to avoid memory leaks

    Returns:
    0 if the node was deleted succesfully
    1 when the node does not exist
    2 when heap memory allocation fails (the sentinel was not created)
    3 when there is a broken pointer
    4 when the tree is empty (root == NULL)
    5 if the node that was just deleted was the root - used to call rbt_destroy
*/
int rbt_delete(handler *tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key));

/*
    Prints the entire Red-Black Tree

    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    keyprinter  : a pointer to a function that can print the key of the node, based on the key type

    Returns:
    0 if executed correctly
*/
int rbt_print(handler tree, void (*keyprinter)(const void *key));

/*
    Prints the iformation of a specific node

    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    keyprinter  : a pointer to a function that can print the key of the node, based on the key type

    Returns:
    0 if executed correctly
*/
int rbt_printkey(handler tree, void (*keyprinter)(const void *key));

#endif