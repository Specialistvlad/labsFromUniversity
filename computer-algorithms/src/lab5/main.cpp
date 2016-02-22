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
	return maxRow;
}

int main()
{
	int data[] = {35, 55, 15, 50, 40, 0, 10, 45, 5, 30, 25};
	int size = sizeof(data) / (sizeof(data[0]));

	cout << "Exer.1 - Balanced B-Tree" << endl;
	int *it = (int *)&data;
	Node* balancedBTreeRoot = createBalancedBTree(NULL, it, size);
	printPretty(balancedBTreeRoot);
	cout << endl;

	cout << "Exer.2 - Search B-Tree" << endl;
	Node* searchBTreeRoot = createSearchBTree(data, size);
	printPretty(searchBTreeRoot);
	cout << endl;

	cout << "Exer.6 - Find row with max summ of values from search B-Tree" << endl;
	printPretty(searchBTreeRoot);
	cout << "Count starts from 0, -1 = no values found" << endl;
	cout << "Answer is " << findRowWithMaxSumm(searchBTreeRoot, size) << endl;
	cout << endl;

	return 0;
}
