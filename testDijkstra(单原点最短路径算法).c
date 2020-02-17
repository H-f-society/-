//
//  testDijkstra.c
//  
//
//  Created by tujunfeng on 2019/7/31.
//

#include <stdio.h>
#define MAXM 10000
#define MAXN 100
#define INF 19910326

typedef struct Vex{
    int dis;      //节点到源节点距离
    int par;      //节点前驱
    int vexNum;   //节点号
}Vex;

Vex vexs[MAXN];


int Edges[MAXM];  //每条边的头结点号
int next[MAXM];   //某条边以相同节点为尾的下一条边的位置
int g[MAXN];      //以某节点为尾的最后一条边的位置
int cost[MAXM];   //每条边的权重
int size;         //边的条数

int pos[MAXN];    //每个节点在优先队列中的序列

int m,n,s;          //边的个数和节点个数和源节点
int heap_size;    //堆中剩余点个数

void initialGraph();
void insert(int u,int v,int w);
void dijkstra();
void swap(int a,int b);
void minHeapfp();
void relax(int u,int v,int w);

/*  用数组实现邻接链表  */
void insert(int u,int v,int w){
    Edges[++size]=v;
    next[size]=g[u];
    cost[size]=w;
    g[u]=size;
}

/*  初始化边  */
void initialGraph(){
    int i,u,v,w;
    scanf("%d %d",&m,&n);
    for(i=1; i<=m; i++){
        scanf("%d %d %d",&u,&v,&w);
        insert(u,v,w);
    }
    s=1;
}

/*  交换堆中两个节点  */
void swap(int a,int b){
    vexs[0]=vexs[a];
    vexs[a]=vexs[b];
    vexs[b]=vexs[0];
    pos[vexs[a].vexNum]=a;
    pos[vexs[b].vexNum]=b;
}

/*  堆调整维护  */
void minHeapfp(){
    int i=2;
    while(i<=heap_size){
        if(i < heap_size && vexs[i+1].dis<vexs[i].dis)
            i++;
        if (vexs[i].dis<vexs[i>>1].dis) {
            swap(i,i>>1);
            i<<=1;
        }
        else
            break;
    }
}

/*  删除堆中最小节点  */
void deletMin(){
    swap(1,heap_size);
    heap_size--;
    minHeapfp();
}

/* 优先队列减少一个元素值重新排列 */
void decrease(int k){
    while(k>1 && vexs[k].dis<vexs[k>>1].dis){
        swap(k,k>>1);
        k>>=1;
    }
}

/*  松弛操作  */
void relax(int u,int v,int w){
    if(vexs[pos[v]].dis > vexs[pos[u]].dis+w){
        vexs[pos[v]].dis=vexs[pos[u]].dis+w;
        vexs[pos[v]].par=u;
        decrease(pos[v]);
    }
}

void dijkstra(){
    int i,u,p;
    for(i=1;i<=n;i++){
        vexs[i].vexNum=pos[i]=i;
        vexs[i].dis=INF;
        vexs[i].par=0;
    }
    vexs[s].dis=0;
    swap(1,s);
    heap_size=n;
    while (heap_size) {
        u=vexs[1].vexNum;
        deletMin();
        p=g[u];
        while(p){
            if(pos[Edges[p]]<=heap_size){
                relax(u,Edges[p],cost[p]);
            }
            p=next[p];
        }
    }
}

int main(){
    int i,p;
    initialGraph();
    dijkstra();
    for(i=1;i<=n;i++){
        if(vexs[pos[i]].dis==INF){
            continue;
        }
        printf("%d->",i);
        p=vexs[pos[i]].par;
        while(p){
            printf("%d->",p);
            p=vexs[pos[p]].par;
        }
        printf("the dis is:%d\n", vexs[pos[i]].dis);
    }
    return 0;
}
