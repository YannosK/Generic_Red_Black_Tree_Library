#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlackTree.h"
#include "IntegerNodes.h"
#include "StringNodes.h"

// #define NDEBUG
#include <assert.h>

/*
    This main function is a scafold to test the red-black tree library
    It implements a terminal menu for a user to use the library functions

    returns 0 when the user selects to quit
    returns 1 if dynamic memory allocation in the heap fails
    rerurns 2 if something else goes wrong
*/
int main()
{
    char usr_char, usr_char2;
    char usr_string[64];
    int usr_int, usr_int2, rt, i;
    void *key;
    void *node;

    /*
        ID is an array with the handlers of all created RBTs
        It is used by this scaffold main.c for the user to know where to insert and delete
    */
    handler int_ID[10];
    handler string_ID[10];
    for (i = 0; i < 10; i++)
    {
        int_ID[i] = NULL;
        string_ID[i] = NULL;
    }

    usr_char = 'z';

    while (usr_char != 'q')
    {
        fflush(stdin);

        printf("\n\n****************************************************************************************\n");
        printf("Previous choice %c\n", usr_char);
        printf("Select what would you like to do:\n");
        printf("q: quit\ni: insert new node\nd: delete a node\nk: print a key value from a node from the red-black tree\np: print a red-black Tree\ns: print all trees\n");
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

            printf("\tInsert an integer or a string?\n\tPress i for integer and s for string, or q to abort: ");
            scanf("%c", &usr_char2);
            getchar();

            if (usr_char2 == 'i')
            {
                printf("\tEnter the tree ID: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (int_ID[usr_int] == NULL)
                    int_ID[usr_int] = rbt_create();

                printf("\tEnter the node value: ");
                if (1 != scanf("%d", &usr_int2))
                    break;
                getchar();

                key = int_createkey(usr_int2);
                if (key == NULL)
                    return 1;

                rt = rbt_insert((int_ID + usr_int), key, int_compare, int_equal, int_destroykey);
                switch (rt)
                {
                case 2:
                    printf("\n\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 1;
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
            }
            else if (usr_char2 == 's')
            {
                printf("\tEnter the tree ID: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (string_ID[usr_int] == NULL)
                    string_ID[usr_int] = rbt_create();

                printf("\tEnter the node value: ");
                if (fgets(usr_string, sizeof(usr_string), stdin) == NULL)
                    break;

                key = string_createkey(usr_string, sizeof(usr_string));
                if (key == NULL)
                    return 1;

                rt = rbt_insert((string_ID + usr_int), key, string_compare, string_equal, string_destroykey);
                switch (rt)
                {
                case 2:
                    printf("\n\t\tFATAL ERROR: You have no memory (heap allocation failed) and the program will terminate\n");
                    return 1;
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
            }
            break;
        case 'd':
            printf("\n\n\tDELETE\n\n");

            printf("\tDelete an integer or a string?\n\tPress i for interger and s for string, or q to abort: ");
            scanf("%c", &usr_char2);
            getchar();

            if (usr_char2 == 'i')
            {
                printf("\tEnter the tree ID: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (int_ID[usr_int] == NULL)
                    printf("\n\tInvalid ID\n");
                else
                {
                    printf("\tEnter the node value: ");
                    if (1 != scanf("%d", &usr_int2))
                        break;
                    getchar();

                    node = rbt_nodefind(int_ID[usr_int], int_createkey(usr_int2), int_compare, int_equal, int_destroykey);
                    if (node == NULL)
                        printf("\n\t\tNo node with the inserted key exists\n");
                    else
                    {
                        rt = rbt_delete((int_ID + usr_int), node, int_compare, int_equal, int_destroykey);
                        switch (rt)
                        {
                        case 0:
                            break;
                        case 1:
                            assert(0);
                            break;
                        case 2:
                            printf("\n\t\tFatal memory error\n");
                            return 2;
                            break;
                        case 3:
                            printf("\n\t\tFatal error code from the library redblacktree.h\n");
                            return 2;
                            break;
                        case 4:
                            printf("\n\t\tThe tree is empty\n");
                            break;
                        case 5:
                            rt = rbt_destroy(int_ID[usr_int]);
                            if (rt == 1)
                            {
                                printf("\n\t\tAttempted destruction of a non-empty tree\n");
                                return 2;
                            }
                            else
                                int_ID[usr_int] = NULL;
                            break;
                        default:
                            assert(0);
                            break;
                        }
                    }
                }
            }
            else if (usr_char2 == 's')
            {
                printf("\tEnter the tree ID: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (string_ID[usr_int] == NULL)
                    printf("\n\tInvalid ID\n");
                else
                {
                    printf("\tEnter the node value: ");
                    if (fgets(usr_string, sizeof(usr_string), stdin) == NULL)
                        break;

                    node = rbt_nodefind(string_ID[usr_int], string_createkey(usr_string, sizeof(usr_string)), string_compare, string_equal, string_destroykey);
                    if (node == NULL)
                        printf("\n\t\tNo node with the inserted key exists\n");
                    else
                    {
                        rt = rbt_delete((string_ID + usr_int), node, string_compare, string_equal, string_destroykey);
                        switch (rt)
                        {
                        case 0:
                            break;
                        case 1:
                            assert(0); // it is dealt with above so it should not be needed
                            break;
                        case 2:
                            printf("\n\t\tFatal memory error\n");
                            return 2;
                            break;
                        case 3:
                            printf("\n\t\tFatal error code from the library redblacktree.h\n");
                            return 2;
                            break;
                        case 4:
                            printf("\n\t\tThe tree is empty\n");
                            break;
                        case 5:
                            rt = rbt_destroy(string_ID[usr_int]);
                            if (rt == 1)
                            {
                                printf("\n\t\tAttempted destruction of a non-empty tree\n");
                                return 2;
                            }
                            else
                                string_ID[usr_int] = NULL;
                            break;
                        default:
                            assert(0);
                            break;
                        }
                    }
                }
            }
            break;
        case 'k':
            printf("\n\n\tPRINT KEY\n\n");

            printf("\tYou can print the key of a node, from an existing tree using, the nodes\n");
            break;
        case 'p':
            printf("\n\n\tPRINT\n\n");

            printf("\tYou can print trees with integers or strings\n\tPress i for interger and s for string, or q to abort: ");
            scanf("%c", &usr_char2);
            getchar();

            if (usr_char2 == 'i')
            {
                printf("\tPlease enter the ID of the tree you would like to print: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();
                printf("\n");

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (int_ID[usr_int] == NULL)
                {
                    printf("\tInavlid ID\n");
                }
                else
                {
                    rt = rbt_print(int_ID[usr_int], int_print);
                    if (rt == 1)
                        printf("\tThe tree is empty\n");
                }
            }
            else if (usr_char2 == 's')
            {
                printf("\tPlease enter the ID of the tree you would like to print: ");
                if (1 != scanf("%d", &usr_int))
                    break;
                getchar();
                printf("\n");

                if (usr_int > 9)
                {
                    printf("\n\tThe tree IDs range from 0 to 9!\n");
                    break;
                }
                assert(usr_int <= 9 && usr_int >= 0);

                if (string_ID[usr_int] == NULL)
                {
                    printf("\tInavlid ID\n");
                }
                else
                {
                    rt = rbt_print(string_ID[usr_int], string_print);
                    if (rt == 1)
                        printf("\tThe tree is empty\n");
                }
            }
            break;
        case 's':
            printf("\n\n---------------------------------------------------------------------------------------\n");
            printf("---------------------------------------------------------------------------------------\n");
            printf("\n\n\tINTEGER TREES\n\n");
            for (i = 0; i < 10; i++)
            {
                if (int_ID[i] != NULL)
                {
                    printf("\n---------------------------------------------------------------------------------------\n");
                    printf("Integer Tree ID: %d\n\n\n", i);
                    rt = rbt_print(int_ID[i], int_print);
                }
            }

            printf("\n\n---------------------------------------------------------------------------------------\n");
            printf("---------------------------------------------------------------------------------------\n");
            printf("\n\n\tSTRING TREES\n\n");
            for (i = 0; i < 10; i++)
            {
                if (string_ID[i] != NULL)
                {
                    printf("\n---------------------------------------------------------------------------------------\n");
                    printf("String Tree ID: %d\n\n\n", i);
                    rt = rbt_print(string_ID[i], string_print);
                }
            }
            break;
        default:
            break;
        }
    }
    return 0;
}