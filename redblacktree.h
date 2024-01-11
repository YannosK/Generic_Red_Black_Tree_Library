#ifndef redblacktree
#define redblacktree

typedef struct node_struct *node;
struct node_struct
{
    unsigned int key;
    char color; // 'b' is black and 'r' is red
    node left;
    node right;
    node parent;
};

typedef struct sentinel *handler;
struct sentinel
{
    node root;
};

/*
    Red-Black Tree Node Insertion

    returns 0 if the node was added succesfully
    returns 1 when the node already exists
    returns 2 when there is no memory left on heap
*/
int rbt_insert(int key);

/*
    Red-Black Tree Node Deletion

    returns 0 if the node was deleted succesfully
    returns 1 when the node does not exist
    returns 2 when heap memory allocation fails (the sentinel was not created)
    returns 3 when there is a broken pointer
    returns 4 when the tree is empty (root == NULL)
*/
int rbt_delete(int key);

/*
    Prints the entire Red-Black Tree

    returns 0 if executed correctly
    returns 1 if the tree is empty
*/
int rbt_print(void);

/*
    Creates a new red black tree and returns a handle to the main node of it
    
    returns a pointer to the struct of the sentinel node of the red black tree
    returns NULL if memory allocation failed
*/
handler rbt_create(void);

#endif