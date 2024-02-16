# Showcasing genericity in C language, by writing a generic red-black tree

Red black trees are famous data structures, deriving from the simpler binary search trees. The latter can run most functions in O(N) at worst.
Red black trees are mostly balanced trees, so they improve on complexity, in the order of O(lgN).
<br>

In this project I created generic rbt libraries that can create trees with nodes with integer keys, or string keys, using the same functions to operate on them.
In the future one could possibly add more libraries to have trees with other data types as well, like, for example, double precision keys.
<br>

The project is meant to be a practise of the power of void pointers in C language, as well as the use of libraries and concepts of abstraction, in C programming.
<br>

What follows is the documentation of the current project

## ```RedBlackTree.h``` library

This is the core library of the project providing the user with functions to manipulate red-black trees. It supports the manipulation of red-black trees that are structured from nodes that have keys of (theoretically) any data type, as long as it is used in conjunction with the corresponding key-type libraries (```IntegerKeys.h``` and ```StringKeys.h```).
All the functions inside the library have proper contracts and comments written, that explain in detail what the iput arguments are (type, description etc) as well as the return values. Here I will briefly explain their use

### ```handler```
This is a ```typedef``` of a pointer to an esoteric struct of the ```RedBlackTree.c```, that the user will not have access to, but can declare variables of the type. It points to sentinel ```struct``` of the trees. These **sentinel structures** contain the basic information of each tree, and they are used by most functions inside ```RedBlackTree.c``` to operate on the tree.

### ```rbt_create```
This function is used to create a new tree. It allocates memory in the heap for the _sentinel ```struct```_ of the new tree returning a pointer to it as a type ```handler```. The user is responsible of storing this pointer in an apropriate ```handler``` variable, if they wish to operate on the specific tree. Else they will loose acces to it, resulting in memory leaks.


### ```rbt_destroy```
It is the opposite operation of ```rbt_create```. It deallocated the memory of a tree's sentinel struct, using the ```handler``` to the tree's sentinel, effectively destroying the tree. In order to avoid memory leaks it is only allowed to destroy empty trees. Inside ```RedBlackTree.c``` this means that the tree has a NULL root. If the tree is not empty the function returns ```1```, without destroying the tree.

### ```rbt_nodefind```