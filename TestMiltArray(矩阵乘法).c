//
//  TestArray3.c
//  
//
//  Created by tujunfeng on 18/4/19.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Maxrow 12
#define maxcol 12
typedef struct Triple{
    int i;
    int j;
    int element;
}Triple;

typedef struct RLSMatrix{
    Triple *data;
    int rpos[Maxrow+1];
    int mu,nu,tu;
}RLSMatrix;

void InitialArray(RLSMatrix *T){
    int num[12]={0};
    int col;
    int i,j,element;
    int count;
    printf("input the row and coloum of the matrix\n");
    scanf("%d,%d",&T->mu,&T->nu);
    printf("input the number of element is not Zero\n");
    scanf("%d",&T->tu);
    T->data=(Triple *)malloc(sizeof(Triple)*(T->tu+1));
    if (!T->data) {
        printf("the memory is not enough\n");
        exit(0);
    }
    printf("input the attribution of each element\n");
    for (count=1;count<=T->tu;count++) {
        printf("the No.%d\n",count);
        scanf("%d,%d,%d",&i,&j,&element);
        if(i>T->mu||j>T->nu){
            printf("creating failed\n");
			exit(0);
        }
        T->data[count].i=i;
        T->data[count].j=j;
        T->data[count].element=element;
        
    }
    for (count=1; count<=T->tu; count++) {
        ++num[T->data[count].i];
    }
    T->rpos[1]=1;
    for (count=2; count<=T->mu; count++) {
        T->rpos[count]=T->rpos[count-1]+num[count-1];
    }
    
}

void MuilMatrix(RLSMatrix *M,RLSMatrix *N,RLSMatrix *Q){
    int i;
    int p;
    int q;
    int t;
    int tp;
    int ctempt[12]={0};
    int row;
    int col;
    int brow;
    Q->mu=M->mu;
    Q->nu=N->nu;
    Q->tu=0;
    if (M->nu!=N->mu) {
        printf("wrong!\n");
        exit(0);
    }
    Q->data=(Triple *)malloc(sizeof(Triple)*(M->mu*N->nu+1));
    for (row=1; row<=M->mu; row++) {
        for (i=1; i<=N->nu; i++) {
            ctempt[i]=0;
        }
        Q->rpos[row]=Q->tu+1;
        if (row<M->mu) {
            tp=M->rpos[row+1];
        }
        else{
            tp=M->tu+1;
        }
        for (p=M->rpos[row]; p<tp; p++) {
            brow=M->data[p].j;
            if (brow<N->mu) {
                t=N->rpos[brow+1];
            }
            else{
                t=N->tu+1;
            }
            printf("N->rpos[brow]=%d\n",N->rpos[brow]);
            for (q=N->rpos[brow]; q<t; q++) {
                col=N->data[q].j;
                ctempt[col]+=M->data[p].element*N->data[q].element;
            }
        }
        for (col=1; col<=Q->nu; col++) {
            if(ctempt[col]){
                Q->tu++;
                Q->data[Q->tu].i=row;
                Q->data[Q->tu].j=col;
                Q->data[Q->tu].element=ctempt[col];
                
            }
        }
    }
    
}
void PrintMatrix(RLSMatrix *T){
    int n;
    for (n=1; n<=T->tu; n++) {
        printf("the No.%d nummber is:",n);
        printf("%d,%d,%d\n",T->data[n].i,T->data[n].j,T->data[n].element);
    }
}

int main(){
    RLSMatrix M,N,Q;
    InitialArray(&M);
    InitialArray(&N);
    MuilMatrix(&M,&N,&Q);
    PrintMatrix(&Q);
	system("pause");
	return 0;
}