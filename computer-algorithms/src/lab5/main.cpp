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

int main()
{
	int data[] = {25, 50, 55, 0, 10, 5, 30, 40, 35, 15, 45, 60, 75, 70};
	int size = sizeof(data) / (sizeof(data[0]));

	cout << "Exer.1 - Balanced B-Tree" << endl;
	int *it = (int *)&data;
	printPretty(createBalancedBTree(NULL, it, size));
	cout << endl;

	cout << "Exer.2 - Search B-Tree" << endl;
	printPretty(createSearchBTree(data, size));

	return 0;
}
