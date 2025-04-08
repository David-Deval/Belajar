//BST

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	int x;
	char nam[20];
	struct tnode *right;
	struct tnode *left;
}*root;

struct tnode *createnode(int x, char nam[]){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->x = x;
	strcpy(newnode->nam, nam);
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

struct tnode *insertw(struct tnode *parrent, int x, char nam[]){
	if(parrent == NULL){
		return createnode(x,nam);
	}
	if(x<parrent->x){
		parrent->left = insertw(parrent->left,x, nam);
	}else{
		parrent->right = insertw(parrent->right, x, nam);
	}
	return parrent;
}

struct tnode* findMin(struct tnode* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

struct tnode *deletenode(struct tnode* node, int x) {
	if (node == NULL) return NULL;

	if (x < node->x) {
		node->left = deletenode(node->left, x);
	} else if (x > node->x) {
		node->right = deletenode(node->right, x);
	} else {
		// Node ketemu
		if (node->left == NULL && node->right == NULL) {
			free(node);
			return NULL;
		} else if (node->left == NULL) {
			struct tnode* temp = node->right;
			free(node);
			return temp;
		} else if (node->right == NULL) {
			struct tnode* temp = node->left;
			free(node);
			return temp;
		} else {
			struct tnode* temp = findMin(node->right);
			node->x = temp->x;
			strcpy(node->nam, temp->nam);
			node->right = deletenode(node->right, temp->x);
		}
	}
	return node;
}

void inorder(struct tnode* node) {
	if (node != NULL) {
		inorder(node->left);
		printf("%d %s\n", node->x, node->nam);
		inorder(node->right);
	}
}

void preorder(struct tnode* node) {
	if (node != NULL) {
		printf("%d %s\n", node->x, node->nam);
		preorder(node->left);
		preorder(node->right);
	}
}

void postorder(struct tnode* node) {
	if (node != NULL) {
		postorder(node->left);
		postorder(node->right);
		printf("%d %s\n", node->x, node->nam);
	}
}

int main() {
	root = insertw(root, 50, "Alpha");
	root = insertw(root, 30, "Beta");
	root = insertw(root, 70, "Gamma");
	root = insertw(root, 20, "Delta");
	root = insertw(root, 40, "Epsilon");
	root = insertw(root, 60, "Zeta");
	root = insertw(root, 80, "Eta");

	printf("Inorder:\n");
	inorder(root);

	printf("\nPreorder:\n");
	preorder(root);

	printf("\nPostorder:\n");
	postorder(root);

	// Hapus node
	printf("\n\nSetelah menghapus 30:\n");
	root = deletenode(root, 30);
	inorder(root);

	return 0;
}


