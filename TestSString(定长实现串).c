//
//  TestSString.c
//  
//
//  Created by tujunfeng on 18/3/31.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRLEN 14
typedef char SString[MAXSTRLEN+1];//char string1[15];   =>  SString string1;
											


void StrAssign(SString T,char *chars){
    int i;
    if(strlen(chars)>MAXSTRLEN){
        for(i=1;i<=MAXSTRLEN;i++){
            T[i]=*(chars+i-1);
            T[0]=MAXSTRLEN;
        }
    }
    else{
        for(i=1;i<=strlen(chars);i++){
            T[i]=*(chars+i-1);
        }
        T[0]=strlen(chars);
    }
}

void StrCopy(SString T,SString S){
    int i;
    for (i = 1; i <= S[0]; ++i){
        T[i]=S[i];
    }
    T[0]=S[0];
}

void Concat(SString T,SString S1,SString S2){
    int i;
    if(S1[0]==MAXSTRLEN){
        for(i=1;i<=MAXSTRLEN;i++){
            T[i] = S1[i];
        }
        T[0]=MAXSTRLEN;
    }
    else if(S1[0]+S2[0]<=MAXSTRLEN){
        for(i=1;i<=S1[0];i++){
            T[i] = S1[i];
        }
        for(i=1;i<=S2[0];i++){
            T[S1[0]+i]=S2[i];
        }
        T[0]=S1[0]+S2[0];
    }
    else{
        for(i=1;i<=S1[0];i++){
            T[i] = S1[i];
            }
        for(i=1;i<=MAXSTRLEN-S1[0];i++){
            T[S1[0]+i]=S2[i];
            }
        T[0]=MAXSTRLEN;
    }
    
}


void PrintStr(SString S){
    int i;
    for(i=1;i<=S[0];i++){
        printf("%c",S[i]);
    }
    printf("\n");
}

int main(){
    SString S1,S2,T;
    char str1[MAXSTRLEN];
    char str2[MAXSTRLEN];
    printf("Input S1:\n");
    gets(str1);
    StrAssign(S1,str1);
    printf("Input S2:\n");
    fgets(str2,5,stdio);
    StrAssign(S2,str2);
    
    printf("----------------------------------\n");
    printf("conbination of S1 and S2\n");
    Concat(T,S1,S2);
    PrintStr(T);
    return 0;
    
    
}

