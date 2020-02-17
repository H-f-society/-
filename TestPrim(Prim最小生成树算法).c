//
//  TestPrim.c
//  
//
//  Created by tujunfeng on 19/4/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define MAX_SZIE 20
typedef struct Graph{
    int len;
    char ver[MAX_SZIE];
    int edge[MAX_SZIE][MAX_SZIE];
}Graph;

typedef struct Node{
    int index;
    struct Node *next;
}Node;

int uvex[MAX_SZIE];
int lowest[MAX_SZIE];
int closest[MAX_SZIE];
Node *vhead=NULL;
int unumber=0;
void CreateGraph(Graph *p);
void printGraph(Graph *g);
void prim(Graph *g,int index);
void deleteNode(int index);
int getFir(Graph *g);


void CreateGraph(Graph *g){
    int i,j,n=0,weight;
    Node *p=NULL,*q=vhead;
    printf("input the each vex:\n");
    while ((g->ver[n++]=getchar())!='\n'){
        p=(Node *)malloc(sizeof(Node));
        if (vhead==NULL) {
            vhead=p;
            q=p;
        }
        else{
            q->next=p;
            q=p;
        }
        p->index=n-1;
        p->next=NULL;
        lowest[n-1]=MAX;
    }
    g->len=n-1;
    printf("input the adjMaxtrix:\n");
    for (i=0; i<g->len; i++) {
        for (j=0; j<g->len; j++) {
            scanf("%d",&weight);
            g->edge[i][j]=weight?weight:MAX;
        }
    }
}

void printGraph(Graph *g){
    
    int i,j;
    for (i=0; i<g->len; i++) {
        for (j=0; j<g->len; j++) {
            if (g->edge[i][j]==MAX) {
                printf("# ");
            }else{
                printf("%d ",g->edge[i][j]);
            }
        }
        printf("\n");
    }
     
}


void prim(Graph *g,int index){
    int i,min=MAX;
    Node *p=vhead;
    deleteNode(index);
    if (unumber<g->len) {
        while (p) {
            if(g->edge[index][p->index]<lowest[p->index]){
                lowest[p->index]=g->edge[index][p->index];
                closest[p->index]=index;
            }
            p=p->next;
        }
        p=vhead;
        while (p) {
            if (min>lowest[p->index]) {
                min=lowest[p->index];
                i=p->index;
            }
            p=p->next;
        }
        prim(g,i);
    }
    
}

void deleteNode(int index){
    Node *p=vhead;
    if (p->index==index) {
        vhead=p->next;
    }
    else{
        while (p->next->index!=index) {
            p=p->next;
        }
        p->next=p->next->next;
    }
    uvex[unumber++]=index;
    printf("%d\n",index);
}

int getFir(Graph *g){
    char ch;
    int i=0;
    printf("input the first Node:");
    scanf(" %c",&ch);
    while (ch!=g->ver[i++]);
    return i-1;
}

int main(){
    int i,weight=0,j;
    Graph g;
    CreateGraph(&g);
    printGraph(&g);
    j=getFir(&g);
    prim(&g,j);
    for (i=0; i<g.len; i++) {
        if (i!=j) {
            printf("%c-%c\n",g.ver[closest[i]],g.ver[i]);
            weight+=g.edge[closest[i]][i];
        }
    }
    printf("weight=%d",weight);
}