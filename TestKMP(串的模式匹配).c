//
//  TestKMP.c
//  
//
//  Created by tujunfeng on 18/4/8.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Size 20

typedef char SString[Max_Size+1];


void StrAssign(SString T,char *chars){
    int i;
    if(strlen(chars)>Max_Size){
        for(i=1;i<=Max_Size;i++){
            T[i]=*(chars+i-1);
            T[0]=Max_Size;
        }
    }
    else{
        for(i=1;i<=strlen(chars);i++){
            T[i]=*(chars+i-1);
        }
        T[0]=strlen(chars);
    }
}

void Strindex(SString S,SString Sub){
    int j=1;
    int i=1;
    while(i<=S[0]&&j<=Sub[0]){
        if(S[i]==Sub[j]){
            i++;
            j++;
        }
        else{
            j=1;
            i=i-j+2;
        }
    }
    
    if(j>Sub[0]){
        printf("the location is %d\n",i-Sub[0]);
    }
    else{
        printf("did not exist\n");
    }
    
}

void getNext(SString Sub,int next[]){
    int i=1;
    int j=0;
    next[1]=0;
    while (i<Sub[0]) {
        if(j==0||Sub[i]==Sub[j]){
            i++;
            j++;
            next[i]=j;
        }
        else{
            j=next[j];
        }
    }
}

void StrKMP(SString S,SString Sub){
    int i=1;
    int j=1;
    int next[30];
    getNext(Sub,next);
    while (i<=S[0]&&j<=Sub[0]) {
        if(j==0||S[i]==Sub[j]){
            i++;
            j++;
        }
        else{
            j=next[j];
        }
    }
    if(j>Sub[0]){
        printf("the location is %d\n",i-Sub[0]);
    }
    else{
        printf("did not exist\n");
    }
}





int main(){
    SString S,Sub;
    char ch1[Max_Size];
    char sub1[Max_Size];
    
    printf("Input S:\n");
    gets(ch1);
    StrAssign(S,ch1);
    printf("Input sub:\n");
    gets(sub1);
    StrAssign(Sub,sub1);
    Strindex(S,Sub);
    StrKMP(S,Sub);
    
    
    
}

