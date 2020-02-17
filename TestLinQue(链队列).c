//
//  TestSqQue.c
//  
//
//  Created by tujunfeng on 18/3/24.
//
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct LinkQue{
     Node *front;
     Node *rear;
}LinkQue;

void InitaQueue(LinkQue *Q){
    Q->front=(Node *)malloc(sizeof(Node));
    if(!Q->front){
        printf("not enough memory\n");
        exit(0);
    }
    Q->rear=Q->front;
    Q->front->next=NULL;
}

void destroyQue(LinkQue *Q){
    while (Q->front) {
        Q->rear=Q->front->next;
        free(Q->front);
        Q->front=Q->rear;
    }
}

int Isempty(LinkQue *Q){
    if(Q->front==Q->rear)
        return 1;
    else
        return 0;
}

void EnQueue(LinkQue *Q){
    int n;
    Node *p=(Node *)malloc(sizeof(Node));
    if(!p){
        printf("not enough memory\n");
        exit(0);
    }
    Q->rear->next=p;
    Q->rear=p;
    printf("please input the number\n");
    scanf("%d",&n);
    p->data=n;
    p->next=NULL;
    
}

int DeQueue(LinkQue *Q){
    int e;
    Node *p;
    if(Isempty(Q)){
        printf("the Queue is empty\n");
        exit(0);
    }
    p=Q->front->next;
    e=p->data;
    Q->front->next=Q->front->next->next;
    if(Q->rear==p){
        Q->rear=Q->front;
    }
    free(p);
    return e;
    
}
void DisplayQue(LinkQue *Q){
    Node *p;
    if(Isempty(Q)){
        printf(" queue is empty");
        exit(0);
    }
    p=Q->front->next;
    while(p){
        printf("%d\n",p->data);
        p=p->next;
    }
    
}



int main(){
    char choose;
    char ch;
    LinkQue Q;
    InitaQueue(&Q);
    printf("1.进堆  2.出队\n");
    
    do{
        printf("chhose the operatopn\n");
        scanf(" %c",&choose);
        switch (choose) {
            case '1':
                EnQueue(&Q);
                break;
            
            case '2':
                DeQueue(&Q);
                break;
        }
        printf("do you wanna continue\n");
        scanf(" %c",&ch);
    }while(ch=='y'||ch=='Y');
    DisplayQue(&Q);
    destroyQue(&Q);
}