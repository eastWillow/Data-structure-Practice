#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM 

typedef struct _Node
{
	void* parent;
	void* left;
	void* right;
	uint16_t data;
	uint16_t same;
} Node;

void createTree(_Out_ Node* *parents, _In_ uint16_t* data, size_t dataSize);
Node* addLeaf(_In_ Node* parents, uint16_t newData);
Node* removeLead(_In_ Node* parents, uint16_t targetData);
void printTree(_In_ Node* root);

uint8_t main(void) {
	Node* root = NULL;

#ifndef RANDOM
	uint16_t data[10] = { 12,13,14,15,16,17,18,19,20 };
#endif // !RANDOM
#ifdef RANDOM
	uint16_t data[10];
	size_t size = sizeof(data) / sizeof(data[0]);
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		data[i] = rand() % size + 50;
	}
#endif // RANDOM

	createTree(&root, data, size);
	addLeaf(root, 30);
	addLeaf(root, 2000);
	printTree(root);

	printf("\nPause! Please press any button");
	getchar();
	return 0;
}

void createTree(_Out_ Node* *parents, _In_ uint16_t* data, size_t dataSize) {
	((Node*)*parents) = (Node*)malloc(sizeof(Node));
	((Node*)*parents)->parent = NULL;
	((Node*)*parents)->left = NULL;
	((Node*)*parents)->right = NULL;
	((Node*)*parents)->same = 0;
	((Node*)*parents)->data = data[0];

	for (int i = 1; i < dataSize; i++) {
		addLeaf(((Node*)*parents), data[i]);
	}
}

Node* addLeaf(_In_ Node* parents, uint16_t newData) {
	if (newData < parents->data) {
		if (parents->left == NULL) {
			parents->left = (Node*)malloc(sizeof(Node));
			((Node*)parents->left)->parent = parents;
			((Node*)parents->left)->data = newData;
			((Node*)parents->left)->left = NULL;
			((Node*)parents->left)->right = NULL;
			((Node*)parents->left)->same = 0;
			return parents->left;
		}
		else {
			addLeaf(parents->left, newData);
		}
	}
	else if (newData > parents->data) {
		if (parents->right == NULL) {
			parents->right = (Node*)malloc(sizeof(Node));
			((Node*)parents->right)->parent = parents;
			((Node*)parents->right)->data = newData;
			((Node*)parents->right)->left = NULL;
			((Node*)parents->right)->right = NULL;
			((Node*)parents->right)->same = 0;
			return parents->right;
		}
		else {
			addLeaf(parents->right, newData);
		}
	}
	else {
		parents->same += 1;
		return parents;
	}
}

void printTree(_In_ Node* parents) {
	if (parents->left != NULL) {
		printTree(parents->left);
		printf("%d:%d ", parents->data, parents->same + 1);
	}
	if (parents->right != NULL) {
		if (parents->left == NULL)
			printf("%d:%d ", parents->data, parents->same + 1);
		printTree(parents->right);
	}
	if (parents->left == NULL && parents->right == NULL) {
		printf("%d:%d ", parents->data, parents->same + 1);
	}
}