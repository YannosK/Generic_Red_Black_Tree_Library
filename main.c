#include <stdio.h>
#include "redblacktree.h"

// #define NDEBUG
#include <assert.h>

int main()
{
    char usr_char;
    usr_char = 'a';
    int usr_int, rt;
    handler tree;

    if (rbt_init() == NULL)
    {
        printf("\nFATAL MEMORY ERROR");
        return 1;
    }
    else
    {
        while (usr_char != 'q')
        {
            fflush(stdin);
            printf("\n\n*******************************************************************************\n");
            printf("Previous choice %c\n", usr_char);
            printf("Select what would you like to do:\n");
            printf("q : quit\na: create a new red black tree\ni : insert new node using its key\nd : delete a node using its key\np : print the Red-Black Tree\nu : Use utility function\n");
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
                tree = rbt_create();
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
                    return 0;
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
                    return 0;
                }
                else if (rt == 4)
                {
                    printf("\tThe tree is empty.\n");
                    break;
                }
                else if (rt == 2)
                {
                    printf("\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 0;
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