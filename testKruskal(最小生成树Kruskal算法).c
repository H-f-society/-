//
//  TestKruskal.c
//
//
//  Created by tujunfeng on 19/4/17.
//
//
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 30
#define MAX 1000

typedef struct Graph{
    int vexNum;
    int edgenum;
    char ver[MAX_SIZE];
    int edge[MAX_SIZE][MAX_SIZE];
}Graph;

typedef struct Node{
    int index;
    struct Node *next;
}Node;

typedef struct Edge{
    int v1;
    int v2;
    int weight;
}Edge;

typedef struct Head{
    int count;
    Node *first;
}headd;

void quitSort(Edge a[],int low,int hign);
void swap(Edge *pa,Edge *pb);
void createList(Graph *g);
int part[MAX_SIZE];
void combine(int a,int b);
headd head[MAX_SIZE];
Edge edges[MAX_SIZE];
void kruskal(Graph *g);

int main(){
    Graph g;
    createList(&g);
    quitSort(edges,0,g.edgenum-1);
    kruskal(&g);
}

void createList(Graph *g){
    int i,j,n=0,weight;
    Node *p=NULL;
    g->edgenum=0;
    printf("input the vex:");
    while ((g->ver[n++]=getchar())!='\n');
    g->vexNum=n-1;
    for (i=0; i<g->vexNum; i++) {
        part[i]=i;
        p=(Node *)malloc(sizeof(Node));
        p->index=i;
        p->next=NULL;
        head[i].first=p;
        head[i].count=1;
    }
    printf("input the adjMaxtrix:\n");
    for (i=0; i<g->vexNum; i++) {
        for (j=0; j<g->vexNum; j++) {
            scanf("%d",&weight);
            if (i<j && weight!=0) {
                edges[g->edgenum].v1=i;
                edges[g->edgenum].v2=j;
                edges[g->edgenum].weight=weight;
                g->edgenum++;
            }
        }
    }
}

void swap(Edge *pa,Edge *pb){
	Edge temp;
	temp=*pa;
	*pa=*pb;
	*pb=temp;
}

void quitSort(Edge a[],int low,int hign){
	int lo=low,hi=hign;
	int key=low;
	if(low<hign){
		while(low<hign){
			while(low<hign && a[hign].weight>=a[key].weight)
				hign--;
			while(low<hign && a[low].weight<=a[key].weight)
				low++;
			if(low!=hign){
				swap(&a[low],&a[hign]);	
			}
		}
		swap(&a[key],&a[low]);
		quitSort(a,lo,low-1);
		quitSort(a,low+1,hi);
	}
	
}

void combine(int a,int b){
    Node *p=head[b].first;
    Node *q=head[a].first;
    while (q->next) {
        q=q->next;
    }
    while (p) {
        part[p->index]=a;
        p=p->next;
    }
    q->next=head[b].first;
    head[b].first=NULL;
    head[a].count+=head[b].count;
    head[b].count=0;
}

void kruskal(Graph *g){
    int j=0,sum=0;
    while (j<g->edgenum) {
        if (part[edges[j].v1]!=part[edges[j].v2]) {
            printf("%c-%c %d\n",g->ver[edges[j].v1],g->ver[edges[j].v2],edges[j].weight);
            combine(part[edges[j].v1],part[edges[j].v2]);
            sum+=edges[j].weight;
            printf("head[%d].count=%d\n",part[edges[j].v1],head[part[edges[j].v1]].count);
            if (head[part[edges[j].v1]].count==g->vexNum)
                break;
            
        }
        j++;
    }
    
    printf("weight=%d",sum);
}