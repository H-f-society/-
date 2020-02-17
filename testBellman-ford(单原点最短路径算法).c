//
//  testBellman-ford.c
//  
//
//  Created by tujunfeng on 2019/7/23.
//

#include <stdio.h>
#define MAX_DIS 1000
#define MAX_NUM 100
#define NUL_PA 101
typedef struct Edge{
    int s,e;
    int value;
}Edge;

typedef struct Vex{
    int dis;
    int par;
}Vex;

Edge edgs[MAX_NUM];
Vex vexs[MAX_NUM];

void initialGraph();
void relax();
int Bellman_Ford();
void print_Path();

void initialGraph(int vex_num,int egd_num,int scorce_vex){
    int i,j;
    printf("input the each edge:\n");
    for(i=0;i<egd_num;i++){
        scanf("%d %d %d",&edgs[i].s,&edgs[i].e,&edgs[i].value);
    }
    for(i=0;i<vex_num;i++){
        vexs[i].dis=MAX_DIS;
        vexs[i].par=NUL_PA;
    }
    vexs[scorce_vex].dis=0;
}

void relax(int e,int s,int m){
    if(vexs[e].dis>vexs[s].dis+edgs[m].value){
        vexs[e].dis=vexs[s].dis+edgs[m].value;
        vexs[e].par=s;
    }
}

int Bellman_Ford(int vex_num,int egd_num){
    int i,j;
    for(i=0;i<vex_num-1;i++){
        for(j=0;j<egd_num;j++){
            relax(edgs[j].e,edgs[j].s,j);
        }
    }
    for(j=0;j<egd_num;j++){
        if(vexs[edgs[j].e].dis>vexs[edgs[j].s].dis+edgs[j].value){
            return 0;
        }
    }
    return 1;
}

void print_Path(int vex_num,int scorce_vex){
    int i=0,j=0;
    for(i=0;i<vex_num;i++){
        if(i==scorce_vex || vexs[i].dis==MAX_DIS)
            continue;
        j=i;
        printf("the distant and path to %d is %d, %d<-:",j,vexs[j].dis,j);
        while(vexs[j].par!=NUL_PA){
            printf("%d<-",vexs[j].par);
            j=vexs[j].par;
        }
        printf("\n");
    }
}

int main(){
    int egd_num=0,vex_num=0,scorce_vex=0;
    printf("input the number of vex and edges: ");
    scanf("%d %d",&vex_num,&egd_num);
    printf("input the scorceVex: ");
    scanf("%d",&scorce_vex);
    initialGraph(vex_num,egd_num,scorce_vex);
    if(Bellman_Ford(vex_num,egd_num)){
        printf("the scoreVex to each vex is:\n");
        print_Path(vex_num,scorce_vex);
    }
    else{
        printf("exist the loop<0!\n");
    }
    return 0;
}


