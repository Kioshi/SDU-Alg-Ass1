#include "BinarySearchTree.h"
#include <queue>

BinarySearchTree::BinarySearchTree() : root{ nullptr }
{
}


BinarySearchTree::BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr }
{
	root = clone(rhs.root);
}


BinarySearchTree::BinarySearchTree(BinarySearchTree && rhs) : root{ rhs.root }
{
	rhs.root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	makeEmpty();
}

const int & BinarySearchTree::findMin() const
{
	if (isEmpty())
		return -1;
	return findMin(root)->element;
}


const int & BinarySearchTree::findMax() const
{
	if (isEmpty())
		return -1;
	return findMax(root)->element;
}

bool BinarySearchTree::contains(const int & x) const
{
	return contains(x, root);
}

bool BinarySearchTree::isEmpty() const
{
	return root == nullptr;
}

void BinarySearchTree::printTree(eTraversals traversal) const
{
	if (isEmpty())
		std::cout << "Empty tree" << std::endl;
	else if (traversal != LEVEL)
		printTree(root, traversal, 0);
    else
    {
        std::queue<BinaryNode*> thisFloor;
        std::queue<BinaryNode*> nextFloor;
        thisFloor.push(root);
        while(!thisFloor.empty())
        {
            BinaryNode* node = thisFloor.front();
            thisFloor.pop();
            std::cout << node->element << " ";
            if (node->left) nextFloor.push(node->left);
            if (node->right) nextFloor.push(node->right);

            if (thisFloor.empty())
            {
                std::swap(thisFloor, nextFloor);
                std::cout << std::endl;
            }
        }

    }
}
void BinarySearchTree::makeEmpty()
{
	makeEmpty(root);
}


void BinarySearchTree::insert(const int & x)
{
	insert(x, root);
}

void BinarySearchTree::insert(int && x)
{
	insert(std::move(x), root);
}

void BinarySearchTree::remove(const int & x)
{
	remove(x, root);
}

void BinarySearchTree::insert(const int & x, BinaryNode * & t)
{
	if (t == nullptr)
		t = new BinaryNode{ x, nullptr, nullptr };
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	else
		;  // Duplicate; do nothing
}


void BinarySearchTree::insert(int && x, BinaryNode * & t)
{
	if (t == nullptr)
		t = new BinaryNode{ std::move(x), nullptr, nullptr };
	else if (x < t->element)
		insert(std::move(x), t->left);
	else if (t->element < x)
		insert(std::move(x), t->right);
	else
		;  // Duplicate; do nothing
}

void BinarySearchTree::remove(const int & x, BinaryNode * & t)
{
	if (t == nullptr)
		return;   // Item not found; do nothing
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		BinaryNode *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

BinaryNode * BinarySearchTree::findMin(BinaryNode *t) const
{
	if (t == nullptr)
		return nullptr;
	if (t->left == nullptr)
		return t;
	return findMin(t->left);
}

BinaryNode * BinarySearchTree::findMax(BinaryNode *t) const
{
	if (t != nullptr)
		while (t->right != nullptr)
			t = t->right;
	return t;
}

bool BinarySearchTree::contains(const int & x, BinaryNode *t) const
{
	if (t == nullptr)
		return false;
	else if (x < t->element)
		return contains(x, t->left);
	else if (t->element < x)
		return contains(x, t->right);
	else
		return true;    // Match
}

void BinarySearchTree::makeEmpty(BinaryNode * & t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}


void BinarySearchTree::printElement(BinaryNode *t, int floor) const
{
    for (int i = 0; i < floor; i++)
        std::cout << " ";
    std::cout << t->element << std::endl;
}

void BinarySearchTree::printTree(BinaryNode *t, eTraversals traversal, int floor) const
{
	if (t != nullptr)
	{
        if (traversal == PRE) printElement(t, floor);
		printTree(t->left, traversal, floor+1);
        if (traversal == IN) printElement(t, floor);
		printTree(t->right, traversal, floor + 1);
        if (traversal == POST) printElement(t, floor);
	}
}

BinaryNode * BinarySearchTree::clone(BinaryNode *t) const
{
	if (t == nullptr)
		return nullptr;
	else
		return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
}


void BinarySearchTree::countNodes() const
{
    std::cout << "Nr of nodes: " << _countNodes(root) << std::endl;
}

void BinarySearchTree::countFullNodes() const
{
    std::cout << "Nr of full nodes: " << _countFullNodes(root) << std::endl;
}

void BinarySearchTree::countLeafs() const
{
    std::cout << "Nr of leafs: " << _countLeafs(root) << std::endl;
}

// O(N) - we have to go through every node, we could cache this number to get O(1) for few bytes of memory
int BinarySearchTree::_countNodes(BinaryNode *node) const
{
    return node ? 1 + _countNodes(node->left) + _countNodes(node->right) : 0;
}

// O(N) - we have to go through every node, we could cache this number to get O(1) for few bytes of memory
int BinarySearchTree::_countFullNodes(BinaryNode *node) const
{
    return node ? (node->left && node->right) + _countFullNodes(node->left) + _countFullNodes(node->right) : 0;
}

// O(N) - we have to go through every node, we could cache this number to get O(1) for few bytes of memory
int BinarySearchTree::_countLeafs(BinaryNode* node) const
{
    return node ? (!node->left && !node->right) + _countLeafs(node->left) + _countLeafs(node->right) : 0;
}

void BinarySearchTree::internalPathLenght() const
{
    std::cout << "Internal path lenght: " << _internalPathLenght(root,0) << std::endl;
}
int BinarySearchTree::_internalPathLenght(BinaryNode* node, int floor) const
{
    return node ? floor + _internalPathLenght(node->left, floor + 1) + _internalPathLenght(node->right, floor+1): 0;
}
