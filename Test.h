#pragma once
class Test
{
	class Node {

	public:
		int key;
		Node* leftPtr, * rightPtr;
	};

	Node* newNode(int key);
	Node* rotateRight(Node* x);
	Node* rotateLeft(Node* x);
	Node* splay(Node* root, int key);
	Node* findMin(Node* root);
	Node* search(Node* node, int key);
	Node* insertNode(Node* root, int key);
	Node* deleteNode(Node* root, int key);
	void printTree(Node* root);

};


