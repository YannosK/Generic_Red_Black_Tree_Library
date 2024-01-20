#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"
#include "IntegerNodes.h"

// #define NDEBUG
#include <assert.h>

/*
    This main function is a scafold to test the red-black tree library
    It implements a terminal menu for a user to use the library functions

    returns 0 when the user selects to quit
    returns 1 is scanf reads wrong user input
    returns 2 if dynamic memory allocation in the heap fails
    rerurns 3 if something else goes wrong
*/
int main()
{
    char usr_char;
    int usr_int, usr_int2, rt, i;
    void *key;

    /*
        ID is an array with the handlers of all created RBTs
        It is used by this scaffold main.c for the user to know where to insert and delete
    */
    handler ID[20];
    for (i = 0; i < 20; i++)
        ID[i] = NULL;

    usr_char = 'z';

    while (usr_char != 'q')
    {
        fflush(stdin);

        printf("\n\n*******************************************************************************\n");
        printf("Previous choice %c\n", usr_char);
        printf("Select what would you like to do:\n");
        printf("q: quit\ni: insert new node\nd: delete a node\np: print a red-black Tree\nt: test\n");
        printf("Your choice: ");
        scanf("%c", &usr_char);
        getchar();

        if (usr_char == '\n')
        {
            do
            {
                usr_int = getchar();
            } while (usr_int == 10);
            usr_char = (char)usr_int;
        }

        switch (usr_char)
        {
        case 'q':
            printf("\n\n\tQUIT\n\n");
            break;
        case 'i':
            printf("\n\n\tINSERT\n\n");

            printf("\tEnter the tree ID: ");
            if (1 != scanf("%d", &usr_int))
                return 1;
            getchar();

            if (ID[usr_int] == NULL)
                ID[usr_int] = rbt_create();

            printf("\tEnter the node value: ");
            if (1 != scanf("%d", &usr_int2))
                return 1;
            getchar();

            rt = rbt_insert((ID + usr_int), int_createkey(usr_int2), int_compare, int_equal, int_destroykey);
            switch (rt)
            {
            case 2:
                printf("\n\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                return 2;
                break;
            case 1:
                printf("\n\t\tA node with the inserted key already exists.\n");
                break;
            case 0:
                break;
            default:
                assert(0);
                break;
            }
            break;
        case 'd':
            printf("\n\n\tDELETE\n\n");

            printf("\tEnter the tree ID: ");
            if (1 != scanf("%d", &usr_int))
                return 1;
            getchar();

            if (ID[usr_int] == NULL)
            {
                printf("\n\tInvalid ID\n");
                break;
            }
            else
            {
                printf("\tEnter the node value: ");
                if (1 != scanf("%d", &usr_int2))
                    return 1;
                getchar();

                key = rbt_keyfind(ID[usr_int], int_createkey(usr_int2), int_compare, int_equal, int_destroykey);
                rt = rbt_delete((ID + usr_int), key, int_compare, int_equal, int_destroykey);
                switch (rt)
                {
                case 0:
                    break;
                case 1:
                    printf("\n\t\tNo node with the inserted key exists\n");
                    break;
                case 2:
                    printf("\n\t\tFatal memory error\n");
                    return 3;
                    break;
                case 3:
                    printf("\n\t\tFatal error code from the library redblacktree.h\n");
                    return 3;
                    break;
                case 4:
                    printf("\n\t\tThe tree is empty\n");
                    break;
                case 5:
                    rt = rbt_destroy(ID[usr_int]);
                    if (rt == 1)
                    {
                        printf("\n\t\tAttempted destruction of a non-empty tree\n");
                        return 3;
                    }
                    else
                        ID[usr_int] = NULL;
                    break;
                default:
                    assert(0);
                    break;
                }
                break;
            }
        case 'p':
            printf("\n\n\tPRINT\n\n");
            printf("\n\tPlease enter the ID of the tree you would like to print: ");
            if (1 != scanf("%d", &usr_int))
                return 1;
            getchar();
            printf("\n");
            if (ID[usr_int] == NULL)
            {
                printf("\n\tInavlid ID\n");
                break;
            }
            else
            {
                rt = rbt_print(ID[usr_int], int_print);
                if (rt == 1)
                    printf("\tThe tree is empty\n");
                break;
            }
        // case 't':
        //     if (generic_int_test(int_createkey(5), int_size(), int_compare) == 0)
        //         printf("\n\n\tGREAT SUCCESS!!\n\n");
        //     else
        //         printf("\n\n\tYOU SUCK!!\n\n");
        //     break;
        default:
            break;
        }
    }
    return 0;
}