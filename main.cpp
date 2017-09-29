#include "BinarySearchTree.h"

void main()
{
    BinarySearchTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);

    tree.printTree(PRE);
    std::cout << std::endl << "--------------" << std::endl;
    tree.printTree(IN);
    std::cout << std::endl << "--------------" << std::endl;
    tree.printTree(POST);
    std::cout << std::endl << "--------------" << std::endl;
    tree.printTree(LEVEL);
    std::cout << std::endl << "--------------" << std::endl;
    tree.countNodes();
    tree.countFullNodes();
    tree.countLeafs();
    tree.internalPathLenght();
}