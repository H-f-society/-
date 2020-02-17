//
//  EightQueen.c
//  
//
//  Created by tujunfeng on 19/1/9.
//
//
#include <stdlib.h>
#include <stdio.h>

typedef struct Bitree{
	char data;
	struct Bitree *lchild;
	struct Bitree *rchild;
}Bitree;

typedef struct stack{
	int stack_size;
	struct Bitree **base;
	struct Bitree **top;
}stack;

void createTree(Bitree **T);
void initialStack(stack *s);
Bitree * getTop(stack *s);
int isEmpty(stack *s);
Bitree * pop(stack *s);
void push(stack *s,Bitree *T);
void inOrder(Bitree *T,stack *s);
void preOrder(Bitree *T,stack *s);
void postOrder(Bitree *T,stack *s);

int main(){
	stack s;
	Bitree *T=NULL;
	printf("input the tree:");
	createTree(&T);
	initialStack(&s);
	inOrder(T,&s);
	printf("\n------------------------------\n");
	preOrder(T,&s);
	printf("\n------------------------------\n");
	postOrder(T,&s);
	system("pause");
	return 0;

}
void createTree(Bitree **T){
	char ch;
	scanf("%c",&ch);
	if(ch=='#'){
		*T=NULL;
	}
	else{
		*T=(Bitree *)malloc(sizeof(Bitree));
		(*T)->data=ch;
		createTree(&(*T)->lchild);
		createTree(&(*T)->rchild);
	}
}

void initialStack(stack *s){
	s->base=(Bitree **)malloc(sizeof(Bitree *)*20);
	s->stack_size=20;
	s->top=s->base;
}

Bitree * getTop(stack *s){
	return *(s->top-1);
}

Bitree * pop(stack *s){
	if(s->base==s->top){
		exit(0);
	}
	else{
		return *(--s->top);;
	}
}
void push(stack *s,Bitree *T){
	*(s->top++)=T;

}

int isEmpty(stack *s){
	if(s->base==s->top)
		return 1;
	else 
		return 0;
}

void inOrder(Bitree *T,stack *s){
	Bitree *p; 
	push(s,T);
	while(!isEmpty(s)){
		while((p=getTop(s))!=NULL)
			push(s,p->lchild);
		pop(s);
		if(!isEmpty(s)){
		p=pop(s);
		printf("%c ",p->data);
		push(s,p->rchild);
		}
	}
}

void preOrder(Bitree *T,stack *s){
	Bitree *p; 
	push(s,T);
	while(!isEmpty(s)){
		while((p=getTop(s))!=NULL){
			push(s,p->lchild);
			if(p){
				printf("%c ",p->data);
			}
		}
		pop(s);
		if(!isEmpty(s)){
		p=pop(s);
		push(s,p->rchild);
		}
	}
}

void postOrder(Bitree *T,stack *s){
	int top=-1,flag=1;
	Bitree *p=NULL; 
	if(T){
		do{
			while(T){
				top++;
				push(s,T);
				T=T->lchild;
			}
			flag=1;
			p=NULL;
			while(top>-1 && flag==1){
				T=getTop(s);
				if(T->rchild==p){
					printf("%c ",T->data);
					pop(s);
					p=T;
					top--;
				}
				else{
					T=T->rchild;
					flag=0;
				}
			}
		}while(top>-1);
	}
	else{
		printf("the tree is empty!\n");
	}
}

