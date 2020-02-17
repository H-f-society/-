//
//  TestSqQueue.c
//  
//
//  Created by tujunfeng on 18/3/28.
//
//

#include <stdio.h>
#include <stdlib.h>
#define Queue_Size 5

typedef struct SqQueue{
    int * base;
    int front;
    int rear;
}SqQueue;

void IntialQueue(SqQueue *Q){
    Q->base=(int *)malloc(sizeof(int)*Queue_Size);
    if(!Q->base){
        printf("not enough memory\n");
        exit(0);
    }
    Q->front=Q->rear=0;
}

void Enque(SqQueue *Q){
    int e;
    if((Q->rear+1)%Queue_Size==Q->front){
        printf("the Queue is full\n");
        exit(0);
    }
    printf("input the number\n");
    scanf("%d",&e);
    Q->base[Q->rear]=e;
    Q->rear=(Q->rear+1)%Queue_Size;
}

void DeQueue(SqQueue *Q){
    if(Q->front==Q->rear){
        printf("the Queue is empty\n");
        exit(0);
    }
    Q->front=(Q->front+1)%Queue_Size;
}

void TraversQue(SqQueue *Q){
    int i;
    if(Q->rear==Q->front){
        printf("the queue is empty\n");
        exit(0);
    }
    i=Q->front;
    while (i!=Q->rear) {
        printf("%d",Q->base[i]);
		i=(i+1)%Queue_Size;
        
    }
}

int main(){
    SqQueue Q;
    char choose;
    char ch;
    IntialQueue(&Q);
    
    do{
        printf("1 Enqueue,2 Dequeue\n");
        scanf(" %c",&choose);
        switch (choose) {
            case '1':
                Enque(&Q);
                break;
                
            case '2':
                DeQueue(&Q);
        }
        printf("do you wanna continue\n");
        scanf(" %c",&ch);
    }while(ch=='y'||ch=='Y');
    TraversQue(&Q);
	system("pause");
    return 0;
    
    
}
