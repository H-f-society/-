//
//  TestGlist.c
//  
//
//  Created by tujunfeng on 18/5/4.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Atom 0
#define List 1

typedef struct GLNode{
    int tag;
    union{
        int atom;
        struct {
            struct GLNode *hp,*tp;
        }ptr;
    };
}GLNode;

int GlistDepth(GLNode *gl){
    int dep=0;
    int max;
    struct GLNode *pp;
    if (!gl)
        return 1;
    if(gl->tag==0)
        return 0;
    for(max=0,pp=gl;pp;pp=pp->ptr.tp){
        dep=GlistDepth(pp->ptr.hp);
        if(dep>max)
            max=dep;
    }
    return max+1;
}

void substring(char *sub,char *s,int i,int j){
    int n;
    for (n=0; n<j; n++) {
        sub[n]=s[n+i-1];
    }
    sub[n]='\0';
}

void sever(char *sub,char *hsub){
    int n=strlen(sub);
    int i=0;
    int k=0;
    char ch[2];
    do {
        ++i;
        substring(ch,sub,i,1);
        if (*ch=='(')
            ++k;
        else if(*ch==')')
            --k;
    } while (i<n&&(*ch!=','||k!=0));
    if (i<n) {
        substring(hsub,sub,1,i-1);
        substring(sub,sub,i+1,n-i);
    }
    else{
        strcpy(hsub,sub);
        sub[0]='\0';
    }
}

void CreateGList(GLNode **gl,char *s){
    GLNode *p;
    GLNode *q;
    char sub[30]="";
    char hsub[30]="";
    if(*s=='\0'){
        *gl=NULL;
    }
    else {
        *gl=(GLNode *)malloc(sizeof(GLNode));
        if (strlen(s)==1) {
            (*gl)->tag=0;
            (*gl)->atom=*s;
        }
        else{
            (*gl)->tag=List;
            p=*gl;
            substring(sub,s,2,strlen(s)-2);
            do {
                sever(sub,hsub);
                CreateGList(&p->ptr.hp,hsub);
                q=p;
                if (*sub!='\0') {
                    p=(GLNode *)malloc(sizeof(GLNode));
                    p->tag=1;
                    q->ptr.tp=p;
                }
            } while (*sub!='\0');
            q->ptr.tp=NULL;
        }
    }
}



void printGList(GLNode *ls)
{
    if(ls != NULL)
    {
        if(ls->tag == 0)
        {
            printf("%c " ,ls->atom) ;
        }
        else
        {
            printGList(ls->ptr.hp) ;
            printGList(ls->ptr.tp) ;
        }
    }
}

int main(){
    int depth;
    GLNode *gl;
    char s[30];
    printf("请输入要创建的广义表");
    gets(s);
    CreateGList(&gl,s);
    printGList(gl);
    depth=GlistDepth(gl);
    printf("the depth is %d\n",depth);
}
