//This code from here http://articles.leetcode.com/how-to-pretty-print-binary-tree

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

#include "Binary-tree.hpp"

#define LEVEL 1
#define INDENTSPACE 1

// Find the maximum height of the binary tree
int maxHeight(Node *p) {
	if (!p) return 0;
	int leftHeight = maxHeight(p->left);
	int rightHeight = maxHeight(p->right);
	return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Convert an integer value to string
string intToString(int val) {
	ostringstream ss;
	ss << val;
	return ss.str();
}

// Print the arm branches (eg, /\ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
	deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel / 2; i++) {
		out << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
		out << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
	}
	out << endl;
}

// Print the branches and node (eg, ___10___ )
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
	deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
		out << setw(branchLen+2) << ((*iter) ? intToString((*iter)->data) : "");
		out << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
	}
	out << endl;
}

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue, ostream& out) {
	deque<Node*>::const_iterator iter = nodesQueue.begin();
	for (int i = 0; i < nodesInThisLevel; i++, iter++) {
		out << ((i == 0) ? setw(indentSpace+2) : setw(2*level+2)) << ((*iter) ? intToString((*iter)->data) : "");
	}
	out << endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// levelControl how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpaceChange this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void _printPretty(Node *root, int level, int indentSpace, ostream& out) {
	int h = maxHeight(root);
	int nodesInThisLevel = 1;

	int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);// eq of the length of branch for each node of each level
	int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);// distance between left neighbor node's right arm and right neighbor node's left arm
	int startLen = branchLen + (3-level) + indentSpace;// starting space to the first node to print of each level (for the left most node of each level only)

	deque<Node*> nodesQueue;
	nodesQueue.push_back(root);
	for (int r = 1; r < h; r++) {
		printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
		branchLen = branchLen/2 - 1;
		nodeSpaceLen = nodeSpaceLen/2 + 1;
		startLen = branchLen + (3-level) + indentSpace;
		printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

		for (int i = 0; i < nodesInThisLevel; i++) {
		Node *currNode = nodesQueue.front();
		nodesQueue.pop_front();
		if (currNode) {
			nodesQueue.push_back(currNode->left);
			nodesQueue.push_back(currNode->right);
		} else {
			nodesQueue.push_back(NULL);
			nodesQueue.push_back(NULL);
		}
		}
		nodesInThisLevel *= 2;
	}
	printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
	printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}

void printPretty(Node *root) {
	_printPretty(root, LEVEL, INDENTSPACE, cout);
}
