## Showcasing genericity in C language, by writing a generic red-black tree

Red black trees are famous data structures, deriving from the simpler binary search trees. The latter can run most functions in O(N) at worst.
Red black trees are mostly balanced trees, so they improve on complexity, in the order of O(lgN).

<br>

In this code I create a generic rbt that can create trees with nodes with integer keys, or string keys, using the same library to operate on them.
In the future one could possibly add more libraries to have trees with other data types as well, like, for example, double precision keys.

<br>

The project is meant to be a practise of the power of void pointers in C, as well as the use of libraries and concepts of abstraction, in C programming.