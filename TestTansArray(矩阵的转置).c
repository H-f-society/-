//
//  TestArray2.c
//  
//
//
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 256

typedef struct Triple{
    int i;
    int j;
    int element;
}Triple;

typedef struct TSMatrix{
    Triple *data;
    int mu,nu,tu;
}TSMatrix;

void InitialArray(TSMatrix *T){
    int i,j,element;
    int count;
    printf("input the row and coloum of the matrix\n");
    scanf("%d,%d",&T->mu,&T->nu);
    printf("input the number of element is not Zero\n");
    scanf("%d",&T->tu);
    T->data=(Triple *)malloc(sizeof(Triple)*T->tu+1);
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
        }
        T->data[count].i=i;
        T->data[count].j=j;
        T->data[count].element=element;
        
    }
    
}

void TransposeSMatrix(TSMatrix *M,TSMatrix *N){
    int p;
    int q=1;
    int col;
    N->mu=M->nu;
    N->nu=M->mu;
    N->tu=M->tu;
    N->data=(Triple *)malloc(sizeof(Triple)*N->tu);
    for (col=1; col<=M->nu; col++) {
        for (p=1; p<=M->tu; p++) {
            if(M->data[p].j==col){
                N->data[q].i=M->data[p].j;
                N->data[q].j=M->data[p].i;
                N->data[q].element=M->data[p].element;
                q++;
            }
        }
    }
    
}

void FastTransposeSMatrix(TSMatrix *M,TSMatrix *N){
    int q;
    int t;
    int num[10];
    int cpot[10];
    int col;
    N->mu=M->nu;
    N->nu=M->mu;
    N->tu=M->tu;
    N->data=(Triple *)malloc(sizeof(Triple)*N->tu);
    if (!N->data) {
        printf("the memory is not enough\n");
        exit(0);
    }
    for(col=1;col<=M->nu;col++){
        num[col]=0;
    }
    for (t=1; t<=M->tu; t++){
        ++num[M->data[t].j];
    }
    cpot[1]=1;
    for (col=2; col<=M->nu; col++) {
        cpot[col]=cpot[col-1]+num[col-1];
    }
    for (t=1; t<=M->tu; t++) {
        q=cpot[M->data[t].j]++;
        N->data[q].i=M->data[t].j;
        printf("%d\n",M->data[t].j);
        N->data[q].j=M->data[t].i;
        N->data[q].element=M->data[t].element;

        
    }
   
}

void PrintMatrix(TSMatrix *T){
    int n;
    for (n=1; n<=T->tu; n++) {
        printf("the No.%d nummber is:",n);
        printf("%d,%d,%d\n",T->data[n].i,T->data[n].j,T->data[n].element);
    }
    
}

int main(){
    TSMatrix M,T,Q;
    InitialArray(&M);
    TransposeSMatrix(&M,&T);
    FastTransposeSMatrix(&M,&Q);
    PrintMatrix(&M);
    PrintMatrix(&T);
    PrintMatrix(&Q);
    return 0;
}

