#include <stdio.h>
#include "redblacktree.h"

// #define NDEBUG
#include <assert.h>

/*
    This main function is a scafold to test the red-black tree library
    It implements a terminal menu for a user to use the library functions

    returns 0 when the user selects to quit
    returns 1 is scanf reads wrong user input
    returns 2 if dynamic memory allocation in the heap fails
*/
int main()
{
    char usr_char;
    int usr_int, usr_int2, rt, i;
    int *int_handle;
    handler tree;

    usr_char = 'z';

    if (rbt_init() == NULL)
    {
        printf("\nFATAL MEMORY ERROR");
        return 2;
    }
    else
    {

        // rt = rbt_insert(rbt_create(), 3);
        while (usr_char != 'q')
        {
            fflush(stdin);
            printf("\n\n*******************************************************************************\n");
            printf("Previous choice %c\n", usr_char);
            printf("Select what would you like to do:\n");
            printf("q: quit\na: create a new red black tree\ns: show all red-black trees with their IDs\ni: insert new node\nd: delete a node\np: print the red-black Tree\n");
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
            case 'a':
                printf("\n\n\tCREATE NEW RED-BLACK TREE\n\n");
                rt = rbt_create();
                if (rt == 0)
                {
                    printf("\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 2;
                }
                else
                    printf("\tRed-black tree created with ID No: %d\n", rt);
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
                        printf("\t%d\n", *(int_handle + i));
                }
                break;
            case 'i':
                printf("\n\n\tINSERT\n\n");
                int_handle = rbt_show();
                if (int_handle == NULL)
                {
                    printf("\tNo red-black trees where ever created.\n\tPlease select choice a. from menu\n");
                    continue;
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
                                    continue;
                                else
                                {
                                    printf("\t\tInserting new node with key %d in tree %d\n", usr_int2, usr_int);
                                    rt = rbt_insert(usr_int, usr_int2);
                                    if (rt == 2)
                                    {
                                        printf("\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                                        return 2;
                                    }
                                    else if (rt == 1)
                                    {
                                        printf("\t\tA node with the inserted key already exists.\n");
                                        continue;
                                    }
                                    else if (rt == 0)
                                        continue;
                                    else
                                        assert(0);
                                }
                                break;
                            }
                            else if ((*(int_handle + i + 1)) == 0)
                                printf("\n\tYou entered an ID that does not exist\n");
                        }
                    }
                }
                break;
            case 'd':
                printf("\n\n\tDELETE\n\n");
                printf("\tYou can delete nodes by specifying the tree ID and the node key. Press 0 to abort: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                printf("\t\tFirst select the tree by its ID. Press 0 to see the available trees and their IDs: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                printf("\t\tInsert the node key. 0 is not allowed: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                rt = rbt_delete(&tree, usr_int);
                if (rt == 3)
                {
                    printf("\tFATAL ERROR: Esoteric mistake. Shoot the programmer. This program is dead\n");
                    return 3;
                }
                else if (rt == 4)
                {
                    printf("\tThe tree is empty.\n");
                    break;
                }
                else if (rt == 2)
                {
                    printf("\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 2;
                }
                else if (rt == 1)
                {
                    printf("\tNo node with such a key exists.\n");
                    break;
                }
                else if (rt == 0)
                    break;
                else
                    assert(0);
            case 'p':
                printf("\n\n\tPRINT\n\n");
                printf("\n\tPlease enter the ID of the tree you would like to print: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                // rt = rbt_print(tree);
                if (rt == 1)
                    printf("\tThe tree is empty\n");
                break;
            default:
                break;
            }
        }
    }

    return 0;
}