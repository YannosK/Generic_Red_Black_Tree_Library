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
    Red-Black Tree Node Insertion

    returns 0 if the node was added succesfully
    returns 1 when the node already exists
    returns 2 when there is no memory left on heap
*/
int rbt_insert(handler tree, unsigned int key);

/*
    Red-Black Tree Node Deletion

    returns 0 if the node was deleted succesfully
    returns 1 when the node does not exist
    returns 2 when heap memory allocation fails (the sentinel was not created)
    returns 3 when there is a broken pointer
    returns 4 when the tree is empty (root == NULL)
    returns 5 if the node that was just deleted was the root - used to call rbt_destroy
*/
int rbt_delete(handler tree, unsigned int key);

/*
    Prints the entire Red-Black Tree

    returns 0 if executed correctly
    returns 1 if the tree is empty
*/
int rbt_print(handler tree);

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
// TEMPORAL GENERICITY TEST FUNCTIONS
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/

int generic_int_test(void *key, size_t size, int (*compare)(const void *op1, const void *op2));

#endif