//
//  BookIndex.c
//  
//
//  Created by tujunfeng on 18/10/22.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxBookNum 100
#define MaxKeyNum 50
#define MaxLineLen 100
#define MaxWordNum 20


typedef struct{
    char *ch;
    int length;
}HString;

typedef struct node{
    int data;
    struct node *next;
}node,*LinkList;

typedef struct{
    char item[MaxWordNum][15];
    int last;
}WordListType;

typedef struct{
    HString key;
    struct node *bnolist;
}IdxTermType;

typedef struct{
    IdxTermType item[MaxKeyNum+1];
    int last;
}IdxListType;

int bno;
char *Unkey[9]={"an","a","of","the","and","An","A","The","to"};
char buf[MaxLineLen];
WordListType wdlist;

void InitIdxList(IdxListType *index);
void ExtraKeyWord(FILE *fp);
void InsIdxList(IdxListType *Index);
int isKeyWord(char *ch);
void StrAssign(HString *S,char *ch);
int Locate(IdxListType *Index,HString *wd,int *b);
void insertNewKey(IdxListType *Index,int j,HString *wd);
struct node *InsertNode(struct node *head);
void PutText(IdxListType *Index,FILE *fp,int i);



void InitIdxList(IdxListType *index){
    StrAssign(&(index->item[0].key),"\0");
    index->item[0].bnolist=NULL;
    index->last=0;
}

void ExtraKeyWord(FILE *fp){
    int i=0;
    char *ch=NULL;
    char *saveptr=NULL;
    fscanf(fp,"%d",&bno);
    fgets(buf,MaxLineLen,fp);
    ch=strtok_r(buf," \n",&saveptr);
    while (ch!=NULL) {
        strcpy(wdlist.item[i++],ch);
        ch=strtok_r(NULL," \n",&saveptr);
    }
    wdlist.last=i;
}

void InsIdxList(IdxListType *Index){
    int i=0,j=0,b=0;
    HString wd;
    for(i=0;i<wdlist.last;i++){
        if (!isKeyWord(wdlist.item[i]))
            continue;
        StrAssign(&wd,wdlist.item[i]);
        j=Locate(Index,&wd,&b);
        if (!b) {
            insertNewKey(Index,j,&wd);
        }
        Index->item[j].bnolist=InsertNode(Index->item[j].bnolist);
    }
}

int isKeyWord(char *ch){
    int i;
    for (i=0; i<9 && strcmp(ch,Unkey[i]); i++);
    if(i>=9)
        return 1;
    else
        return 0;
}

void StrAssign(HString *S,char *ch){
    int len;
    int i;
    len=strlen(ch);
    if(!len){
        S->ch=(char *)malloc(1);
        S->ch[0]='\0';
        S->length=0;
    }
    else{
        S->ch=(char *)malloc(len+1);
        if(!S->ch){
            printf("not enough memory\n");
            exit(0);
        }
        strcpy(S->ch,ch);
        S->length=len;
    }
}

int Locate(IdxListType *Index,HString *wd,int *b){
    int i;
    for (i=Index->last; i>0; i--) {
        if(strcmp(Index->item[i].key.ch,wd->ch)<=0)
            break;
    }
    if (strcmp(Index->item[i].key.ch,wd->ch)==0) {
        *b=1;
        return i;
    }
    else{
        *b=0;
        return i+1;
    }
    
    
}

void insertNewKey(IdxListType *Index,int j,HString *wd){
    int i;
    for (i=Index->last; i>=j; i--) {
        Index->item[i+1]=Index->item[i];
    }
    Index->item[j].key.ch=wd->ch;
    Index->item[j].key.length=wd->length;
    Index->item[j].bnolist=NULL;
    ++Index->last;
}

struct node *InsertNode(struct node *head){
    struct node *tempt=head;
    struct node *pr=head;
    struct node *p=NULL;
    p=(struct node *)malloc(sizeof(struct node));
    p->data=bno;
    if (head==NULL) {
        head=p;
        p->next=NULL;
    }
    else{
        if(p->data<=head->data){
            p->next=head;
            head=p;
        }
        else{
            while(tempt!=NULL && p->data>tempt->data ){
                pr=tempt;
                tempt=tempt->next;
            }
            p->next=tempt;
            pr->next=p;
        }
    }
    return head;
}

void PutText(IdxListType *Index,FILE *fp,int i){
    struct node *tempt= Index->item[i].bnolist;
    fprintf(fp,"%-15s",Index->item[i].key.ch);
    while(tempt!=NULL){
        fprintf(fp,"%03d ",tempt->data);
        tempt=tempt->next;
    }
    fputc('\n',fp);
}


int main(){
    int i;
    FILE *fpr;
    FILE *fpw;
    IdxListType index;
    if(!(fpr=fopen("/Users/tujunfeng/Desktop/c_code/bookInfo.txt","rb")))
        exit(0);
    InitIdxList(&index);
    while (!feof(fpr)) {
        ExtraKeyWord(fpr);
        InsIdxList(&index);
    }
    fclose(fpr);
    
    if(!(fpw=fopen("/Users/tujunfeng/Desktop/c_code/bookIndex.txt","wb")))
        exit(0);
    for (i=1; i<=index.last; i++) {
        PutText(&index,fpw,i);
    }
    fclose(fpw);
    return 0;
}





















