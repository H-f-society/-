//
//  TestMazePath.c
//  
//
//  Created by tujunfeng on 18/9/30.
//
//

#include <stdio.h>
#include <stdlib.h>

//迷宫的布局放入到一个二维的数组中
                   //nowy:0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9  nowx:
const int mizu[10][10] = {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1,  //0
                          1 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1,  //1
                          1 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 1,  //2
                          1 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 1 , 1,  //3
                          1 , 0 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1,  //4
                          1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 1,  //5
                          1 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1,  //6
                          1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 , 1,  //7
                          1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1,  //8
                          1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1   //9
} ;
int flag[10][10] = {0} ;
typedef int TypeData ;
typedef struct node{
    TypeData datax ;
    TypeData datay ;
    struct node* next ;
}Node , *LinkList ;

typedef struct stack{
    LinkList top ;
}STACK ;
//************************函数声明******************************
int stackInit(STACK* s ) ;
int pushStack(STACK* s ,TypeData x , TypeData y) ;
void popStack(STACK* s , TypeData* x , TypeData* y) ;
int isStackEmpty(STACK* s) ;
int mizePath(STACK* s ,TypeData end_x , TypeData end_y ) ;
int passMizu(TypeData x , TypeData y ) ;
//**********************************************************

//链栈的初始化
int stackInit(STACK* s )
{
    LinkList p = (LinkList)malloc(sizeof(Node)) ;
    if(!p)   return -1 ;
    p->next = NULL ;
    p->datax = -1 ;
    p->datay = -1 ;
    s->top = p ;
    return 1 ;
}
//入栈操作
int pushStack(STACK* s ,TypeData x , TypeData y)
{
    
    LinkList p = (LinkList)malloc(sizeof(Node)) ;
    if(!p)   return -1 ;  //分配内存失败
    p->datax = x ;
    p->datay = y ;
    p->next = s->top ;
    s->top = p ;
    return 1 ;
}
//出栈的操作
void popStack(STACK* s , TypeData* x , TypeData* y)
{
    LinkList p = s->top ;
    s->top = p->next ;
    (*x) = s->top->datax ;
    (*y) = s->top->datay ;
    
    free(p) ;
}
//判断栈是否为空
//1 空  0 不空
int isStackEmpty(STACK* s)
{
    if(s->top->datax == -1)  //栈空
        return 1 ;
    return 0 ;
}
//找到最佳路径
//end_x , end_y为结束的坐标
//上 、右、下、左寻找方式
int mizePath(STACK* s ,TypeData end_x , TypeData end_y )
{
    pushStack(s , 1 ,1) ; //初始坐标压栈
    TypeData nowx = 1 , nowy = 1 ;
    flag[nowy][nowx] = 1 ;  //该坐标已经被占用不能再通过
    while(!isStackEmpty(s)) //当栈不空的时候
    {
        if((nowy == end_x)&&(nowx == end_y))
        {
            return 1 ;
        }
        //		printf("nowx = %d  nowy = %d\n",nowx , nowy) ;
        //		system("PAUSE") ;
        if(passMizu(nowy , nowx-1))   //先向上寻找
        {
            nowx = nowx - 1 ; //坐标更改
            pushStack(s , nowy , nowx) ;  //把该坐标压栈
            flag[nowx][nowy] = 1 ;  //该坐标已经被占用不能再通过
        }
        else  if(passMizu(nowy+1 , nowx)) //向右寻找
        {
            nowy = nowy + 1 ;
            pushStack(s , nowy , nowx) ;  //把该坐标压栈
            flag[nowx][nowy] = 1 ;  //该坐标已经被占用不能再通过
        }
        else if(passMizu(nowy , nowx+1)) //向下寻找
        {
            nowx = nowx + 1 ;
            pushStack(s , nowy , nowx) ;  //把该坐标压栈
            flag[nowx][nowy] = 1 ;  //该坐标已经被占用不能再通过
        }
        else if(passMizu(nowy-1 , nowx)) //向左寻找
        {
            nowy = nowy - 1 ;
            pushStack(s , nowy , nowx) ;  //把该坐标压栈
            flag[nowx][nowy] = 1 ;  //该坐标已经被占用不能再通过
        }
        else  //都行不通
        {
            popStack(s , &nowy , &nowx) ;
        }
        
    } //while(!isStackEmpty(s)) //当栈不空的时候
    return 0 ;
}
//判断该位置是否可通
int passMizu(TypeData x , TypeData y )
{
    if((x > 9)||(y > 9))
        return 0 ;  //越界不可通
    if(mizu[y][x])
        return 0 ;  //该位置是墙，不可通
    if(flag[y][x])
        return 0 ;  //该坐标已经被占用，不能通过
    return 1 ;
}
//打印栈中的数据
int printStackData(STACK s)
{
    STACK temp ;  //新建一个临时的栈
    stackInit(&temp) ;
    if(s.top->datax == -1)  return 0 ; //栈为空
    while(s.top->datax != -1)
    {
        pushStack(&temp,s.top->datax,s.top->datay);
        s.top = s.top->next ;
    }
    while(temp.top->datax != -1)
    {
        printf("(%d,%d)\n",temp.top->datax , temp.top->datay) ;
        temp.top = temp.top->next ;
    } 
    return 1 ;
}

void initmaze(){//生成迷宫
    int a,b;
    printf("生成的迷宫是:\n");
    printf("0,1,2,3,4,5,6,7,8,9\n");
    for(a=0;a<10;a++){
        for(b=0;b<10;b++)
            printf(mizu[a][b]?"# ":"  ");//输出迷宫图形
        printf(" %d\n",a);
    }
}



int main()
{
    STACK mi_stack ; 
    int i = 0 , j = 0 ;
    stackInit(&mi_stack) ;
    initmaze();
    if(mizePath(&mi_stack , 8 , 8))
    {
        printStackData(mi_stack) ; //把坐标倒叙打印出来 
    }	
    else printf("没有通路！\n") ; 
    
    return  0 ;
}


