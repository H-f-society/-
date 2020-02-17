//
//  testKosaraju.c
//  
//
//  Created by tujunfeng on 19/5/4.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLIN 20

typedef struct ArcNode{
	int adjvex;
	struct ArcNode* next;
}ArcNode;

typedef struct VNode{
	char Info[5];
    ArcNode *head; 
}VNode;

typedef struct Edge{
    char one[5];
    char two[5];
}Edge;

typedef struct ALgraph{
    VNode adjList[MAXLIN];
	VNode retreAdjList[MAXLIN];
    int vexNum;
    int edgeNum;
    Edge edges[MAXLIN];
}ALgraph;

typedef struct stack{
	int *base;
	int *top;
}stack;

int visit[MAXLIN];
int deleted[MAXLIN];

ALgraph IputGraph(ALgraph *G);
void CreateMGraph(ALgraph *G,stack *S);
int getLoc(VNode *pv,int vexNum,char *pc);
void InserToAdj(int loc1,int loc2,VNode *pv);
void outPutAdj(ALgraph *G);
void DFS(ALgraph *G,stack *S,int n);
void getPart(ALgraph *G,int n);
void testKosaraju(ALgraph *G,stack *S,int n);

int main(){
	stack S; 
	ALgraph G;
    IputGraph(&G);
    CreateMGraph(&G,&S);
    outPutAdj(&G);
	testKosaraju(&G,&S,0);
	system("pause");
}

ALgraph IputGraph(ALgraph *G){
    int i;
    printf("input the number of vex:");
    scanf("%d",&G->vexNum);
    printf("input the name of each vex:");
    for (i=0; i<G->vexNum; i++) {
        scanf("%s",G->adjList[i].Info);
		strcpy(G->retreAdjList[i].Info,G->adjList[i].Info);
        G->adjList[i].head=NULL;
		G->retreAdjList[i].head=NULL;
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

void CreateMGraph(ALgraph *G,stack *S){
    int i, locOne,locTwo;
	S->base=(int *)malloc(sizeof(int)*MAXLIN);
	S->top=S->base;
    for (i=0; i<G->edgeNum; i++) {
        locOne=getLoc(G->adjList,G->vexNum,G->edges[i].one);
        locTwo=getLoc(G->adjList,G->vexNum,G->edges[i].two);
        InserToAdj(locOne,locTwo,G->adjList);
        InserToAdj(locTwo,locOne,G->retreAdjList);
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

void push(stack *S,int n){
	*(S->top++)=n;
	visit[n]=1;
}

void DFS(ALgraph *G,stack *S,int n){
	ArcNode* p=G->adjList[n].head;
	visit[n]=1;
	while(p){
		if(!visit[p->adjvex]){
			DFS(G,S,p->adjvex);
		}
		p=p->next;
	}
	push(S,n);
}

void getPart(ALgraph *G,int n){
	ArcNode* p=G->retreAdjList[n].head;
	deleted[n]=1;
	printf("%s ",G->adjList[n].Info);
	while(p){
		
		if(!deleted[p->adjvex]){
			getPart(G,p->adjvex);
		}
		p=p->next;
	}
}

void testKosaraju(ALgraph *G,stack *S,int n){
	int m;
	while(n<G->vexNum){
		if(!visit[n]){
			DFS(G,S,n);
		}
		while(S->base!=S->top){
			m=*(--S->top);
			if(!deleted[m]){
				printf("part is:");
				getPart(G,m);
				printf("\n");
			}
		}
		n++;
	}
}


