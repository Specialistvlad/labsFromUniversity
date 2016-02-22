struct Node {
	int data;
	Node *left;
	Node *right;
	int height; // Use only in AVL B-Tree
	Node(int val) : left(NULL), right(NULL), data(val) { }
	Node() : left(NULL), right(NULL), data(0), height(1) { }
};
