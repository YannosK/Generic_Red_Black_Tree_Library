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

This is the core library of the project providing the user with functions to manipulate red-black trees. It supports the manipulation of red-black trees that are structured from nodes that have keys of (theoretically) any data type, as long as it is used in conjunction with the corresponding key-type libraries