#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
	char data;
	struct TreeNode *leftChild;
	struct TreeNode *rightChild;
}TreeNode;

void createTree(TreeNode **T);
void preOrder(TreeNode *T);
void inOrder(TreeNode *T);
void postOrder(TreeNode *T);

int main(){
	TreeNode *T=NULL;
	printf("input the tree:");
	createTree(&T);
	printf("preOrder:");
	preOrder(T);
	printf("\n");
	printf("inOrder:");
	inOrder(T);
	printf("\n");
	printf("postOrder:");
	postOrder(T);
	printf("\n");
	system("pause");
	return 0;

}

void createTree(TreeNode **T){
	char ch;
	scanf("%c",&ch);
	if(ch=='#'){
		*T=NULL;
	}
	else{
		*T=(TreeNode *)malloc(sizeof(TreeNode));
		(*T)->data=ch;
		createTree(&(*T)->leftChild);
		createTree(&(*T)->rightChild);
	}
}

void preOrder(TreeNode *T){
	if(T==NULL){
		return;
	}
	else{
		printf("%c ",T->data);
		preOrder(T->leftChild);
		preOrder(T->rightChild);
	}
}

void inOrder(TreeNode *T){
	if(T==NULL){
		return;
	}
	else{
		inOrder(T->leftChild);
		printf("%c ",T->data);
		inOrder(T->rightChild);
	}
}

void postOrder(TreeNode *T){
	if(T==NULL){
		return;
	}
	else{
		postOrder(T->leftChild);
		postOrder(T->rightChild);
		printf("%c ",T->data);
	}
}

