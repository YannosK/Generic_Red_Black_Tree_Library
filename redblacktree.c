#include <stdio.h>
#include <stdlib.h>
#include "redblacktree.h"

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
    unsigned int key;
    char color; // 'b' is black and 'r' is red
    node left;
    node right;
    node parent;
};

/*
    Pointer to the defining struct of each tree. The sentinel of the tree
    It is a member of a list that contains all the trees

    Contains:
    No          : the integer ID of the tree
    multitude   : number of all the trees, only updated on the head and the tail of the list
    root        : pointer to the root node of the tree
    n           : pointer to the next tree
    b           : pointer to the previous tree
*/
struct sentinel
{
    unsigned int No;
    unsigned int multitude;
    node root;
    handler n;
    handler b;
};

handler head_rbt_list = NULL;
handler tail_rbt_list = NULL;

/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/
// INTERNAL FUNCTIONS
/****************************************************************************************************************************************************************/
/****************************************************************************************************************************************************************/

/*
    Takes the integer ID of a tree and returns a pointer to the tree's sentinel
 */
handler tree_find(unsigned int tree_id)
{
    handler instance;

    instance = head_rbt_list;
    while (instance->No != tree_id)
    {
        instance = instance->n;
        assert(instance != NULL);
    }

    return instance;
}

/*
    Left Rotation on Red-Black Tree Node

    returns 1 if successful
*/
int rotate_left(handler *tree, node *x)
{
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
    assert((*x) != NULL);

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
        printf("\tFixup Loop Call: %d\n", cnt);

        if ((*x)->parent == (*x)->parent->parent->left)
        {
            uncle = (*x)->parent->parent->right;

            if (uncle != NULL && uncle->color == 'r')
            {
                printf("\t\tCASE 1\n");
                (*x)->parent->color = 'b';
                uncle->color = 'b';
                (*x)->parent->parent->color = 'r';
                (*x) = (*x)->parent->parent;
            }
            else
            {
                if ((*x) == (*x)->parent->right)
                {
                    printf("\t\tCASE 2\n");
                    (*x) = (*x)->parent;
                    rl = rotate_left(tree, x) + rl;
                }
                assert((*x)->parent->parent != NULL);
                printf("\t\tCASE 3\n");
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
                printf("\t\tCASE 1\n");
                (*x)->parent->color = 'b';
                uncle->color = 'b';
                (*x)->parent->parent->color = 'r';
                (*x) = (*x)->parent->parent;
            }
            else
            {
                if ((*x) == (*x)->parent->left)

                {
                    printf("\t\tCASE 2\n");
                    (*x) = (*x)->parent;
                    rr = rotate_right(tree, x) + rr;
                }
                assert((*x)->parent->parent != NULL);
                printf("\t\tCASE 3\n");
                (*x)->parent->color = 'b';
                (*x)->parent->parent->color = 'r';
                aux = (*x)->parent->parent;
                rl = rotate_left(tree, &aux) + rl;
            }
        }
        else
            assert(0);
    }
    printf("\t\tCASE 0\n");
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
    assert((*x) != NULL);

    printf("\t\tDelete fix-up invoked\n");

    node w, p, T;
    int flag;

    if ((*x)->right == (*x) && (*x)->left == (*x))
    {
        printf("\t\tSentinel added in delete_fixup\n");
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
                    printf("\t\t\tTYPE 1\n");
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
                        printf("\t\t\tTYPE 2\n");
                        w->color = 'r';
                        (*x) = (*x)->parent;
                    }
                    else
                    {
                        if (w->right == NULL || w->right->color == 'b')
                        {
                            assert(w->left->color == 'r');
                            printf("\t\t\tTYPE 3\n");
                            w->left->color = 'b';
                            w->color = 'r';
                            rotate_right(tree, &w);
                            assert((*x) == (*x)->parent->left);
                            w = (*x)->parent->right;
                        }
                        printf("\t\t\tTYPE 4\n");
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
                printf("\t\t\tTYPE 0\n"); // sibling is null
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
                    printf("\t\t\tTYPE 1\n");
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
                        printf("\t\t\tTYPE 2\n");
                        w->color = 'r';
                        (*x) = (*x)->parent;
                    }
                    else
                    {
                        if (w->left == NULL || w->left->color == 'b')
                        {
                            assert(w->right->color == 'r');
                            printf("\t\t\tTYPE 3\n");
                            w->right->color = 'b';
                            w->color = 'r';
                            rotate_left(tree, &w);
                            assert((*x) == (*x)->parent->right);
                            w = (*x)->parent->left;
                        }
                        printf("\t\t\tTYPE 4\n");
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
                printf("\t\t\tTYPE 0\n"); // sibling is null
                if ((*x)->parent != (*tree)->root)
                    assert(0);
            }
        }
        else
            assert(0); // return 1;
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
            printf("\t\tSentinel killed by delete_fixup\n");
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
int print_recursive(node x, int level)
{
    if (x == NULL)
        return 1;
    else
    {
        level++;
        if (x->left != NULL)
            print_recursive(x->left, level);

        int i;
        for (i = 0; i < level; i++)
            printf("\t");
        printf("Key: %d\n", x->key);
        for (i = 0; i < level; i++)
            printf("\t");
        printf("Color: %c\n", x->color);
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->parent == NULL)
            printf("Parent: NULL\n");
        else
            printf("Parent: %d\n", x->parent->key);
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->right == NULL)
            printf("Right: NULL\n");
        else
            printf("Right: %d\n", x->right->key);
        for (i = 0; i < level; i++)
            printf("\t");
        if (x->left == NULL)
            printf("Left: NULL\n");
        else
            printf("Left: %d\n", x->left->key);

        if (x->right != NULL)
            print_recursive(x->right, level);

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
*/
int watchdog_rbt_selfcheck(handler tree, node r, int blacks, int nill_blacks)
{
    assert(blacks >= 0 && nill_blacks >= 0);

    int rt;

    if (r == tree->root || tree->root == NULL)
    {
        if (tree->root == NULL)
            return -5;
        else
        {
            if (tree->root->color != 'r' && tree->root->color != 'b')
                return -1;
            else if (tree->root->color == 'r' || tree->root->parent != NULL)
                return -2;
        }
    }
    else
    {
        assert(r != NULL);

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
            rt = watchdog_rbt_selfcheck(tree, r->left, blacks, nill_blacks);

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
                case -5:
                    assert(0);
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
            rt = watchdog_rbt_selfcheck(tree, r->right, blacks, nill_blacks);

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
                case -5:
                    assert(0);
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
int watchdog_file_logger(handler tree)
{
    int rt;
    int x = 5;
    int number;
    int log_num = 0;

    // printf("\n\n\tUTILITY: checking if we have a RBT\n\n");

    rt = watchdog_rbt_selfcheck(tree, tree->root, 0, 0);

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
        // printf("\tThe structure is a RBT with root %d and %d black nodes from root to NULL nodes.", root->key, rt);
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
    if (tail_rbt_list == NULL && head_rbt_list == NULL)
    {
        assert(tail_rbt_list == NULL && head_rbt_list == NULL);

        handler instance = (handler)malloc(sizeof(struct sentinel));
        if (instance == NULL)
            return NULL;

        instance->n = NULL;
        instance->b = NULL;
        instance->multitude = 1;
        instance->root = NULL;
        instance->No = 1;

        tail_rbt_list = instance;
        head_rbt_list = tail_rbt_list;

        assert(tail_rbt_list != NULL && head_rbt_list != NULL);

        return instance;
    }
    else if (tail_rbt_list != NULL && head_rbt_list != NULL)
    {
        assert(0);
        handler instance = (handler)malloc(sizeof(struct sentinel));
        if (instance == NULL)
            return NULL;
        instance->root = NULL;

        handler aux = head_rbt_list;
        assert(aux != NULL);

        while (aux->n != NULL && ((aux->n->No) - (aux->No) == 1))
            aux = aux->n;

        if (aux->n == NULL)
        {
            assert(aux == tail_rbt_list);

            instance->n = NULL;
            instance->b = aux;
            aux->n = instance;

            instance->multitude = tail_rbt_list->multitude + 1;
            instance->No = aux->No + 1;

            tail_rbt_list = instance;
            head_rbt_list->multitude = tail_rbt_list->multitude;

            return instance;
        }
        else
        {
            instance->n = aux->n;
            aux->n->b = instance;
            instance->b = aux;
            aux->n = instance;

            instance->No = aux->No + 1;
            instance->multitude = tail_rbt_list->multitude + 1;

            tail_rbt_list->multitude = instance->multitude;
            head_rbt_list->multitude = instance->multitude;

            return instance;
        }
    }
    else
        assert(0);
}

unsigned int rbt_destroy(handler tree)
{
    // WON'T ALLOW ME TO TOUCH THE HEAD AND TAIL
    assert(head_rbt_list != NULL && tail_rbt_list != NULL);

    handler aux_back, aux_next;

    if (tree->root != NULL)
        return 1;
    else
    {
        aux_back = tree->b;
        aux_next = tree->n;

        aux_back->n = aux_next;
        aux_next->b = aux_back;

        assert(0);
        assert(head_rbt_list->multitude == 2);

        head_rbt_list->multitude = (head_rbt_list->multitude) - 1;
        tail_rbt_list->multitude = tail_rbt_list->multitude - 1;
        assert(head_rbt_list->multitude == tail_rbt_list->multitude);

        free(tree);
        return 0;
    }
}

int rbt_insert(handler tree, unsigned int key)
{
    node aux1, aux2;
    int rot;

    aux2 = NULL;
    aux1 = tree->root;
    while (aux1 != NULL)
    {
        aux2 = aux1;
        if (key < aux1->key)
            aux1 = aux1->left;
        else if (key > aux1->key)
            aux1 = aux1->right;
        else if (key == aux1->key)
            return 1;
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
        tree->root = new;
    else if (key < aux2->key)
        aux2->left = new;
    else if (key > aux2->key)
        aux2->right = new;
    else
        assert(0);

    rot = insert_fixup(&tree, &new);
    if (rot != 0)
        printf("\t%d rotations performed during fixup\n", rot);

    return 0;
}

int rbt_delete(handler tree, unsigned int key)
{
    if (tree->root == NULL)
        return 4;

    node d, temp, aux, T;
    int rt;
    int flag = 0; // if it ends up 1 it means a sentinel was created, if it ends up 2 it means the root was deleted
    char og_color;

    d = tree->root;

    while (d != NULL)
    {
        if (key < d->key)
            d = d->left;
        else if (key > d->key)
            d = d->right;
        else
            break;
    }

    if (d != NULL)
    {
        og_color = d->color;

        if (d->left == NULL && d->right == NULL)
        {
            printf("\t\tCASE 1");
            if (d->parent == NULL)
            {
                printf(".1\n");
                tree->root = NULL;
                og_color = 'r';
                flag = 2;
                free(d);
            }
            else
            {
                if (og_color == 'r')
                {
                    printf(".2\n");
                    if (d == d->parent->left)
                        d->parent->left = NULL;
                    else if (d == d->parent->right)
                        d->parent->right = NULL;
                    else
                        assert(0);
                }
                else if (og_color == 'b')
                {
                    printf(".3\n");

                    T = (node)malloc(sizeof(struct node_struct));

                    if (T == NULL)
                        return 2;

                    flag = 1;
                    printf("\t\tSentinel added in rbt_delete\n");

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

                free(d);
            }
        }
        else if (d->left == NULL && d->right != NULL)
        {
            printf("\t\tCASE 2\n");
            temp = d->right;
            delete_transplant(&tree, &d, &temp);
            free(d);
        }
        else if (d->right == NULL && d->left != NULL)
        {
            printf("\t\tCASE 3\n");
            temp = d->left;
            delete_transplant(&tree, &d, &temp);
            free(d);
        }
        else if (d->left != NULL && d->right != NULL)
        {
            printf("\t\tCASE 4\n");
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
                printf("\t\tSentinel added in rbt_delete\n");

                T->color = 'b';
                T->left = T;
                T->right = T;

                aux = T;
                temp->right = T;
                T->parent = temp;
            }

            delete_transplant(&tree, &temp, &aux);
            temp->right = d->right;
            temp->right->parent = temp;
            assert(temp->left == NULL);

            delete_transplant(&tree, &d, &temp);
            temp->left = d->left;
            assert(temp->left != NULL);
            temp->left->parent = temp;
            temp->color = d->color;

            temp = aux;

            free(d);
        }
        else
            assert(0);

        if (og_color == 'b')
        {
            rt = delete_fixup(&tree, &temp);
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
                    printf("\t\tSentinel is killed by rbt_delete\n");
                    return 0;
                }
                else
                    assert(0);
            }
            else if (flag == 2)
                return 5;
        }
        return 0;
    }
    else
        return 1;
}

int rbt_print(handler tree)
{
    return print_recursive(tree->root, 0);
}