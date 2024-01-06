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
    returns 2 when the sentinel memory allocation fails
    returns 3 when there is a broken pointer
    returns 4 when the tree is empty (root == NULL)
*/
int rbt_delete(int key);

// /*
//     Red-Black Tree Recursive Print

//     returns 0 if executed correctly
//     returns 1 if we add a null node with no subtree
// */
// int rbt_print(node x, int level);

// /*
//     Checks if the subtree rooted in the inserted node is a RBT

//     returns the (positive) number of black nodes if it is a RBT
//     returns -1 if a node is neither red nor black
//     returns -2 if the root is not black or if it hasn't got a NULL parent
//     returns -3 if a red node does not have NULL or black children
//     returns -4 if a path to NULL has more or less black nodes than the other paths
//     returns -5 if the tree is empty
// */
// int util_rbt_selfcheck(node r, int blacks, int nill_blacks);

#endif