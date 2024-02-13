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
    A function where a key is inputed and it finds a node that has such a key
    It uses a temporary key to find the key we want
    It is responsible to free the memory of the temporary key (using destroykey)


    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    key         : a (void) pointer to the struct that holds a key.
    compare     : a pointer to a function that compares keys to see if key1 > key2, taking pointers to their structs as inputs
    equal       : a pointer to a function that compares keys to see if they are equal, taking pointers to their structs as inputs
    destroykey  : a pointer to a function that destroys the container of the inserted key, to avoid memory leaks

    Returns:
    NULL if no equal key was found
    the pointer to the node struct it found
*/
void *rbt_nodefind(handler tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key));

/*
    Prints information of a node of a tree
    It is used to work in conjunction with rbt_nodefind

    Arguments:
    nd          : a pointer to the node struct (returned by rbt_nodefind)
    keyprinter  : a pointer to a function that can print the key of the node, based on the key type (use the same as rbt_nodefind)

    Returns:
    0 if executed correctly
    1 if the pointer to the node entered was NULL (which means rbt_keyfind found no equal key)
*/
int rbt_nodeprint(const void *nd, void (*keyprinter)(const void *key));

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
    delnode     : a (void) pointer to the node struct we wish to delete
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
int rbt_delete(handler *tree, void *delnode, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key));

/*
    Prints the entire Red-Black Tree

    Arguments:
    tree        : a pointer to the sentinel struct of the tree
    keyprinter  : a pointer to a function that can print the key of the node, based on the key type

    Returns:
    0 if executed correctly
*/
int rbt_print(handler tree, void (*keyprinter)(const void *key));

#endif