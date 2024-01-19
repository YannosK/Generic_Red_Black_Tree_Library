#include <stdio.h>
#include <stdlib.h>
#include "redblacktree.h"

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

    int *int_handle;
    int_handle = NULL;

    usr_char = 'z';

    while (usr_char != 'q')
    {
        fflush(stdin);
        if (int_handle != NULL)
        {
            free(int_handle);
            int_handle = NULL;
        }

        printf("\n\n*******************************************************************************\n");
        printf("Previous choice %c\n", usr_char);
        printf("Select what would you like to do:\n");
        printf("q: quit\ns: show all red-black trees with their IDs\ni: insert new node\nd: delete a node\np: print a red-black Tree\n");
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
        case 's':
            printf("\n\n\tSHOW RED-BLACK TREE INSTANCES\n\n");
            int_handle = rbt_show();
            if (int_handle == NULL)
                printf("\tNo red-black trees where ever created\n");
            else
            {
                printf("\tThe available red-black trees have IDs:\n\n");
                for (i = 0; *(int_handle + i) != 0; i++)
                {
                    printf("\t%d\n", *(int_handle + i));
                }
            }
            break;
        case 'i':
            printf("\n\n\tINSERT\n\n");
            int_handle = rbt_show();
            if (int_handle == NULL)
            {
                printf("\tNo red-black trees were ever created. A new tree with a new ID will be created. Press any number to continue or 0 to abort: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                else
                {
                    usr_int = rbt_create();
                    if (usr_int == 0)
                    {
                        printf("\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                        return 2;
                    }
                    else
                    {
                        printf("\n\t\tInsert the key of the node you want to add. 0 is not allowed. If you enter zero it will abort: ");
                        if (1 != scanf("%d", &usr_int2))
                            return 1;
                        getchar();
                        if (usr_int2 == 0)
                        {
                            rt = rbt_destroy(usr_int);
                            if (rt == 1)
                            {
                                printf("\n\t\tAttempted destruction of a non-empty tree\n");
                                return 3;
                            }
                            break;
                        }
                        else
                        {
                            rt = rbt_insert(usr_int, usr_int2);
                            switch (rt)
                            {
                            case 2:
                                printf("\n\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                                return 2;
                                break;
                            case 1:
                                assert(0); // the tree did not previously exist, it can't have nodes in it
                                break;
                            case 0:
                                break;
                            default:
                                assert(0);
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                printf("\tYou can insert nodes by specifying the tree ID and the node key. Press any number to continue, or 0 to abort: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                else
                {
                    printf("\n\tFirst select the tree by its ID. Press 0 to see the available trees and their IDs: ");
                    if (1 != scanf("%d", &usr_int))
                        return 1;
                    getchar();
                    if (usr_int == 0)
                    {
                        printf("\n\t\tThe available red-black trees have IDs:\n\n");
                        for (i = 0; *(int_handle + i) != 0; i++)
                            printf("\t\t\t%d\n", *(int_handle + i));
                        printf("\n\tNow please enter an ID based on the above: ");
                        if (1 != scanf("%d", &usr_int))
                            return 1;
                        getchar();
                    }
                    for (i = 0; *(int_handle + i) != 0; i++)
                    {
                        if ((*(int_handle + i)) == usr_int)
                        {
                            printf("\n\t\tInsert the node key. 0 is not allowed. If you enter zero it will abort: ");
                            if (1 != scanf("%d", &usr_int2))
                                return 1;
                            getchar();
                            if (usr_int2 == 0)
                                break;
                            else
                            {
                                rt = rbt_insert(usr_int, usr_int2);
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
                            }
                        }
                        else if ((*(int_handle + i + 1)) == 0)
                            printf("\n\tYou entered an ID that does not exist\n");
                    }
                }
            }
            break;
        case 'd':
            printf("\n\n\tDELETE\n\n");
            int_handle = rbt_show();
            if (int_handle == NULL)
            {
                printf("\tNo red-black trees were ever created - nothing to delete\n");
                continue;
            }
            else
            {
                printf("\tYou can delete nodes by specifying the tree ID and the node key. Press any number to continue, or 0 to abort: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                else
                {
                    printf("\n\tFirst select the tree by its ID. Press 0 to see the available trees and their IDs: "); // needs an enum
                    if (1 != scanf("%d", &usr_int))
                        return 1;
                    getchar();
                    if (usr_int == 0)
                    {
                        printf("\n\t\tThe available red-black trees have IDs:\n\n");
                        for (i = 0; *(int_handle + i) != 0; i++)
                            printf("\t\t\t%d\n", *(int_handle + i));
                        printf("\n\tNow please enter an ID based on the above: ");
                        if (1 != scanf("%d", &usr_int))
                            return 1;
                        getchar();
                    }
                    for (i = 0; *(int_handle + i) != 0; i++)
                    {
                        if ((*(int_handle + i)) == usr_int)
                        {
                            printf("\n\t\tInsert the node key. 0 is not allowed. If you enter zero it will abort: ");
                            if (1 != scanf("%d", &usr_int2))
                                return 1;
                            getchar();
                            if (usr_int2 == 0)
                                break;
                            else
                            {
                                printf("\n\t\tDeleting node with key %d from tree %d\n\n", usr_int2, usr_int);
                                rt = rbt_delete(usr_int, usr_int2);
                                switch (rt)
                                {
                                case 0:
                                    break;
                                case 1:
                                    printf("\t\tNo node with the inserted key exists\n");
                                    break;
                                case 2:
                                    printf("\t\tFatal memory error\n");
                                    return 3;
                                    break;
                                case 3:
                                    printf("\t\tFatal error code from the library redblacktree.h\n");
                                    return 3;
                                    break;
                                case 4:
                                    printf("\t\tThe tree is empty\n");
                                    break;
                                case 5:
                                    // rt = rbt_destroy(usr_int);
                                    // assert(0);
                                    // if (rt == 1)
                                    // {
                                    //     printf("\n\t\tAttempted destruction of a non-empty tree\n");
                                    //     return 3;
                                    // }
                                    break;
                                default:
                                    assert(0);
                                    break;
                                }
                            }
                            break;
                        }
                        else if ((*(int_handle + i + 1)) == 0)
                            printf("\n\tYou entered an ID that does not exist\n");
                    }
                }
            }
            break;
        case 'p':
            printf("\n\n\tPRINT\n\n");
            int_handle = rbt_show();
            if (int_handle == NULL)
            {
                printf("\tNo red-black trees were ever created - nothing to print\n");
                continue;
            }
            else
            {
                printf("\n\tPlease enter the ID of the tree you would like to print: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                printf("\n");
                for (i = 0; *(int_handle + i) != 0; i++)
                {
                    if ((*(int_handle + i)) == usr_int)
                    {
                        rt = rbt_print(usr_int);
                        if (rt == 1)
                            printf("\tThe tree is empty\n");
                        break;
                    }
                    else if ((*(int_handle + i + 1)) == 0)
                        printf("\tYou entered an ID that does not exist\n");
                }
            }
            break;
        default:
            break;
        }
    }
    return 0;
}