struct Node {
	int data;
	Node *left;
	Node *right;
	Node(int val) : left(NULL), right(NULL), data(val) { }
	Node() : left(NULL), right(NULL), data(0) { }
};
