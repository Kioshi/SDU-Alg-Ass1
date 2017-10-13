#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <algorithm>

enum eTraversals
{
    PRE,
    IN,
    POST,
    LEVEL
};

class BinaryNode
{
public:
	int element;
	BinaryNode *left;
	BinaryNode *right;

	BinaryNode(const int & theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ theElement }, left{ lt }, right{ rt } { }

	BinaryNode(int && theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ std::move(theElement) }, left{ lt }, right{ rt } { }
};


class BinarySearchTree
{
public:
	BinarySearchTree(); 
	BinarySearchTree(const BinarySearchTree & rhs); 
	BinarySearchTree(BinarySearchTree && rhs); 
	~BinarySearchTree();
	
	const int & findMin() const;
	const int & findMax() const;
	bool contains(const int & x) const;
	bool isEmpty() const;
	void printTree(eTraversals t) const;
    void countNodes() const;
    void countLeafs() const;
    void countFullNodes() const;
    void internalPathLength() const;

	void makeEmpty();
	void insert(const int & x);
	void insert(int && x);
	void remove(const int & x);
	
private:
	BinaryNode *root;

	void insert(const int & x, BinaryNode * & t);
	void insert(int && x, BinaryNode * & t);
	void remove(const int & x, BinaryNode * & t);
	BinaryNode * findMin(BinaryNode *t) const;
	BinaryNode * findMax(BinaryNode *t) const;
	
	bool contains(const int & x, BinaryNode *t) const;
	
	void makeEmpty(BinaryNode * & t);
    void printElement(BinaryNode *t, int floor) const;
	void printTree(BinaryNode *t, eTraversals traversal, int floor) const;
	BinaryNode * clone(BinaryNode *t) const;


    int _countNodes(BinaryNode *node) const;
    int _countLeafs(BinaryNode *node) const;
    int _countFullNodes(BinaryNode *node) const;
    int _internalPathLenght(BinaryNode *node, int floor) const;
	
};

#endif
