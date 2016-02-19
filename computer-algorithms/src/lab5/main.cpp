#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;

#include "Binary-tree.hpp"
#include "pretty-print.hpp"

// Функция создает сбалансированное дерево и возращает корневой узел дерева
Node* createBalancedTree(Node** node, int *&val, int cnt)
{
	if (cnt <= 0)
		return NULL;

	if ((*node) == NULL) {
		(*node) = new Node(*val);
		++val;
		--cnt;
	}

	int cntl = cnt / 2;
	int cntr = cnt - cntl;

	if (cntl > 0) {
		createBalancedTree(&(*node)->left, val, cntl);
	}

	if (cntr > 0) {
		createBalancedTree(&(*node)->right, val, cntr);
	}
	return (*node);
}

int main()
{
	#define ARRSIZE 11
	int data[ARRSIZE] = {25, 50, 10, 5, 30, 55, 0, 40, 35, 15, 45};
	for (int i = 0; i < ARRSIZE; i++)
		cout << data[i] << " ";
	cout << endl << endl;

	// Exer.1 - Balanced B-Tree
	Node* node = NULL;
	int *it = (int *)&data;
	printPretty(createBalancedTree(&node, it, ARRSIZE));
	return 0;
}
