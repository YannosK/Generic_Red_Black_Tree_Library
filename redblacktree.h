#ifndef redblacktree
#define redblacktree

/*
    Creates a new red-black tree

    returns the ID number of the red-black tree it created
    returns 0 if memory allocation failed
*/
unsigned int rbt_create(void);

/*
    Destroys a red-black tree using its ID
*/
unsigned int rbt_destroy(unsigned int tree_id);

/*
    Red-Black Tree Node Insertion

    returns 0 if the node was added succesfully
    returns 1 when the node already exists
    returns 2 when there is no memory left on heap
*/
int rbt_insert(unsigned int tree_id, unsigned int key);

/*
    Red-Black Tree Node Deletion

    returns 0 if the node was deleted succesfully
    returns 1 when the node does not exist
    returns 2 when heap memory allocation fails (the sentinel was not created)
    returns 3 when there is a broken pointer
    returns 4 when the tree is empty (root == NULL)
*/
int rbt_delete(unsigned int tree_id, unsigned int key);

/*
    Returns an array of integers with the IDs of all the created trees

        WARNING:
        the ouput is a pointer to a heap structure
        after you use the ouput ofthe function copy it immidiately and free the memory

    returns NULL when no tree was ever created
    returns a pointer to a heap allocated array of integers that are the IDs of the trees. Last one will always be zero and not have to do with the tree
*/
int *rbt_show(void);

/*
    Prints the entire Red-Black Tree

    returns 0 if executed correctly
    returns 1 if the tree is empty
*/
int rbt_print(unsigned int tree_id);

#endif