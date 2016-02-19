#include <iostream>
#include <queue>
using namespace std;

#include "Binary-tree.hpp"
#include "pretty-print.hpp"

// Создание листа со значением(первы параметр) в конце дерева начиная от узла(второй параметр)
Node* createSampleTreeDirect()
{
	Node *root = new Node(30);
	root->left = new Node(20);
	root->right = new Node(40);

	root->left->left = new Node(10);
	root->left->right = new Node(25);
	root->right->left = new Node(35);
	root->right->right = new Node(50);

	root->left->left->left = new Node(5);
	root->left->left->right = new Node(15);
	root->left->right->right = new Node(28);
	root->right->right->left = new Node(41);

	return root;
}

int main()
{
	Node *root = createSampleTreeDirect();
	printPretty(root, 1, 0, cout);
	return 0;
}
