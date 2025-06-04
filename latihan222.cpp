#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	char id[100];
	int value;
	struct tnode *left;
	struct tnode *right;
	int height;
};

struct tnode *createnode(char id[], int value){
	struct tnode *newnode = (struct tnode*)malloc(sizeof(struct tnode));
	strcpy(newnode->id, id);
	newnode->value = value;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->height = 1;
	
	return newnode;
};

int max(int a, int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

int getheight(tnode *node){
	if(node == NULL){
		return 0;
	}else{
		return node->height;
	}
}

int getbalance(tnode *node){
	if(node == NULL){
		return 0;
	}else{
		return getheight(node->left) - getheight(node->right);
	}
}

struct tnode *LLCase(tnode *node){
	struct tnode *a= node->left;
	struct tnode *b= a->right;
	
	a->right = node;
	node->left = b;
	
	node->height = 1 + max(getheight(node->left), getheight(node->right));
	a->height = 1 + max(getheight(a->left), getheight(a->right));
	
	return a;
}

struct tnode *RRCase(tnode *node){
	struct tnode *a = node->right;
	struct tnode *b = a->left;
	
	a->left = node;
	node->right = b;
	
	node->height = 1 + max(getheight(node->left), getheight(node->right));
	a->height = 1 + max(getheight(a->left), getheight(a->right));
	
	return a;
}

struct tnode *minvalue(tnode *node){
	struct tnode *curr = node;
	while(curr->left != NULL){
		curr = curr->left;
	}
	return curr;
}

// insert by value
struct tnode *insertnode(tnode *node, char id[], int value){
	struct tnode *temp = createnode(id, value);
	
	if(node == NULL){
		return temp;
	}
	
	if(value < node->value){
		node->left = insertnode(node->left,id,value);
	}else if(value > node->value){
		node->right = insertnode(node->right,id,value);
	}else{
		return node;
	}
	
	node->height = 1 + max(getheight(node->left),getheight(node->right));
	int balance = getbalance(node);
	
	if(balance > 1 && value < node->left->value){
		return LLCase(node);
	}else if(balance > 1 && value > node->left->value){
		node->left = RRCase(node->left);
		return LLCase(node);
	}
	if(balance < -1 && value > node->right->value){
		return RRCase(node);
	}else if (balance < -1 && value < node->right->value){
		node->right =  LLCase(node->right);
		return RRCase(node);
	}
	
	return node;
}

int compare(char id[], char id2[]){
	int result = strcmp(id, id2);
	if(result < 0 ){
		return -1;
	}else if(result > 0){
		return 1;
	}else{
		return 0;
	}
}
// insert by id
struct tnode *insertnodes(tnode *node, char id[], int value){

	if(node == NULL){
		return createnode(id, value);
	}
	
	int cmp = compare(id,node->id);
	
	if(cmp < 0 ){ // kalau lebih kecil dari root
		node->left = insertnodes(node->left,id,value);
	}else if(cmp > 0){ // kalau lebih gede dari root
		node->right = insertnodes(node->right,id,value);
	}else{
		return node;
	}
	
	node->height = 1 + max(getheight(node->left),getheight(node->right));
	int balance = getbalance(node);
	
	if(balance > 1 && compare(id,node->left->id)<0){
		return LLCase(node);
	}else if(balance > 1 && compare(id,node->left->id)>0){
		node->left = RRCase(node->left);
		return LLCase(node);
	}
	if(balance < -1 && compare(id,node->right->id)>0){
		return RRCase(node);
	}else if (balance < -1 && compare(id,node->right->id)<0){
		node->right =  LLCase(node->right);
		return RRCase(node);
	}
	
	return node;
}

struct tnode *deletenode (tnode *node, char id[],int value){
	if(node == NULL){
		return node;
	}
	
	if(value < node->value){
		node->left = deletenode(node->left, id, value);
	}else if(value > node->value){
		node->right = deletenode(node->right, id, value);
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
		}
		else{
			struct tnode *temp = minvalue(node->right);
			node->value = temp->value;
			strcpy(node->id, temp->id); 
			node->right = deletenode(node->right,temp->id,temp->value);
		}
	}
	
	if(node == NULL){
		return node;
	}
	
	node->height = 1 + max(getheight(node->left),getheight(node->right));
	int balance = getbalance(node);
	
	if(balance > 1 && getbalance(node->left) >= 0){
		return LLCase(node);
	}else if(balance > 1 && getbalance(node->left) < 0){
		node->left = RRCase(node->left);
		return LLCase(node);
	}
	if(balance < -1 && getbalance(node->right) <= 0){
		return RRCase(node);
	}else if(balance < -1 && getbalance(node->right) > 0){
		node->right = LLCase(node->right);
	}
	
	return node;
}


struct tnode *deletenodes (tnode *node, char id[],int value){
	if(node == NULL){
		return node;
	}
	
	int cmp = compare(id, node->id);
	
	if(cmp < 0){
		node->left = deletenode(node->left, id, value);
	}else if(cmp > 0){
		node->right = deletenode(node->right, id, value);
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
		}
		else{
			struct tnode *temp = minvalue(node->right);
			node->value = temp->value;
			strcpy(node->id, temp->id); 
			node->right = deletenode(node->right,temp->id,temp->value);
		}
	}
	
	if(node == NULL){
		return node;
	}
	
	node->height = 1 + max(getheight(node->left),getheight(node->right));
	int balance = getbalance(node);
	
	if(balance > 1 && getbalance(node->left) >= 0){
		return LLCase(node);
	}else if(balance > 1 && getbalance(node->left) < 0){
		node->left = RRCase(node->left);
		return LLCase(node);
	}
	if(balance < -1 && getbalance(node->right) <= 0){
		return RRCase(node);
	}else if(balance < -1 && getbalance(node->right) > 0){
		node->right = LLCase(node->right);
	}
	
	return node;
}

//void Inorder1(tnode *node){
//	while(node != NULL){
//		Inorder(node->left);
//		printf("%d",node->value);
//		Inorder(node->right);
//	}
//}
//
//void Inorder2(tnode *node){=
//	while(node != NULL){
//		Inorder(node->left);
//		printf("%s",node->id);
//		Inorder(node->right);
//	}
//}

void inorder(struct tnode *node) {
    if (node == NULL) return;
    inorder(node->left);
    printf("ID: %s | Value: %d\n", node->id, node->value);
    inorder(node->right);
}

int main() {
    struct tnode *root = NULL;
    int n, value;
    char id[100];
    int sortChoice;

    printf("Berapa banyak data yang ingin dimasukkan? ");
    scanf("%d", &n);

    printf("Pilih metode penyusunan tree:\n");
    printf("1. Berdasarkan Value\n");
    printf("2. Berdasarkan ID\n");
    printf("Pilihan Anda: ");
    scanf("%d", &sortChoice);
    getchar(); // buang newline

    for (int i = 0; i < n; i++) {
        printf("Data ke-%d:\n", i + 1);
        printf("  Masukkan ID: ");
        scanf("%s", id);
        printf("  Masukkan Value: ");
        scanf("%d", &value);
        getchar(); // buang newline

        if (sortChoice == 1) {
            root = insertnode(root, id, value);
        } else if (sortChoice == 2) {
            root = insertnodes(root, id, value);
        }
    }

    printf("\n--- Inorder Traversal (Sebelum Delete) ---\n");
    inorder(root);

    printf("\nMasukkan data yang ingin dihapus:\n");
    if (sortChoice == 1) {
        printf("  Berdasarkan value: ");
        scanf("%d", &value);
        root = deletenode(root, "", value); // id tidak dipakai untuk sorting by value
    } else if (sortChoice == 2) {
        printf("  Berdasarkan ID: ");
        scanf("%s", id);
        printf("  Masukkan value dari ID tersebut: ");
        scanf("%d", &value);  // penting agar node bisa dicocokkan dengan benar!
        root = deletenodes(root, id, value);
    }

    printf("\n--- Inorder Traversal (Setelah Delete) ---\n");
    inorder(root);

    return 0;
}


