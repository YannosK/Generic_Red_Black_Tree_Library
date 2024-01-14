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
    usr_char = 'a';
    int usr_int, rt;
    int *int_handle;
    handler tree;

    if (rbt_init() == NULL)
    {
        printf("\nFATAL MEMORY ERROR");
        return 2;
    }
    else
    {
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
                printf("\n\n\tSHOW RED-BLAVK TREE INSTANCES\n\n");
                int_handle = rbt_show();
                if (int_handle == NULL)
                    printf("\tNo red-black trees where ever created\n");
                else
                {
                    printf("\tThe available red-black trees have IDs:\n\n");
                    int i;
                    for (i = 0; *(int_handle + i) != 0; i++)
                        printf("\t%d\n", *(int_handle + i));
                }
                break;
            case 'i':
                printf("\n\n\tINSERT\n\n");
                printf("\tType the key of the node you would like to insert. Zero is not allowed. Press 0 to abort: ");
                if (1 != scanf("%d", &usr_int))
                    return 1;
                getchar();
                if (usr_int == 0)
                    continue;
                rt = rbt_insert(&tree, usr_int);
                if (rt == 2)
                {
                    printf("\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 2;
                }
                else if (rt == 1)
                {
                    printf("\tA node with the inserted key already exists.\n");
                    break;
                }
                else if (rt == 0)
                    break;
                else
                    assert(0);
            case 'd':
                printf("\n\n\tDELETE\n\n");
                printf("\tType the key of the node you would like to delete. Press 0 to abort: ");
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
                rt = rbt_print(tree);
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