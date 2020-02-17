//
//  TestString.c
//  
//
//  Created by tujunfeng on 17/12/1.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node *AppendNode(struct node *head);//
struct node *FindNode(struct node *head);
struct node *InsertNode(struct node *head);
struct node *DeleteNode(struct node *head);
void DisplayNode(struct node *head);
void deleteMemory(struct node *head);
struct node{
    int data;
    struct node *next;
};

int main(){
	int i=0;
	struct node *head=NULL;
    while(i<5){
		head=AppendNode(head);
		i++;
	}
	DisplayNode(head);
	head=InsertNode(head);
	DisplayNode(head);
	head=DeleteNode(head);
	DisplayNode(head);
	

	system("pause");
    return 0;
}

struct node *AppendNode(struct node *head){
    struct node *tempt=head;
    struct node *p=NULL;
    p=(struct node *)malloc(sizeof(struct node));
    if(p==NULL){
        printf("not eough memory\n");
        exit(0);
    }
    else{
        if (tempt==NULL) {
            head=p;
        }else{
            while (tempt->next!=NULL) {
                tempt=tempt->next;
            }
            tempt->next=p;
        }
        printf("inupt the number\n");
        scanf("%d",&(p->data));
        p->next=NULL;
    }
    return head;
}

void DisplayNode(struct node *head){
    struct node *tempt=head;
	printf("DisplayNode");
    while(tempt!=NULL){
		printf("%d ",tempt->data);
		tempt=tempt->next;
	}
		printf("\n");
}
 
struct node *InsertNode(struct node *head){
	struct node *tempt=head;
	struct node *pr=head;
	struct node *p=NULL;
    p=(struct node *)malloc(sizeof(struct node));
	printf("input the number to insert\n");
	scanf("%d",&(p->data));
	if(p->data<head->data){
		p->next=head;
		head=p;
	}
	else{
		while(tempt!=NULL &&  p->data>tempt->data ){
			pr=tempt;
			tempt=tempt->next;
		}
	
		p->next=tempt;
		pr->next=p;

		
	}
	return head;
}

struct node *DeleteNode(struct node *head){
	int n;
	struct node *tempt=head;
	struct node *pr=head;
	printf("input the number you wanna delete\n");
	scanf("%d",&n);
	if(n==head->data){
		head=head->next;
	}
	else{
		while(tempt!=NULL && tempt->data<n ){
			pr=tempt;
			tempt=tempt->next;
		}
	if(tempt==NULL || tempt->data!=n){
		printf("do not exist the number\n");
	}
	else{
				
		pr->next=tempt->next;
		}
	}
	return head;
	
}


void deleteMemory(struct node *head){
    struct node *pr=head;
    struct node *p=NULL;
    while (pr!=NULL) {
        p=pr->next;
        free(pr);
        pr=p;
    }
}
 
