## Scaffold ```main.c```

The main function ```main.c``` is a scaffold to test the libraries' functions. It provides a user interface via terminal where the user has the ability to work on and modify up to 10 different intger type red-black trees and up to 10 different string type red-black trees. The different trees have IDs ranging from 0 to 9 (for integer and string types respectfully). These IDs are asked from the user everytime they wish to modify a certain tree.

The terminal menu provides the user options that are specifically designed to put in use the function of the libraries of the project. These options are:

### insert
the user can insert a node in a specific tree. First the user must specify wether they want to insert a node in an integer type tree or a string type tree. Then they must provide the tree ID. If no tree with such ID exists then it is automatically created, and the node to be inserted will be the first node in the tree. Then they must input the value of the key they want the node to hold. Finally insertion in the tree is attempted.

If all goes well the program automatically resumes to the main menu. If something goes wrong then specific error messages are shown and then again the program returns to the main menu, except there is a fatal error.

Possible errors:
- inserting a tree ID outside the range 0 to 9
- inserting a node key that is equal with another node's key inside a tree

Functions from RedBlackTree.h used
- typedef handler is used to declare pointers to sentinel structs of trees. These pointers are what is stored inside the tree ID arrays (the ID of the trees is basically the indexing of these arrays)
- rbt_insert is used to insert a node in a tree with a known handler (found from the ID array), with the key the user inserted

Functions from IntegerNodes.h and StringNodes.h used:
