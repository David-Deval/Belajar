// queu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	int x;
	char nam[20];
	struct tnode *next;
}*head,*tail;

struct tnode *createnode(int x, char nam[]){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	newnode->x = x;
	strcpy(newnode->nam, nam);
	newnode->next = NULL;
	return newnode; 
} 

void push_back(int x, char nam[]){
	struct tnode *node = createnode(x,nam);
	
	if(tail == NULL){
		head = tail = node;
	}else{
		tail->next = node;
		tail = node;
	}
}

void delete_front(){
	if(head == NULL){
		tail == NULL;
		printf("No data yet\n");
	}else{
		struct tnode *del = head;
		head = head->next;
		free(del);
	}
}

void printlist(){
	struct tnode *curr = head;
	while (curr != NULL){
		printf("%d %s\n",curr->x,curr->nam);
		curr = curr->next;
	}
}

int main(){
	
	push_back(1,"dana");
	push_back(2,"yose");
	push_back(3,"yono");
	printlist();
	
	printf("Setelah popout\n");
	delete_front();
	printlist();
	
	return 0;
}
