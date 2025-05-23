#include <iostream>
using namespace std;
#include <queue>
#include "Test.h"
class Node {

	public:
		int key;
		Node *leftPtr, *rightPtr;
};
Node* newNode(int key) {
	Node* node = new Node();
	node->key = key;
	node->leftPtr = NULL;
	node->rightPtr = NULL;
	return (node);

}

//фукнция для поворота вправо
Node* rotateRight(Node *x) {
	Node* y = x->leftPtr;
	x->leftPtr = y->rightPtr;
	y->rightPtr = x;
	return y;

}

//функция для поворота влево
Node* rotateLeft(Node *x) {
	Node* y = x->rightPtr;
	x->rightPtr = y->leftPtr;
	y->leftPtr = x;
	return y;
}


Node* splay(Node* root, int key) {
	if (root == NULL) {
		return root;
	}
	if (root->key > key) {
		
		if (root->leftPtr == NULL) {
			return root;
		}

		//Zig-Zig
		if (root->leftPtr->key > key) {
			root->leftPtr->leftPtr = splay(root->leftPtr->leftPtr, key);

			root = rotateRight(root);
		}

		//Zig-Zag
		else if (root->leftPtr->key < key) {
			root->leftPtr->rightPtr = splay(root->leftPtr->rightPtr, key);
			if (root->leftPtr->rightPtr != NULL) {
				root->leftPtr = rotateLeft(root->leftPtr);
			}
		}
		
		if (root->leftPtr == NULL) {
			return root;
		}
		else {
			return rotateRight(root);
		}
		
	}

	else {

		   
		if (root->rightPtr == NULL) {
			return root;
		}

		//Zag-Zag
		if (root->rightPtr->key < key) {
			root->rightPtr->rightPtr = splay(root->rightPtr->rightPtr, key);

			root = rotateLeft(root);

		}

		//Zag-Zig
		if (root->rightPtr->key > key) {
			root->rightPtr->leftPtr = splay(root->rightPtr->leftPtr, key);
			if (root->rightPtr->leftPtr != NULL) {
				root->rightPtr = rotateRight(root->rightPtr);
			}
		}
		if (root->rightPtr == NULL) {
			return root;
		}
		else {
			return rotateLeft(root);
		}

	}
}

//функция для поиска узла
Node* search(Node* node, int key) {
	return splay(node, key);
}


//вставка узла в дерево
Node* insertNode(Node* root, int key) {
	if (!root) return newNode(key);
	root = splay(root, key);  // Поднимаем узел наверх перед вставкой
	if (root->key == key) return root;  //проверка на наличие ключа

	Node *newNode = new Node();
	newNode->key = key;
	if (key < root->key) {// если ключ меньше,следовательно идём в правое поддереве, в противном случае в левое
		newNode->rightPtr = root;
		newNode->leftPtr = root->leftPtr;
		root->leftPtr = NULL;
	}
	else {
		newNode->leftPtr = root;
		newNode->rightPtr = root->rightPtr;
		root->rightPtr = NULL;
	}
	return newNode;
}

//функция для находъждения минимального значения в правом поддереве
Node* findMin(Node* root) {
	while (root && root->leftPtr) root = root->leftPtr;
	return root;
}

//функция для удаления узла
Node* deleteNode(Node* root, int key) {
	if (!root) return NULL;
	root = splay(root, key);  
	if (root->key != key) return root; // проверка на наличие ключа


	if (!root->leftPtr) return root->rightPtr;
	if (!root->rightPtr) return root->leftPtr;

	
	Node* replacement = findMin(root->rightPtr);
	replacement->rightPtr = splay(replacement->rightPtr, replacement->key);
	replacement->leftPtr = root->leftPtr;
	delete root;
	return replacement;
}

// функция вывода дерева
void printTree(Node* root) {
	if (root == NULL) {
		cout << "Дерево пустое." << endl;
		return;
	}

	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		int levelSize = q.size(); // Узнаем количество элементов текущего уровня

		for (int i = 0; i < levelSize; ++i) {
			Node* node = q.front();
			q.pop();

			cout << node->key << ' ';

			if (node->leftPtr)
				q.push(node->leftPtr);

			if (node->rightPtr)
				q.push(node->rightPtr);
		}

		cout << endl; // Переходим на новую строку между уровнями
	}
}


int main() {
	Node* root = newNode(100);
	root->leftPtr = newNode(50);
	root->rightPtr = newNode(200);
	root->leftPtr->leftPtr = newNode(40);
	root->leftPtr->leftPtr->leftPtr = newNode(30);
	root->leftPtr->leftPtr->leftPtr->leftPtr = newNode(20);
	root = insertNode(root, 150);
	root = search(root, 30);

	printTree(root);
}