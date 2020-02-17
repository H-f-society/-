//
//  TestSLinkList.c
//  
//
//  Created by tujunfeng on 18/9/21.
//
//

#include <stdio.h>
#include <stdlib.h>
#define Inital_size 8

typedef struct Node{
    int data;
    int cur;
}Node;

Node *InitalList(Node *head){
    int i;
    head=(Node *)malloc(sizeof(Node)*Inital_size);
    for(i=0;i<Inital_size-1;i++){
        head[i].cur=i+1;
    }
    head[Inital_size-1].cur=0;
    return head;
    
}

int getElem(Node *head){
    int i;
    i=head[0].cur;
    if (i) {
        head[0].cur=head[i].cur;
    }
    return i;
}

void offNode(Node *head,int k){
    head[k].cur=head[0].cur;
    head[0].cur=k;
    
}

void diffrience(Node *head){
    int m,n,j,i,s,p,k,e;
    int r;
    s=getElem(head);
    r=s;
    printf("input the number of A and b\n");
    scanf("%d,%d",&m,&n);
    for (j=1; j<=m; j++) {
        if(!(i=getElem(head))){
            printf("spilling\n");
            exit(0);
        }
        scanf("%d",&head[i].data);
        head[r].cur=i;
        r=i;
    }
    head[r].cur=0;
    for (j=1; j<=n; j++) {
        scanf("%d",&e);
        k=head[s].cur;
        p=head[s].cur;
        while (e!=head[p].data && p!=head[r].cur) {
            k=p;
            p=head[p].cur;
        }
        if (p==head[r].cur) {
            if(!(i=getElem(head))){
                printf("spilling\n");
                exit(0);
            }
            head[i].data=e;
            head[i].cur=head[r].cur;
            head[r].cur=i;
            r=i;
        }else{
            if(k==p){
                head[s].cur=head[k].cur;
                offNode(head,p);
            }else{
                head[k].cur=head[p].cur;
                offNode(head,p);
                if(p==r)
                    r=k;
            }
        }
    }
    i=head[s].cur;
    while (i) {
        printf("%d\n",head[i].data);
        i=head[i].cur;
    }

    
}

int main(){
    Node *head=NULL;
    head=InitalList(head);
    diffrience(head);
    
}