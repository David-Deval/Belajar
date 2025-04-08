//tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	int x;
	char nam[20];
	struct tnode *left;
	struct tnode *right;
}*root;

struct tnode *createnode(int x, char nam[]){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->x = x;
	strcpy(newnode->nam,nam);
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

void insert_left(struct tnode *parrent, int x, char nam[]){
	if(parrent == NULL){
		printf("Data is invalid\n");
	}
	if(parrent != NULL){
		printf("Kiri dari node %s sudah terisi!\n", parrent->nam);
    return;
    }
    parrent->left = createnode(x, nam);
}

void insert_right(struct tnode *parrent, int x, char nam[]){
	if(parrent == NULL){
		printf("Invalid Present\n");
	}
	if(parrent != NULL){
		printf("Kana dari node %s sudah terisi\n",parrent->nam);
	return;
	}
	parrent = parrent->right;
}

int main(){
	root = createnode(1,"Dwa");
	insert_left(root,2,"DAa");
	insert_right(root,3,"Daw");
	
	return 0;
}
