#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;

#include "Binary-tree.hpp"
#include "pretty-print.hpp"

// Функция создает сбалансированное дерево и возращает корневой узел дерева
Node* createBalancedBTree(Node** node, int *&value, int cnt)
{
	if (cnt <= 0)
		return NULL;

	if (node == NULL) {
		Node* tmp = NULL;
		node = &tmp;
	}

	if ((*node) == NULL) {
		(*node) = new Node(*value);
		++value;
		--cnt;
	}

	int cntr = cnt / 2;
	int cntl = cnt - cntr;

	if (cntl > 0)
		createBalancedBTree(&(*node)->left, value, cntl);

	if (cntr > 0)
		createBalancedBTree(&(*node)->right, value, cntr);
	return (*node);
}

// Функция создает бинарное дерево поиска и возращает корневой узел дерева
Node* insertSearchBTree(Node** node, int value)
{
	if ((*node) == NULL) {
		(*node) = new Node(value);
		return *node;
	}

	if ((*node)->data > value) {
		return insertSearchBTree(&(*node)->left, value);
	} else if ((*node)->data < value) {
		return insertSearchBTree(&(*node)->right, value);
	} else {
		std::cout << "something going wrong! " << value << endl;
	}
}

// Функция создает бинарное дерево поиска и возращает корневой узел дерева
Node* createSearchBTree(int *array, int size)
{
	Node* node = NULL;
	for (int i = 0; i < size; ++i)
		insertSearchBTree(&node, array[i]);
	return node;
}

void findRowsSumm(Node *node, int *rows, int currentDepth)
{
	if (node == NULL)
		return;

	rows[currentDepth] += node->data;
	findRowsSumm(node->left, rows, currentDepth+1);
	findRowsSumm(node->right, rows, currentDepth+1);
}

int findRowWithMaxSumm(Node *node, int rowsCount)
{
	if (node == NULL)
		return -1;

	int *rowsSumm = new int[rowsCount];
	for (int i = 0; i < rowsCount; ++i)
		rowsSumm[i] = 0;

	findRowsSumm(node, rowsSumm, 0);

	int maxRow = -1;
	int maxValue = 0;
	for (int i = 0; i < rowsCount; i++)
	{
		if ((rowsSumm[i] >= 0) && (rowsSumm[i] > maxValue)) {
			maxRow = i;
			maxValue = rowsSumm[i];
		}
	}
	delete [] rowsSumm;
	return maxRow;
}

void free(Node *node) {
	if (node != NULL) {
		free(node->left);
		free(node->right);
	}

	delete node;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
Node * minValueNode(Node* node)
{
	Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
Node* deleteNode(Node **root, int data)
{
	// base case
	if ((*root) == NULL)
		return (*root);

	// If the key to be deleted is smaller than the root's key,
	// then it lies in left subtree
	if (data < (*root)->data)
		(*root)->left = deleteNode(&(*root)->left, data);

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (data > (*root)->data)
		(*root)->right = deleteNode(&(*root)->right, data);

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if ((*root)->left == NULL)
		{
			Node *temp = (*root)->right;
			free((*root));
			return temp;
		}
		else if ((*root)->right == NULL)
		{
			Node *temp = (*root)->left;
			free((*root));
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		Node * temp = minValueNode((*root)->right);

		// Copy the inorder successor's content to this node
		(*root)->data = temp->data;

		// Delete the inorder successor
		(*root)->right = deleteNode(&(*root)->right, temp->data);
	}
	return (*root);
}

void exer1(int *data, int size) {
	cout << "Exer.1 - Balanced B-Tree" << endl;
	int *it = (int *)&(*data);
	Node* balancedBTreeRoot = createBalancedBTree(NULL, it, size);
	printPretty(balancedBTreeRoot);
	free(balancedBTreeRoot);
	cout << endl;
}

void exer2(int *data, int size) {
	cout << "Exer.2 - Search B-Tree" << endl;
	Node* searchBTreeRoot = createSearchBTree(data, size);
	printPretty(searchBTreeRoot);
	free(searchBTreeRoot);
	cout << endl;
}

void exer3(int *data, int size) {
	cout << "Exer.3 - Delete nodes from B-Tree" << endl;
	Node* root = createSearchBTree(data, size);

	cout << "Delete node with one children" << endl;
	deleteNode(&root, 5);
	printPretty(root);
	cout << endl;

	cout << "Delete node with two childrens" << endl;
	deleteNode(&root, 15);
	printPretty(root);

	//cout << "Delete terminal node(root)" << endl;
	//root = deleteNode(&root, 35);
	//printPretty(root);

	free(root);
	cout << endl;
}

void exer6(int *data, int size) {
	cout << "Exer.6 - Find row with max summ" << endl;
	cout << "Rows indexing start from 0, -1 = no values found" << endl;
	int *it6 = (int *)&(*data);
	Node * tree6 = createBalancedBTree(NULL, it6, size);
	printPretty(tree6);
	int row = findRowWithMaxSumm(tree6, size);
	free(tree6);
	cout << "Answer is " << row << endl;
	cout << endl;
}

int main()
{
	int data[] = {35, 55, 15, 50, 40, 0, 10, 45, 5, 30, 25};
	int size = sizeof(data) / (sizeof(data[0]));

	exer1(data, size);
	exer2(data, size);
	exer3(data, size);
	// exer4(data, size);
	// exer5(data, size);
	exer6(data, size);

	return 0;
}
