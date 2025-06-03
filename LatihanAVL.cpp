#include <stdio.h>
#include <stdlib.h>

struct tnode{
	int value;
	struct tnode *left;
	struct tnode *right;
	int height;
};

struct tnode *createNode(int key){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->value = key;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->height = 1;
	
	return newnode;
}

int getHeight(tnode *node){
	if(node == NULL){
		return 0;
	}
	return node->height;
}

int getBalance(tnode *node){
	if(node == NULL){
		return 0;
	}
	return getHeight(node->left)  - getHeight(node->right);
}

int max(int a, int b){
	if(a > b){
		return a;
	}else {
		return b;
	}
}

struct tnode *RightR(tnode *node){
	struct tnode *a = node->left;
	struct tnode *b = a->right;
	
	a->right = node;
	node->left = b;
	
	node->height = 1 + max(getHeight(node->left),getHeight(node->right));
	a->height = 1 + max(getHeight(a->left),getHeight(a->right));
	
	return a;
}

struct tnode *LeftR(tnode *node){
	struct tnode *a = node->right;
	struct tnode *b = a->left;
	
	a->left = node;
	node->right = b;
	
	node->height = 1 + max(getHeight(node->left),getHeight(node->right));
	a->height = 1 + max(getHeight(a->left),getHeight(a->right));
	
	return a;
}

struct tnode *minvalue(struct tnode *node){
	struct tnode *curr = node;
	while(curr->left != NULL){
		curr = curr->left;
	}
	return curr;
}

struct tnode *insertNode(tnode *node, int key){
	struct tnode *temp = createNode(key);
	
	if(node == NULL){
		return temp;
	}
	
	if(key < node->value){
		node->left =  insertNode(node->left, key);
	}else if(key > node->value){
		node->right =  insertNode(node->right, key);
	}
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int balance = getBalance(node);
	
	if(balance > 1 && key < node->left->value){
		return RightR(node);
	}else if(balance > 1 && key > node->left->value){
		node->left = LeftR(node->left);
		return RightR(node);
	}
	
	if(balance < -1 && key > node->right->value){
		return LeftR(node);
	}else if(balance < -1 && key < node->right->value){
		node->right = RightR(node->right);
		return LeftR(node);
	}
	
	return node;
}

struct tnode *deletenode(tnode *node,int key){
	if (node == NULL){
		return node;
	}
	
	if(key < node->value){
		node->left = deletenode(node->left,key);
	}else if(key > node->value){
		node->right = deletenode(node->right,key);
	}else{
		if(node->left == NULL || node->right == NULL){
			struct tnode *temp;
			if(node->left){
				temp = node->left;
			}else{
				temp = node->right;
			}
			if(temp == NULL){
				temp = node;
				node = NULL;
			}else{
				*node = *temp;
				free(temp);
			}
		}else{
			struct tnode *temp = minvalue(node->right);
			node->value = temp->value;
			node->right = deletenode(node->right,temp->value);
		}
	}
	return node;
}

void Inorder(tnode *node){
	if(node != NULL){
		Inorder(node->left);
		printf("%d ",node->value);
		Inorder(node->right);
	}
}

int main(){
	struct tnode *root = NULL;
	
	int n, value;
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		scanf("%d",&value);
		root = insertNode(root,value);
	}
	
	Inorder(root);
	
	printf("\n");
	
	int del, x;
	scanf("%d",&del);
	printf("\n");
	
	for(int i=0;i<del;i++){
		scanf("%d",&x);
		root = deletenode(root,x);
	}
	
	Inorder(root);
}
