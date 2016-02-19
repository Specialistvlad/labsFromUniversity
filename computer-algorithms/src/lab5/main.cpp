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

	int cntr = cnt / 2;
	int cntl = cnt - cntr;

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
	#define ARRSIZE 14
	int data[ARRSIZE] = {25, 50, 10, 5, 30, 55, 0, 40, 35, 15, 45, 60, 75, 70};

	cout << "Exer.1 - Balanced B-Tree" << endl;
	Node* node = NULL;
	int *it = (int *)&data;
	printPretty(createBalancedTree(&node, it, ARRSIZE));
	return 0;
}
