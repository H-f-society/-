//
//  DFS/BFStraversal.c
//  
//
//  Created by tujunfeng on 19/4/13.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLIN 50
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

int visit[MAXLIN];

ALgraph IputGraph(ALgraph G);
void CreateMGraph(ALgraph *G);
int getLoc(VNode *pv,int vexNum,char *pc);
void InserToAdj(int loc1,int loc2,VNode *pv);
void outPutAdj(ALgraph *G);
void DFStraversal(ALgraph *G);
void DPS(char *ch,int index,ALgraph *G);
void BFStraversal(ALgraph *G);
void BPS(ALgraph *G,vexQue *Q);
void InQue(vexQue *Q,int index);
int DeQue(vexQue *Q);
int isEmpty(vexQue *Q);


int main(){
    int choose;
    ALgraph G;
    G=IputGraph(G);
    CreateMGraph(&G);
    outPutAdj(&G);
    printf("please choose(1.DFS 2.BFS):");
    scanf("%d",&choose);
    if (choose==1) {
        DFStraversal(&G);
    }
    else{
        BFStraversal(&G);
    }
}

ALgraph IputGraph(ALgraph G){
    int i;
    printf("input the number of vex:");
    scanf("%d",&G.vexNum);
    printf("input the name of each vex:");
    for (i=0; i<G.vexNum; i++) {
        scanf("%s",G.adjList[i].Info);
        G.adjList[i].head=NULL;
    }
    printf("input the number of edge:");
    scanf("%d",&G.edgeNum);
    printf("input the each edge:\n");
    for (i=0; i<G.edgeNum; i++) {
        scanf("%s %s",G.edges[i].one,G.edges[i].two);
    }
    return G;
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
        InserToAdj(locTwo,locOne,G->adjList);
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

void DPS(char *ch,int index,ALgraph *G){
    if (!visit[index]) {
        ArcNode *p=G->adjList[index].head;
        visit[index]=1;
        printf("%s->",ch);
        while (p) {
            //printf("%s->",G->adjList[p->adjvex].Info);
            DPS(G->adjList[p->adjvex].Info,p->adjvex,G);
            p=p->next;
        }
    }
}

void DFStraversal(ALgraph *G){
    int i,count=1;
    char start[5];
    printf("input the start vex to DFStraversal:");
    scanf("%s",start);
    for (i=0; i<G->vexNum; i++) {
        if (strcmp(G->adjList[i].Info,start)==0) {
            printf("the No.%d DPS is:",count);
            DPS(start,i,G);
            printf("NULL\n");
            count++;
            
        }
        if(i==G->vexNum){
            printf("Error!Not exist the Vex!");
        }
    }
    for (i=0; i<G->vexNum; i++) {
        if (!visit[i]) {
            printf("the No.%d DPS is:",count);
            DPS(G->adjList[i].Info,i,G);
            printf("NULL\n");
        }
    }
    
}

void InQue(vexQue *Q,int index){
    Q->vex[Q->rear++]=index;
    visit[index]=1;
}

int DeQue(vexQue *Q){
    return Q->vex[Q->front++];
}

int isEmpty(vexQue *Q){
    if (Q->front==Q->rear)
        return 1;
    else
        return 0;
}

void BPS(ALgraph *G,vexQue *Q){
    int index;
    ArcNode *p=NULL;
    if(!isEmpty(Q)){
        index=DeQue(Q);
        p=G->adjList[index].head;
        while (p) {
            if (!visit[p->adjvex]) {
                InQue(Q,p->adjvex);
            }
            p=p->next;
        }
        printf("%s->",G->adjList[index].Info);
        BPS(G,Q);
    }
}

void BFStraversal(ALgraph *G){
    int i,count=1;
    char start[5];
    vexQue Q;
    Q.front=Q.rear=0;
    printf("input the start vex to DFStraversal:");
    scanf("%s",start);
    for (i=0; i<G->vexNum; i++) {
        if (strcmp(G->adjList[i].Info,start)==0) {
            InQue(&Q,i);
            printf("the No.%d DPS is:",count);
            BPS(G,&Q);
            printf("NULL\n");
            count++;
        }
        if(i==G->vexNum){
            printf("Error!Not exist the Vex!");
        }
    }
    for (i=0; i<G->vexNum; i++) {
        if (!visit[i]) {
            InQue(&Q,i);
            printf("the No.%d BPS is:",count);
            BPS(G,&Q);
            printf("NULL\n");
        }
    }
}