//
//  TestSqList.c
//  
//
//  Created by tujunfeng on 18/9/5.
//
//

#include <stdio.h>
#include <stdlib.h>
#define Init_Size 10
#define Increment_Size 10

typedef struct SqList{
    int *elem;
    int Length;
    int ListSize;
}SqList;

void initList(SqList *L);
void AddAtom(SqList *L,int n);
void InsertList(SqList *L,int i, int e);
void DeletList(SqList *L,int i);
int LocateElem(SqList *L,int n);
void Union(SqList *L1,SqList *L2);
void MergeList(SqList *L1,SqList *L2,SqList *L3);
void TraverseList(SqList *L);

void initList(SqList *L){
    L->elem=(int *)malloc(sizeof(int)*Init_Size);
    if (!L->elem) {
        exit(0);
    }
    L->Length=0;
    L->ListSize=Init_Size;
}

void AddAtom(SqList *L,int n){
    int i;
    if ((L->Length+n)>L->ListSize) {
        printf("*****\n");
        L->elem=(int *)realloc(L->elem,sizeof(int)*(L->ListSize+Increment_Size));
        if (!L->elem) {
            exit(0);
        }
        L->ListSize=L->ListSize+Increment_Size;
    }
    printf("input the number\n");
    for (i=1; i<=n; i++) {
        scanf("%d",L->elem+L->Length++);
    }
}

void MergeList(SqList *L1,SqList *L2,SqList *L3){
    int i=0,j=0,k=0;
    L3->elem=(int *)malloc(sizeof(int)*(L1->Length+L2->Length));
    if (!L3->elem) {
        exit(0);
    }
    L3->Length=L1->Length+L2->Length;
    L3->ListSize=L1->Length+L2->Length;
    while (i<L1->Length && j<L2->Length) {
        if (L1->elem[i]<=L2->elem[j])
            L3->elem[k++]=L1->elem[i++];
        else
            L3->elem[k++]=L2->elem[j++];
        
    }
    while (i<L1->Length) {
        L3->elem[k++]=L1->elem[i++];
    }
    while (j<L2->Length) {
        L3->elem[k++]=L1->elem[j++];
    }
}

void InsertList(SqList *L,int i, int e){ //在顺序表L第i个位置插入元素e
    int n;
    if (i<1||i>L->Length+1) {
        exit(0);
    }
    if (L->Length>=L->ListSize) {
        L->elem=(int *)realloc(L->elem,sizeof(int)*(L->ListSize+Increment_Size));
        if (!L->elem) {
            exit(0);
        }
        L->ListSize=L->ListSize+Increment_Size;
    }
    for (n=L->Length; n>=i; n--) {
        L->elem[n]=L->elem[n-1];
    }
    L->elem[i-1]=e;
    L->Length++;
}

void DeletList(SqList *L,int i){
    int n;
    if (i<1||i>L->Length) {
        exit(0);
    }
    for (n=i; n<L->Length; n++) {
        L->elem[n-1]=L->elem[n];
    }
    L->Length--;
}

int LocateElem(SqList *L,int n){
    int i=1;
    while (i<=L->Length) {
        if (L->elem[i-1]==n)
            return i;
        else
            i++;
    }
    return 0;
}

void Union(SqList *L1,SqList *L2){
    int i;
    if ((L1->Length+L2->Length)>L1->ListSize) {
        L1->elem=(int *)realloc(L1->elem,sizeof(int)*(L1->Length+L2->Length));
        if (!L1->elem) {
            exit(0);
        }
        L1->ListSize=L1->Length+L2->Length;
    }
    for(i=0;i<L2->Length;i++){
        if (!LocateElem(L1,L2->elem[i])) {
            InsertList(L1,L1->Length+1,L2->elem[i]);
        }
    }
}

void TraverseList(SqList *L){
    int i;
    printf("the all atom is:\n");
    for(i=0;i<L->Length;i++){
        printf("%d ",*(L->elem+i));
    }
}


int main(){
    SqList L1,L2,L3;
    initList(&L1);
    initList(&L2);
    AddAtom(&L1,6);
    printf("%d %d\n",L1.Length,L1.ListSize);
    AddAtom(&L2,6);
    printf("%d %d\n",L2.Length,L2.ListSize);
    InsertList(&L1,2,6);
    Union(&L1,&L2);
    DeletList(&L1,6);
    printf("%d %d\n",L1.Length,L1.ListSize);
    TraverseList(&L1);
    return 1;
}