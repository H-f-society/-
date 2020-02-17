//
//  TestStake.c
//  
//
//  Created by tujunfeng on 18/3/21.
//
//

#include <stdio.h>
#include <stdlib.h>
#define Stake_Init_Size 20
#define Stake_Increment 10

typedef struct {
    int *base;
    int *top;
    int StakeSize;

}SqStake;

void InitiStake(SqStake *S,int len){
    S->base=(int *)malloc(sizeof(int)*len);
    if (!S->base) {
        printf("Not eought memory\n");
        exit(0);
    }
    S->top=S->base;
    S->StakeSize=len;
}

void Push(SqStake *S,int e){
    if (S->top-S->base>==S->StakeSize) {
        S->base=(int *)realloc(S->base,sizeof(int)*(S->StakeSize+Stake_Increment));
        if (!S->base) {
            printf("not eought memory\n");
            exit(0);
        }
        S->top=S->base+S->StakeSize;
        S->StakeSize+=Stake_Increment;
    }
    *S->top++=e;
}

int Pop(SqStake *S){
    int e;
    if (S->top==S->base) {
        printf("the stake is empty\n");
        exit(0);
    }
    e=*--S->top;
    return e;
}

int StakeEmpty(SqStake *S){
    if (S->base==S->top)
        return 1;
    else
        return 0;
}

void onversion(SqStake *S){
    int n;
    int e=0;
    printf("please input the numeber\n");
    scanf("%d",&n);
    while (n) {
        Push(S,n%8);
        n=n/8;
    }
    while (!StakeEmpty(S)) {
        e=Pop(S);
        printf("%d\n",e);
    }
    
}



int main(){
    SqStake S;
    InitiStake(&S,Stake_Init_Size);
    onversion(&S);
	system("pause");
    return 0;
    

}
