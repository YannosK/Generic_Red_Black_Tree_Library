#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"

// #define NDEBUG
#include <assert.h>

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
// STRUCTURES TYPE DEFINES
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/

typedef struct node_struct *node;
struct node_struct
{
    void *key;
    char color; // 'b' is black and 'r' is red
    node left;
    node right;
    node parent;
};

struct sentinel
{
    node root;
};

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
// INTERNAL FUNCTIONS
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/

/*
    Left Rotation on Red-Black Tree Node

    returns 1 if successful
*/
int rotate_left(handler *tree, node *x)
{
    assert((*tree) != NULL);
    assert((*x) != NULL && (*x)->right != NULL);

    node y;

    y = (*x)->right;

    (*x)->right = y->left;
    if (y->left != NULL)
        y->left->parent = (*x);

    y->parent = (*x)->parent;
    if ((*x)->parent == NULL)
        (*tree)->root = y;
    else if ((*x) == (*x)->parent->left)
        (*x)->parent->left = y;
    else if ((*x) == (*x)->parent->right)
        (*x)->parent->right = y;
    else
        assert(0);

    y->left = (*x);
    (*x)->parent = y;

    return 1;
}

/*
    Right Rotation on Red-Black Tree Node

    returns 1 if successful
*/
int rotate_right(handler *tree, node *x)
{
    assert((*tree) != NULL);
    assert((*x) != NULL && (*x)->left != NULL);

    node y;

    y = (*x)->left;

    (*x)->left = y->right;
    if (y->right != NULL)
        y->right->parent = (*x);

    y->parent = (*x)->parent;
    if ((*x)->parent == NULL)
        (*tree)->root = y;
    else if ((*x) == (*x)->parent->left)
        (*x)->parent->left = y;
    else if ((*x) == (*x)->parent->right)
        (*x)->parent->right = y;
    else
        assert(0);

    y->right = (*x);
    (*x)->parent = y;

    return 1;
}

/*
    Fix for Red-Black Tree Insertion

    returns the number of rotations performed during the fixup
*/
int insert_fixup(handler *tree, node *x)
{
    assert((*tree) != NULL && (*x) != NULL);

    node uncle;
    node aux;
    int rr = 0;
    int rl = 0;
    int cnt = 0;

    while ((*x)->parent != NULL && (*x)->parent->color == 'r')
    {
        assert((*x)->parent->parent != NULL);
        assert((*x)->parent->parent->color == 'b');

        cnt++;

        if ((*x)->parent == (*x)->parent->parent->left)
        {
            uncle = (*x)->parent->parent->right;

            if (uncle != NULL && uncle->color == 'r')
            {
                (*x)->parent->color = 'b';
                uncle->color = 'b';
                (*x)->parent->parent->color = 'r';
                (*x) = (*x)->parent->parent;
            }
            else
            {
                if ((*x) == (*x)->parent->right)
                {
                    (*x) = (*x)->parent;
                    rl = rotate_left(tree, x) + rl;
                }
                assert((*x)->parent->parent != NULL);
                (*x)->parent->color = 'b';
                (*x)->parent->parent->color = 'r';
                aux = (*x)->parent->parent;
                rr = rotate_right(tree, &aux) + rr;
            }
        }
        else if ((*x)->parent == (*x)->parent->parent->right)
        {
            uncle = (*x)->parent->parent->left;

            if (uncle != NULL && uncle->color == 'r')
            {
                (*x)->parent->color = 'b';
                uncle->color = 'b';
                (*x)->parent->parent->color = 'r';
                (*x) = (*x)->parent->parent;
            }
            else
            {
                if ((*x) == (*x)->parent->left)
                {
                    (*x) = (*x)->parent;
                    rr = rotate_right(tree, x) + rr;
                }
                assert((*x)->parent->parent != NULL);
                (*x)->parent->color = 'b';
                (*x)->parent->parent->color = 'r';
                aux = (*x)->parent->parent;
                rl = rotate_left(tree, &aux) + rl;
            }
        }
        else
            assert(0);
    }
    (*tree)->root->color = 'b';
    return rr + rl;
}

/*
    Auxiliary of Red-Black Tree Delete

    Node t (transplant) takes node's d (soon-to-be dead) place
    returns 0 if executed correctly
    returns 1 if we inserted a node with broken pointers on the parent side
*/
int delete_transplant(handler *tree, node *d, node *t)
{
    assert((*tree) != NULL);
    assert((*d) != NULL && (*t) != NULL & (*t)->parent != NULL);

    if ((*d)->parent == NULL)
        (*tree)->root = (*t);
    else
    {
        if ((*d) == (*d)->parent->left)
            (*d)->parent->left = (*t);
        else if ((*d) == (*d)->parent->right)
            (*d)->parent->right = (*t);
        else
            return 1;
    }

    (*t)->parent = (*d)->parent;

    return 0;
}

/*
    Fix for the Red-Black Tree Delete

    returns 0 if executed correctly
    returns 1 if (*x) has broken pointers
*/
int delete_fixup(handler *tree, node *x)
{
    assert((*x) != NULL && (*tree) != NULL);

    node w, p, T;
    int flag;

    if ((*x)->right == (*x) && (*x)->left == (*x))
    {
        flag = 1;
        T = (*x);
        T->right = NULL;
        T->left = NULL;
    }
    else
        flag = 0;

    while ((*x)->color == 'b' && (*x) != (*tree)->root)
    {
        assert((*x) != NULL);
        assert((*x)->parent != NULL);

        if ((*x) == (*x)->parent->left)
        {
            w = (*x)->parent->right;

            if (w != NULL)
            {
                if (w->color == 'r')
                {
                    w->color = 'b';
                    (*x)->parent->color = 'r';
                    p = (*x)->parent;
                    rotate_left(tree, &p);
                    assert((*x) == (*x)->parent->left);
                    w = (*x)->parent->right;
                }

                if (w->color == 'b')
                {
                    if ((w->left == NULL || w->left->color == 'b') && (w->right == NULL || w->right->color == 'b'))
                    {
                        w->color = 'r';
                        (*x) = (*x)->parent;
                    }
                    else
                    {
                        if (w->right == NULL || w->right->color == 'b')
                        {
                            assert(w->left->color == 'r');
                            w->left->color = 'b';
                            w->color = 'r';
                            rotate_right(tree, &w);
                            assert((*x) == (*x)->parent->left);
                            w = (*x)->parent->right;
                        }
                        w->color = (*x)->parent->color;
                        (*x)->parent->color = 'b';
                        assert(w->right != NULL);
                        w->right->color = 'b';
                        p = (*x)->parent;
                        rotate_left(tree, &p);
                        (*x) = (*tree)->root;
                    }

                    if (w->color != 'r' && w->color != 'b')
                        assert(0);
                }
            }
            else
            {
                if ((*x)->parent != (*tree)->root)
                    assert(0);
            }
        }
        else if ((*x) == (*x)->parent->right)
        {
            w = (*x)->parent->left;

            if (w != NULL)
            {
                if (w->color == 'r')
                {
                    w->color = 'b';
                    (*x)->parent->color = 'r';
                    p = (*x)->parent;
                    rotate_right(tree, &p);
                    assert((*x) == (*x)->parent->right);
                    w = (*x)->parent->left;
                }

                if (w->color == 'b')
                {
                    if ((w->left == NULL || w->left->color == 'b') && (w->right == NULL || w->right->color == 'b'))
                    {
                        w->color = 'r';
                        (*x) = (*x)->parent;
                    }
                    else
                    {
                        if (w->left == NULL || w->left->color == 'b')
                        {
                            assert(w->right->color == 'r');
                            w->right->color = 'b';
                            w->color = 'r';
                            rotate_left(tree, &w);
                            assert((*x) == (*x)->parent->right);
                            w = (*x)->parent->left;
                        }
                        w->color = (*x)->parent->color;
                        (*x)->parent->color = 'b';
                        assert(w->left != NULL);
                        w->left->color = 'b';
                        p = (*x)->parent;
                        rotate_right(tree, &p);
                        (*x) = (*tree)->root;
                    }

                    if (w->color != 'r' && w->color != 'b')
                        assert(0);
                }
            }
            else
            {
                if ((*x)->parent != (*tree)->root)
                    assert(0);
            }
        }
        else
            assert(0);
    }

    if ((*x) != NULL)
        (*x)->color = 'b';

    if (flag == 1)
    {
        if (T->left == NULL && T->right == NULL)
        {
            if (T->parent == NULL)
                assert(0);
            else if (T == T->parent->left)
                T->parent->left = NULL;
            else if (T == T->parent->right)
                T->parent->right = NULL;

            free(T);
            return 0;
        }
        else
            assert(0);
    }

    return 0;
}

/*
    Print function that print nodes of the same level on the same vertical
    It begins from an inputed node and it prints downward recursively

    returns 0 if executed correctlywatchdog_rbt_selfcheck
    returns 1 if we input a NULL node with no subtree
*/
int print_recursive(node x, int level, void (*keyprinter)(const void *key))
{
    assert(keyprinter != NULL);

    if (x == NULL)
        return 1;
    else
    {
        level++;
        if (x->left != NULL)
            print_recursive(x->left, level, keyprinter);

        int i;
        for (i = 0; i < level; i++)
            printf("\t");
        printf("Key: ");
        keyprinter(x->key);
        for (i = 0; i < level; i++)
            printf("\t");
        printf("Color: %c\n", x->color);
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->parent == NULL)
            printf("Parent: NULL\n");
        else
        {
            printf("Parent: ");
            keyprinter(x->parent->key);
        }
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->right == NULL)
            printf("Right: NULL\n");
        else
        {
            printf("Right: ");
            keyprinter(x->right->key);
        }
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->left == NULL)
            printf("Left: NULL\n");
        else
        {
            printf("Left: ");
            keyprinter(x->left->key);
        }
        if (x->right != NULL)
            print_recursive(x->right, level, keyprinter);

        return 0;
    }
}

/*
    Checks if the subtree rooted in the inserted node is a RBT

    returns the (positive) number of black nodes if it is a RBT
    returns -1 if a node is neither red nor black
    returns -2 if the root is not black or if it hasn't got a NULL parent
    returns -3 if a red node does not have NULL or black children
    returns -4 if a path to NULL has more or less black nodes than the other paths
    returns -5 if the tree is empty
    returns -6 if the node's children have wrong key order (left child must have smaller key and right must have bigger)
*/
int watchdog_rbt_selfcheck(handler tree, node r, int blacks, int nill_blacks, int (*compare)(const void *op1, const void *op2))
{
    assert(tree != NULL && compare != NULL);
    assert(blacks >= 0 && nill_blacks >= 0);

    int rt;

    if (r == tree->root || tree->root == NULL)
    {
        if (tree->root == NULL)
            return -5;
        else
        {
            if (r->left != NULL && compare(r->key, r->left->key) != 1)
                return -6;
            if (r->right != NULL && compare(r->right->key, r->key) != 1)
                return -6;
            if (tree->root->color != 'r' && tree->root->color != 'b')
                return -1;
            else if (tree->root->color == 'r' || tree->root->parent != NULL)
                return -2;
        }
    }
    else
    {
        assert(r != NULL);

        if (r->left != NULL && compare(r->key, r->left->key) != 1)
            return -6;
        if (r->right != NULL && compare(r->right->key, r->key) != 1)
            return -6;

        if (r->color != 'r' && r->color != 'b')
            return -1;
        if (r->color == 'r')
        {
            if (!(((r->left == NULL) || (r->left->color == 'b')) && ((r->right == NULL) || (r->right->color == 'b'))))
                return -3;
        }
        else if (r->color == 'b')
            blacks++;
    }

    if (r->left == NULL && r->right == NULL)
    {
        if (nill_blacks != 0 && nill_blacks != blacks)
            return -4;
        else
        {
            nill_blacks = blacks;
            return nill_blacks;
        }
    }
    else
    {
        assert(r->left != NULL || r->right != NULL);

        if (r->left != NULL)
        {
            rt = watchdog_rbt_selfcheck(tree, r->left, blacks, nill_blacks, compare);

            if (rt < 0)
            {
                switch (rt)
                {
                case -1:
                    return -1;
                    break;
                case -2:
                    assert(0);
                    break;
                case -3:
                    return -3;
                    break;
                case -4:
                    return -4;
                    break;
                case -5:
                    assert(0);
                    break;
                case -6:
                    return -6;
                    break;
                default:
                    assert(0);
                    break;
                }
            }
            else
                nill_blacks = rt;
        }

        if (r->right != NULL)
        {
            rt = watchdog_rbt_selfcheck(tree, r->right, blacks, nill_blacks, compare);

            if (rt < 0)
            {
                switch (rt)
                {
                case -1:
                    return -1;
                    break;
                case -2:
                    assert(0);
                    break;
                case -3:
                    return -3;
                    break;
                case -4:
                    return -4;
                    break;
                case -5:
                    assert(0);
                    break;
                case -6:
                    return -6;
                    break;
                default:
                    assert(0);
                    break;
                }
            }
            else
                nill_blacks = rt;
        }

        return nill_blacks;
    }
}

/*
    Uses watchdog and creates error logs in a text file

    returns 0 if the structure is a RBT
*/
int watchdog_file_logger(handler tree, int (*compare)(const void *op1, const void *op2))
{
    assert(tree != NULL && compare != NULL);

    int rt;
    int x = 5;
    int number;
    int log_num = 0;

    rt = watchdog_rbt_selfcheck(tree, tree->root, 0, 0, compare);

    if (rt < 0)
    {
        FILE *fp;
        fp = fopen("ErrorLogs.txt", "r+");

        fseek(fp, 0, SEEK_SET);
        while (fscanf(fp, "%d", &log_num) == 1)
        {
        }
        fseek(fp, 0, SEEK_END);
        log_num++;

        fprintf(fp, "\n\nError log: %d\n\n", log_num);

        fprintf(fp, "\tThe structure is not a RBT\n");
        switch (rt)
        {
        case -1:
            fprintf(fp, "\tThere are nodes that have a wrong color (neither red nor black)\n");
            break;
        case -2:
            fprintf(fp, "\tThe root is not black or it has a parent other than NULL\n");
            break;
        case -3:
            fprintf(fp, "\tA red node has black children\n");
            break;
        case -4:
            fprintf(fp, "\tNot all paths to NULL nodes have the same number of black nodes\n");
            break;
        case -5:
            fprintf(fp, "\tThe tree is empty\n");
            break;
        case -6:
            fprintf(fp, "\tThe tree violates the binary tree property, that the right child must be larger than its parent, and the left smaller\n");
            break;
        default:
            break;
        }

        fprintf(fp, "\n\nEnd of error log: %d\n\n**************************************************************************", log_num);
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "%d", log_num);
        fseek(fp, 0, SEEK_SET);
        fclose(fp);

        perror("The data strucure is broken");
        exit(666);
    }
    else
    {
        assert(rt >= 0 && tree->root != NULL);
        return 0;
    }
}

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
// PUBLIC FUNCTIONS
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/

handler rbt_create(void)
{
    handler instance = (handler)malloc(sizeof(struct sentinel));
    if (instance == NULL)
        return NULL;

    instance->root = NULL;

    return instance;
}

int rbt_destroy(handler tree)
{
    assert(tree != NULL);

    handler aux_back, aux_next;

    if (tree->root != NULL)
        return 1;
    else
    {
        free(tree);
        return 0;
    }
}

void *rbt_nodefind(handler tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key))
{
    assert(compare != NULL && equal != NULL && destroykey != NULL);

    if (tree == NULL)
    {
        destroykey(key);
        return NULL;
    }
    else
    {
        node aux;

        aux = tree->root;
        assert(aux->key != NULL);

        while (aux != NULL)
        {
            if (equal(key, aux->key))
            {
                destroykey(key);
                return aux;
            }
            else if (compare(key, aux->key))
                aux = aux->right;
            else if (compare(aux->key, key))
                aux = aux->left;
            else
                assert(0);
        }
        destroykey(key);
        return NULL;
    }
}

int rbt_nodeprint(const void *nd, void (*keyprinter)(const void *key))
{
    assert(keyprinter != NULL);

    if (nd == NULL)
        return 1;
    else
    {
        node n = (node)nd;
        printf("\n\nKey: ");
        keyprinter(n->key);
        printf("Color: %c\n", n->color);
        if (n->parent == NULL)
            printf("Parent: NULL\n");
        else
        {
            printf("Parent: ");
            keyprinter(n->parent->key);
        }
        if (n->right == NULL)
            printf("Right: NULL\n");
        else
        {
            printf("Right: ");
            keyprinter(n->right->key);
        }
        if (n->left == NULL)
            printf("Left: NULL\n");
        else
        {
            printf("Left: ");
            keyprinter(n->left->key);
        }
        printf("\n");
        return 0;
    }
}

int rbt_insert(handler *tree, void *key, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key))
{
    assert(compare != NULL && equal != NULL && destroykey != NULL);

    if ((*tree)->root != NULL)
        watchdog_file_logger((*tree), compare);

    node aux1, aux2;
    int rot;

    aux2 = NULL;
    aux1 = (*tree)->root;
    while (aux1 != NULL)
    {
        aux2 = aux1;
        if (compare(aux1->key, key))
            aux1 = aux1->left;
        else if (compare(key, aux1->key))
            aux1 = aux1->right;
        else if (equal(key, aux1->key))
        {
            destroykey(key);
            return 1;
        }
        else
            assert(0);
    }

    node new = (node)malloc(sizeof(struct node_struct));
    if (new == NULL)
        return 2;
    new->color = 'r';
    new->key = key;
    new->parent = aux2;
    new->left = NULL;
    new->right = NULL;

    if (aux2 == NULL)
        (*tree)->root = new;
    else if (compare(aux2->key, key))
        aux2->left = new;
    else if (compare(key, aux2->key))
        aux2->right = new;
    else
        assert(0);

    rot = insert_fixup(tree, &new);

    watchdog_file_logger((*tree), compare);
    return 0;
}

int rbt_delete(handler *tree, void *delnode, int (*compare)(const void *op1, const void *op2), int (*equal)(const void *op1, const void *op2), void (*destroykey)(void *key))
{
    assert(compare != NULL && equal != NULL && destroykey != NULL);

    watchdog_file_logger((*tree), compare);

    if ((*tree)->root == NULL)
        return 4;

    node d, temp, aux, T;
    int rt;
    int flag = 0; // if it ends up 1 it means a sentinel was created, if it ends up 2 it means the root was deleted
    char og_color;

    d = (node)delnode;
    if (d != NULL)
    {
        void *key;
        key = d->key;

        og_color = d->color;

        if (d->left == NULL && d->right == NULL)
        {
            if (d->parent == NULL)
            {
                (*tree)->root = NULL;
                og_color = 'r';
                flag = 2;
            }
            else
            {
                if (og_color == 'r')
                {
                    if (d == d->parent->left)
                        d->parent->left = NULL;
                    else if (d == d->parent->right)
                        d->parent->right = NULL;
                    else
                        assert(0);
                }
                else if (og_color == 'b')
                {
                    T = (node)malloc(sizeof(struct node_struct));

                    if (T == NULL)
                        return 2;

                    flag = 1;

                    T->color = 'b';
                    T->left = T;
                    T->right = T;
                    T->parent = d->parent;

                    if (d == d->parent->left)
                        d->parent->left = T;
                    else if (d == d->parent->right)
                        d->parent->right = T;
                    else
                        assert(0);

                    temp = T;
                }
                else
                    assert(0);
            }
            destroykey(key);
            free(d);
        }
        else if (d->left == NULL && d->right != NULL)
        {
            temp = d->right;
            delete_transplant(tree, &d, &temp);
            destroykey(key);
            free(d);
        }
        else if (d->right == NULL && d->left != NULL)
        {
            temp = d->left;
            delete_transplant(tree, &d, &temp);
            destroykey(key);
            free(d);
        }
        else if (d->left != NULL && d->right != NULL)
        {
            temp = d->right;
            while (temp->left != NULL)
                temp = temp->left;

            assert(temp != NULL && temp->parent != NULL);

            og_color = temp->color;
            aux = temp->right;

            if (aux == NULL)
            {
                T = (node)malloc(sizeof(struct node_struct));

                if (T == NULL)
                    return 2;

                flag = 1;

                T->color = 'b';
                T->left = T;
                T->right = T;

                aux = T;
                temp->right = T;
                T->parent = temp;
            }

            delete_transplant(tree, &temp, &aux);
            temp->right = d->right;
            temp->right->parent = temp;
            assert(temp->left == NULL);

            delete_transplant(tree, &d, &temp);
            temp->left = d->left;
            assert(temp->left != NULL);
            temp->left->parent = temp;
            temp->color = d->color;

            temp = aux;

            destroykey(key);
            free(d);
        }
        else
            assert(0);

        if (og_color == 'b')
        {
            rt = delete_fixup(tree, &temp);
            watchdog_file_logger((*tree), compare);
            if (rt == 0)
                return 0;
            else if (rt == 1)
                return 3;
            else
                assert(0);
        }
        else if (og_color == 'r')
        {
            if (flag == 1)
            {
                if (T->left == T && T->right == T)
                {
                    if (T->parent == NULL)
                        assert(0);
                    else if (T == T->parent->left)
                        T->parent->left = NULL;
                    else if (T == T->parent->right)
                        T->parent->right = NULL;

                    free(T);

                    watchdog_file_logger((*tree), compare);
                    return 0;
                }
                else
                    assert(0);
            }
            else if (flag == 2)
                return 5;
            else
            {
                watchdog_file_logger((*tree), compare);
                return 0;
            }
        }
    }
    else
        return 1;
}

int rbt_print(handler tree, void (*keyprinter)(const void *key))
{
    assert(tree != NULL && keyprinter != NULL);
    return print_recursive(tree->root, 0, keyprinter);
}
