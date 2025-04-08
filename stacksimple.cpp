// stack 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
	int x;
	char nam[20];
	struct tnode *next;
}*head;

struct tnode *createnode(int x, char nam[]){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->x = x;
	strcpy(newnode->nam, nam);
	newnode->next = NULL;
	return newnode; 
} 

void push_front(int x, char nam[]){
	struct tnode *node = createnode(x,nam);
	
	if(head == NULL){
		head = node;
	}else{
		node->next = head;
		head = node;
	}
} 

void delete_front(){
	if (head == NULL){
		printf("No Stack Yet\n");
	}else{
		struct tnode *del = head;
		head = head->next;
		free(del);
	}
}

void printlist(){
	struct tnode *curr = head;
	while (curr != NULL){
		printf("%d %s\n", curr->x,curr->nam);
	curr = curr->next;
}
}

int main(){
	push_front(1, "David");
	push_front(2, "Aldi");
	push_front(3, "Rina");

	printf("Isi stack:\n");
	printlist();

	printf("\nSetelah satu kali pop:\n");
	delete_front();
	printlist();

	return 0;
}

