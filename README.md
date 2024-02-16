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

This is the core library of the project providing the user with functions to manipulate red-black trees. It supports the manipulation of red-black trees that are structured from nodes that have keys of (theoretically) any data type, as long as it is used in conjunction with the corresponding key-type libraries (```IntegerKeys.h``` and ```StringKeys.h```). The structure of the red-black trees is based on the key values of the nodes, and their relationships (for example with integer keys they are sorted based on whuch is smaller and which is larger, while strings are sorted based on alphabetical order).
<br>
All the functions inside the library have proper contracts and comments written, that explain in detail what the iput arguments are (type, description etc) as well as the return values. Here I will briefly explain their use

### ```handler```
This is a ```typedef``` of a pointer to an esoteric struct of the ```RedBlackTree.c```, that the user will not have access to, but can declare variables of the type. It points to sentinel ```struct``` of the trees. These **sentinel structures** contain the basic information of each tree, and they are used by most functions inside ```RedBlackTree.c``` to operate on a specific tree.

### ```rbt_create```
This function is used to create a new tree. It allocates memory in the heap for the _sentinel ```struct```_ of the new tree returning a pointer to it as a type ```handler```. The user is responsible of storing this pointer in an apropriate ```handler``` variable, if they wish to operate on the specific tree. Else they will loose acces to it, resulting in memory leaks.

### ```rbt_destroy```
This function performs the opposite operation of ```rbt_create```. It deallocated the memory of a tree's sentinel struct, using the ```handler``` to the tree's sentinel, effectively destroying the tree. In order to avoid memory leaks it is only allowed to destroy empty trees. Inside ```RedBlackTree.c``` this means that the tree has a NULL root. If the tree is not empty the function returns 1, without destroying the tree.

### ```rbt_nodefind```
This function finds a specific node inside a tree and prints out its information - that is its key, its parent's and childrens' keys, and its color. The user musty input the ```handler``` to the tree and a temporary proper key, that will be created with the key-type functions of the key-type libraries (```IntegerKeys.h``` and ```StringKeys.h```).Generally it must make use of functions from the key-type libraries in order to add a proper key and do comparsions of key values of various nodes inside ```RedBlackTree.c```. The key inserted will be a void pointer to a **key data-holder structure** created by the key-type functions. The comparison functions from the key-type libraries are added as pointers to functions inside the arguments of ```rbt_nodefind```.
<br>
If the function finds a specific node it returns a void pointer to it. Else it returns a NULL pointer. In any case the key inserted as argument is temporary, and the function is responsible to destroy it before it returns, to avoid memory leaks. Thus it takes as an argument a ```destroykey``` function, provided by the key-type libraries.

### ```rbt_nodeprint```
This function is designed to be used in conjunction with the ```rbt_nodefind``` function, to print node information, from a specific tree's node. The user must provide a pointer to the node directly, as a void pointer, as well as a proper ```keyprinter``` function provided by the key-type libraries (```IntegerKeys.h``` and ```StringKeys.h```). The only way for the user to acquire the pointer to a node in a tree is to run ```rbt_nodefind``` first, or even add it directly as argument. In the second case it will return 1 if ```rbt_nodefind``` found no proper node.

### ```rbt_insert```
This function is used to insert a node inside an existing red-black tree. The user must have first run ```rbt_create``` to create the tree, and use the returned ```handler``` as an input argument for ```rbt_insert```. They must also have run a proper key creation function, provided by the key-type libraries (```IntegerKeys.h``` and ```StringKeys.h```), and add a pointer to the key's data-holder structure (that is returned by the key creation functions) as a second argument of ```rbt_insert```. Also it must provide as arguments to ```rbt_insert``` pointers to functions from the key-type libraries, in order to perform comparisons of different key types.
<br>
The function has different return values to inform the user of proper execution, wether the insertion failed, or memory allocation in the heap failed. The latter is a fatal error and the user should terminate the program. The case where insertion failed is because a node with the inserted key already existed in the specified tree. In that case ```rbt_insert``` automatically destroys the inputed key data-holder structure before it returns, to avoid memory leaks. To do that it takes as a last input argument a pointer to a ```destroykey``` function provided by the key-type libraries.