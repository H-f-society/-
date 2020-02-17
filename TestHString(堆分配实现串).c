//
//  TestSString2.c
//  
//
//  Created by tujunfeng on 18/4/7.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct HString{
    char *ch;
    int length;
}HString;

void StrAssign(HString *S,char *ch){
    int len;
    int i;
    len=strlen(ch);
    S->ch=(char *)malloc(len);
    if(!S->ch){
        printf("not enough memory\n");
        exit(0);
    }
    for(i=0;i<len;i++){
        S->ch[i]=ch[i];
    }
    S->length=len;
}

void Concat(HString *T,HString *S1,HString *S2){
    int i;
    T->ch=(char *)malloc(S1->length+S2->length);
    if(!T->ch){
        printf("not enough memory\n");
        exit(0);
    }
    for(i=0;i<S1->length;i++){
        T->ch[i]=S1->ch[i];
    }
    for(i=0;i<S2->length;i++){
        T->ch[S1->length+i]=S2->ch[i];
    }
    T->length=S1->length+S2->length;
}

void SubStr(HString *sub,HString *S,int pos,int len){
    int i;
    if(pos<1||pos>S->length||len<1||len>S->length-pos+1){
        printf("the parament is wrong\n");
    }
    else{
        sub->ch=(char *)malloc(len);
        for(int i=1;i<=len;i++){
            sub->ch[i-1]=S->ch[pos+i-2];
        }
        sub->length=len;
    }
}

void PrintStr(HString *S){
    int i;
    for(i=0;i<S->length;i++){
        printf("%c",*(S->ch+i));
    }
}

int main(){
    int pos,len;
    char ch1[10];
    char ch2[10];
    HString S1,S2,T,sub;
    printf("input the S1\n");
    gets(ch1);
    StrAssign(&S1,ch1);
    
    printf("input the S2\n");
    gets(ch2);
    StrAssign(&S2,ch2);
    printf("----------------\n");
    printf("the cobination of S1 and S2\n");
    Concat(&T,&S1,&S2);
    PrintStr(&T);
    
    printf("----------------\n");
    printf("the location and the lenth of subString\n");
    scanf("%d,%d",&pos,&len);
    SubStr(&sub,&T,pos,len);
    PrintStr(&sub);
}









