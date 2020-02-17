//
//  testTarjan.c
//  
//
//  Created by tujunfeng on 19/4/24.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLIN 15
typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;

typedef struct  VNode{
    char Info[5];
    ArcNode *head;
}VNode;

typedef struct Edge{
    char one[5];
    char two[5];
}Edge;

typedef struct ALgraph{
    VNode adjList[MAXLIN];
    int vexNum;
    int edgeNum;
    Edge edges[MAXLIN];
}ALgraph;

typedef struct vexQue{
    int vex[MAXLIN];
    int front;
    int rear;
}vexQue;

typedef struct stack{
    int *top;
    int *base;
}stack;

int visit[MAXLIN];
int dnf[MAXLIN];
int low[MAXLIN];
int outstack[MAXLIN];
int dindex=0;

void IputGraph(ALgraph *G,stack *S);
void CreateMGraph(ALgraph *G);
int getLoc(VNode *pv,int vexNum,char *pc);
void InserToAdj(int loc1,int loc2,VNode *pv);
void outPutAdj(ALgraph *G);
void testTarjan(ALgraph *G,int i,stack *S);


int main(){
    int start;
    ALgraph g;
    stack s;
    IputGraph(&g,&s);
    CreateMGraph(&g);
    outPutAdj(&g);
    printf("input the start:");
    scanf("%d",&start);
    testTarjan(&g,start,&s);
}

void IputGraph(ALgraph *G,stack *S){
    int i;
    printf("input the number of vex:");
    scanf("%d",&G->vexNum);
    S->base=S->top=(int *)malloc(sizeof(int)*G->vexNum);
    printf("input the name of each vex:");
    for (i=0; i<G->vexNum; i++) {
        scanf("%s",G->adjList[i].Info);
        G->adjList[i].head=NULL;
    }
    printf("input the number of edge:");
    scanf("%d",&G->edgeNum);
    printf("input the each edge:\n");
    for (i=0; i<G->edgeNum; i++) {
        scanf("%s %s",G->edges[i].one,G->edges[i].two);
    }
}

int getLoc(VNode *pv,int vexNum,char *pc){
    int i;
    for (i=0; i<vexNum; i++) {
        if (strcmp(pv[i].Info,pc)==0) {
            return i;
        }
    }
    printf("Error!Not exist the Vex!");
    exit(1);
}

void InserToAdj(int loc1,int loc2,VNode *pv){
    ArcNode *q=pv[loc1].head;
    ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
    if (!p) {
        printf("Memory is not enough!");
        exit(1);
    }
    p->adjvex=loc2;
    p->next=NULL;
    if (q==NULL) {
        pv[loc1].head=p;
    }
    else{
        if (q->adjvex>p->adjvex) {
            pv[loc1].head=p;
            p->next=q;
        }
        else{
            while (q->next) {
                if (q->next->adjvex>p->adjvex) {
                    p->next=q->next;
                    q->next=p;
                    break;
                }
                q=q->next;
            }
            if (q->next==NULL) {
                q->next=p;
            }
        }
    }
}

void CreateMGraph(ALgraph *G){
    int i, locOne,locTwo;
    for (i=0; i<G->edgeNum; i++) {
        locOne=getLoc(G->adjList,G->vexNum,G->edges[i].one);
        locTwo=getLoc(G->adjList,G->vexNum,G->edges[i].two);
        InserToAdj(locOne,locTwo,G->adjList);
    }
}

void outPutAdj(ALgraph *G){
    int i;
    for (i=0; i<G->vexNum; i++) {
        ArcNode *q=G->adjList[i].head;
        printf("%s:",G->adjList[i].Info);
        while (q) {
            printf("->%d",q->adjvex);
            q=q->next;
        }
        printf("->NULL\n");
    }
}

int min(int a,int b){
    return a<b?a:b;
}

void testTarjan(ALgraph *G,int i,stack *S){
    ArcNode *t=G->adjList[i].head;
    *(S->top++)=i;
    dnf[i]=low[i]=++dindex;
    visit[i]=1;
    while (t) {
        if (!visit[t->adjvex]) {
            testTarjan(G,t->adjvex,S);
            low[i]=min(low[i],low[t->adjvex]);
        }
        else if(!outstack[t->adjvex]){
            low[i]=min(low[i],dnf[t->adjvex]);
        }
        t=t->next;
    }
    printf("low[%d]=%d def[%d]=%d\n",i,low[i],i,dnf[i]);
    if (low[i]==dnf[i]) {
        printf("part is: ");
        while (1) {
            outstack[*(--S->top)]=1;
            if (*(S->top)==i) {
                printf("%s ",G->adjList[*(S->top)].Info);
                break;
            }
            printf("%s ",G->adjList[*(S->top)].Info);
            
        }
        printf("\n");
    }
}


