#include <stdio.h>
#include <stdlib.h>
#include "redblacktree.h"

// #define NDEBUG
#include <assert.h>

node root = NULL;

/*******************************************************************************/
// INTERNAL FUNCTIONS
/*******************************************************************************/

/*
    Left Rotation on Red-Black Tree Node

    returns 1 if successful
*/
int rotate_left(node *x)
{
    assert((*x) != NULL && (*x)->right != NULL);

    node y;

    y = (*x)->right;

    (*x)->right = y->left;
    if (y->left != NULL)
        y->left->parent = (*x);

    y->parent = (*x)->parent;
    if ((*x)->parent == NULL)
        root = y;
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
int rotate_right(node *x)
{
    assert((*x) != NULL && (*x)->left != NULL);

    node y;

    y = (*x)->left;

    (*x)->left = y->right;
    if (y->right != NULL)
        y->right->parent = (*x);

    y->parent = (*x)->parent;
    if ((*x)->parent == NULL)
        root = y;
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
int insert_fixup(node *x)
{
    assert((*x) != NULL);

    node uncle;
    node aux;
    int rr = 0;
    int rl = 0;
    int cnt = 0;

    while ((*x)->parent != NULL && (*x)->parent->color == 'r')
    {
        assert((*x)->parent->parent != NULL);       // if the parent is red then grandparent definately exists
        assert((*x)->parent->parent->color == 'b'); // grandparent should also be black in any case

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
                    rl = rotate_left(x) + rl;
                }
                assert((*x)->parent->parent != NULL);
                printf("\t\tCASE 3\n");
                (*x)->parent->color = 'b';
                (*x)->parent->parent->color = 'r';
                aux = (*x)->parent->parent;
                rr = rotate_right(&aux) + rr;
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
                    rr = rotate_right(x) + rr;
                }
                assert((*x)->parent->parent != NULL);
                printf("\t\tCASE 3\n");
                (*x)->parent->color = 'b';
                (*x)->parent->parent->color = 'r';
                aux = (*x)->parent->parent;
                rl = rotate_left(&aux) + rl;
            }
        }
        else
            assert(0);
    }
    printf("\t\tCASE 0\n");
    root->color = 'b';
    return rr + rl;
}

/*
    Auxiliary of Red-Black Tree Delete

    Node t (transplant) takes node's d (soon-to-be dead) place
    returns 0 if executed correctly
    returns 1 if we inserted a node with broken pointers on the parent side
*/
int delete_transplant(node *d, node *t)
{
    assert((*d) != NULL && (*t) != NULL & (*t)->parent != NULL);

    if ((*d)->parent == NULL)
        root = (*t);
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
int delete_fixup(node *x)
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

    while ((*x)->color == 'b' && (*x) != root)
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
                    rotate_left(&p);
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
                            rotate_right(&w);
                            assert((*x) == (*x)->parent->left);
                            w = (*x)->parent->right;
                        }
                        printf("\t\t\tTYPE 4\n");
                        w->color = (*x)->parent->color;
                        (*x)->parent->color = 'b';
                        assert(w->right != NULL);
                        w->right->color = 'b';
                        p = (*x)->parent;
                        rotate_left(&p);
                        (*x) = root;
                    }

                    if (w->color != 'r' && w->color != 'b')
                        assert(0);
                }
            }
            else
            {
                printf("\t\t\tTYPE 0\n"); // sibling is null
                if ((*x)->parent != root)
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
                    rotate_right(&p);
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
                            rotate_left(&w);
                            assert((*x) == (*x)->parent->right);
                            w = (*x)->parent->left;
                        }
                        printf("\t\t\tTYPE 4\n");
                        w->color = (*x)->parent->color;
                        (*x)->parent->color = 'b';
                        assert(w->left != NULL);
                        w->left->color = 'b';
                        p = (*x)->parent;
                        rotate_right(&p);
                        (*x) = root;
                    }

                    if (w->color != 'r' && w->color != 'b')
                        assert(0);
                }
            }
            else
            {
                printf("\t\t\tTYPE 0\n"); // sibling is null
                if ((*x)->parent != root)
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

    returns 0 if executed correctly
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

/*******************************************************************************/
// PUBLIC FUNCTIONS
/*******************************************************************************/

int rbt_insert(int key)
{
    node aux1, aux2;
    int rot;

    aux2 = NULL;
    aux1 = root;
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
        root = new;
    else if (key < aux2->key)
        aux2->left = new;
    else if (key > aux2->key)
        aux2->right = new;
    else
        assert(0);

    rot = insert_fixup(&new);
    if (rot != 0)
        printf("\t%d rotations performed during fixup\n", rot);

    return 0;
}

int rbt_delete(int key)
{
    if (root == NULL)
        return 4;

    node d, temp, aux, T;
    int rt;
    int flag = 0;
    char og_color;

    d = root;

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
                root = NULL;
                og_color = 'r';
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
            }

            free(d);
        }
        else if (d->left == NULL && d->right != NULL)
        {
            printf("\t\tCASE 2\n");
            temp = d->right;
            delete_transplant(&d, &temp);
            free(d);
        }
        else if (d->right == NULL && d->left != NULL)
        {
            printf("\t\tCASE 3\n");
            temp = d->left;
            delete_transplant(&d, &temp);
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

            delete_transplant(&temp, &aux);
            temp->right = d->right;
            temp->right->parent = temp;
            assert(temp->left == NULL);

            delete_transplant(&d, &temp);
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
            rt = delete_fixup(&temp);
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
        }
        return 0;
    }
    else
        return 1;
}

int rbt_print(void)
{
    return print_recursive(root, 0);
}

// int util_rbt_selfcheck(node r, int blacks, int nill_blacks)
// {
//     assert(blacks >= 0 && nill_blacks >= 0);

//     int rt;

//     if (r == root || root == NULL)
//     {
//         if (root == NULL)
//             return -5;
//         else
//         {
//             if (root->color != 'r' && root->color != 'b')
//                 return -1;
//             else if (root->color == 'r' || root->parent != NULL)
//                 return -2;
//         }
//     }
//     else
//     {
//         assert(r != NULL);

//         if (r->color != 'r' && r->color != 'b')
//             return -1;
//         if (r->color == 'r')
//         {
//             if (!(((r->left == NULL) || (r->left->color == 'b')) && ((r->right == NULL) || (r->right->color == 'b'))))
//                 return -3;
//         }
//         else if (r->color == 'b')
//             blacks++;
//     }

//     if (r->left == NULL && r->right == NULL)
//     {
//         if (nill_blacks != 0 && nill_blacks != blacks)
//             return -4;
//         else
//         {
//             nill_blacks = blacks;
//             return nill_blacks;
//         }
//     }
//     else
//     {
//         assert(r->left != NULL || r->right != NULL);

//         if (r->left != NULL)
//         {
//             rt = util_rbt_selfcheck(r->left, blacks, nill_blacks);

//             if (rt < 0)
//             {
//                 switch (rt)
//                 {
//                 case -1:
//                     return -1;
//                     break;
//                 case -2:
//                     assert(0);
//                     break;
//                 case -3:
//                     return -3;
//                     break;
//                 case -4:
//                     return -4;
//                 case -5:
//                     assert(0);
//                     break;
//                 default:
//                     assert(0);
//                     break;
//                 }
//             }
//             else
//                 nill_blacks = rt;
//         }

//         if (r->right != NULL)
//         {
//             rt = util_rbt_selfcheck(r->right, blacks, nill_blacks);

//             if (rt < 0)
//             {
//                 switch (rt)
//                 {
//                 case -1:
//                     return -1;
//                     break;
//                 case -2:
//                     assert(0);
//                     break;
//                 case -3:
//                     return -3;
//                     break;
//                 case -4:
//                     return -4;
//                 case -5:
//                     assert(0);
//                     break;
//                 default:
//                     assert(0);
//                     break;
//                 }
//             }
//             else
//                 nill_blacks = rt;
//         }

//         return nill_blacks;
//     }
// }