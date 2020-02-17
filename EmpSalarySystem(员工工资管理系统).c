//
//  SalarySystem.c
//  
//
//  Created by tujunfeng on 18/5/17.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max 500



struct emploee         //职工数据结构
{
    char num[7];      //员工工资卡号
    char name[10];    //员工姓名
    char gender;      //员工性别
    float wage1;      //员工的基本工资
    float wage2;      //员工的绩效工资
    float funds;      //员工的住房公积金
    float TAXfee;     //员工的个人所得税
    float wage3;      //员工的实发工资
}emp[Max],emploee;

struct manager          //管理员结构体
{
    char account[10];      //管理员账号
    char password[10];     //管理员密码
}manag;

void enter();
void search_num();
void search_name();
void browse();
void delete_num();
int LoginSystem();
void menu();
void modi_num();

int n;   //员工的总数

int main()
{
    if(LoginSystem())
        menu();
	system("pause");
    return 0;
}

int LoginSystem(){
    FILE *fp;
    int n=2;
    char account[10];
    char password[10];
    printf("************* ************* ***************\n");
    printf("********* 欢迎使用职工工资管理系统 ************\n");
    printf("          账号:");
    gets(account);
    printf("          密码:");
    gets(password);
    fp=fopen("E:\\admin.txt","r");
    
    while (n) {
        while (!feof(fp)) {
            fscanf(fp,"%s %s",manag.account,manag.password);
            if (strcmp(manag.account,account)==0 && strcmp(manag.password,password)==0){
                printf("登录成功,按回车进入操作界面\n");
                getchar();
                return 1;
            }
            
        }
		printf("       密码账号不正确,请重新输入,你还有%d次机会\n",n--);
        rewind(fp);
        printf("          账号:");
        gets(account);
        printf("          密码:");
        gets(password);
    }
    printf("           错误次数过多，按回车键退出\n");
    fclose(fp);
    getchar();
    return 0;
}

void menu(){
    int choose,w1;
	char w2='N';
	do{
		do{
			printf("************* 职工工资管理系统 **************\n");
			printf("*            1-----输入职工信息                   *\n");
			printf("*            2-----根据工资卡号查询职工信息         *\n");
			printf("*            3-----根据姓名查询职工信息            *\n");
			printf("*            4-----按照工资卡号升序浏览全部职工信息  *\n");
			printf("*            5-----按照工资卡号修改职工信息  *\n");
			printf("*            6-----根据工资卡号删除职工信息         *\n");
			printf("*            7-----退出程序                      *\n");
			printf("***************************************************\n");
			printf("       输入您的选择(1-7):[ ]\b\b");
			scanf("%d",&choose);
			if(choose<1||choose>6)                                    //对选择的数字作判断
			{
				w1=1;
				printf("your choice is not between 1 and 9,Please input again:");
				getchar();
			}
			else
				w1=0;
		}while(w1==1);
		switch(choose)
		{
			case 1:enter();       break;
			case 2:search_num();   break;
			case 3:search_name();     break;
			case 4:browse();   break;
			case 5:modi_num();   break;
			case 6:delete_num();   break;
			case 7:printf("\n×××××××工资管理系统退出成功！×××××××\n");
			default:exit(0);  //退出系统,exit(0)函数功能是退出程序。
		}
		printf("是否继续操作：（Y/N）");
		scanf(" %c",&w2);
	}while(w2=='Y'||w2=='y');
    
}


void enter()
{
    FILE *fp;
    int n,i;
    if ((fp=fopen("E:\\emp.txt","wb"))==NULL)
    {
        
        printf("建立工资文件失败\n");
        exit(1);
    }
    printf("输入职工人数:");
    scanf("%d",&n);
    printf("输入格式: 工资卡号    姓名  性别  基本工资 绩效工资 公积金 所得税 \n");
    for(i=0;i<n;i++)   /*  循环获取n个职工记录 */
    {
        printf("第%d个职工:",i+1);
        scanf("%s%s %c%f%f%f%f",emp[i].num,emp[i].name,&emp[i].gender,
              &emp[i].wage1,&emp[i].wage2,&emp[i].funds,&emp[i].TAXfee);
        emp[i].wage3=emp[i].wage1+emp[i].wage2-emp[i].funds-emp[i].TAXfee;
    }
    for(i=0;i<n;i++)      /*将n个职工记录写入文件*/
        fwrite(&emp[i],sizeof(struct emploee),1,fp);
    fclose(fp);
}

void search_num(){
    FILE *fp;
    int i;
    char num[5];
    if((fp=fopen("E:\\emp.txt","rb"))==NULL)
    {
        printf("打开工资文件失败\n");
        exit(1);
    }
    printf("要查询的工资卡:");
    scanf("%s",num);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++){
        if(!strcmp(emp[i].num,num)) break;
    }
    if(feof(fp))
    {
        printf("\t查无此人\n");
        exit(2);
    }
    printf(" 工资卡号   姓名  性别  基本工资  绩效工资  公积金  所得税  实发工资\n");
    printf("%8s%10s%2c     %.1f      %.1f      %.1f      %.1f      %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
          emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    fclose(fp);
}

void search_name(){
    FILE *fp;
    int i;
    char name[10];
    if((fp=fopen("E:\\emp.txt","rb"))==NULL)
    {
        printf("打开工资文件失败\n");
        exit(1);
    }
    printf("要查询的姓名:");
    scanf("%s",name);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++){
        if(!strcmp(emp[i].name,name)) break;
    }
    if(feof(fp))
    {
        printf("\t查无此人\n");
        exit(2);
    }
    printf(" 工资卡号 姓名  性别  基本工资  绩效工资  公积金  所得税  实发工资\n");
    printf("%8s%10s%2c      %.1f     %.1f     %.1f     %.1f     %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
           emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    fclose(fp);
}

void browse(){
    struct emploee* empp[Max];
    struct emploee* tempt=NULL;
    int i,j,n;
    FILE *fp;
    if((fp=fopen("E:\\emp.txt","rb"))==NULL)
    {
        printf("打开工资文件失败\n");
        exit(1);
    }
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++);
    n=i;
    fclose(fp);
    for (i=0; i<n; i++) {
        empp[i]=emp+i;
    }
    for (i=0; i<n-1; i++) {
        for (j=i+1; j<n; j++){
            if (strcmp(empp[j]->num,empp[i]->num)<0) {
                tempt=empp[i];
                empp[i]=empp[j];
                empp[j]=tempt;
            }
        }
    }
    for (i=0; i<n; i++) {
        printf(" 工资卡号 姓名  性别  基本工资  绩效工资  公积金  所得税  实发工资\n");
        printf("%8s%10s%2c      %.1f     %.1f     %.1f     %.1f     %.1f\n",empp[i]->num,
               empp[i]->name,empp[i]->gender,empp[i]->wage1,empp[i]->wage2,
               empp[i]->funds,empp[i]->TAXfee,empp[i]->wage3);
    }
}
void delete_num(){
    int i,j,n;
    FILE *fp;
    char num[7];
    if((fp=fopen("E:\\emp.txt","rb"))==NULL)
    {
        printf("不能打开emp文件\n");
        exit(1);
    }
    for(n=0;fread(emp+n,sizeof(struct emploee),1,fp);n++);
    fclose(fp);
    printf("要删除的职工号:");
    scanf("%s",num);
    for(i=0;(strcmp(emp[i].num,num)&&i<n);i++);
    if(i>=n)
    {
        printf("\t没有%s职工号的职工\n",num);
        exit(2);
    }
    fp=fopen("E:\\emp.txt","wb");
    if(n==1)  /*一个记录已经删除了*/
    {
        printf("只有一个数据自动清空\n");
        fclose(fp);
        exit(3);
    }
    for(j=0;j<i;j++)
        fwrite(&emp[j],sizeof(struct emploee),1,fp);
    for(j=i+1;j<n;j++)
        fwrite(&emp[j],sizeof(struct emploee),1,fp);
    fclose(fp);
    browse();
}
void modi_num()
{
    FILE *fp;
    int i,j;
    char num[7];
    if((fp=fopen("E:\\emp.txt","rb+"))==NULL)
    {
        printf("不能打开emp文件\n");
        exit(1);
    }
    printf("要修改的职工号:");
    scanf("%s",num);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++)
        if(!strcmp(emp[i].num,num))break;
    if(feof(fp))
    {
        printf("\t没有%s职工号的职工\n",num);
        return;
    }
    printf(" 工资卡号 姓名  性别  基本工资  绩效工资  公积金  所得税  实发工资\n");
           printf("%8s%10s%2c     %.1f      %.1f      %.1f      %.1f      %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
                  emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    printf("输入格式: 工资卡号    姓名  性别  基本工资 绩效工资 公积金 所得税 \n");
    printf("第%d个记录:",i+1);
           scanf("%s%s %c%f%f%f%f",emploee.num,emploee.name,&emploee.gender,
                 &emploee.wage1,&emploee.wage2,&emploee.funds,&emploee.TAXfee);
           emploee.wage3=emploee.wage1+emploee.wage2-emploee.funds-emploee.TAXfee;
    fseek(fp,-(long)sizeof(struct emploee),SEEK_CUR);  //文件指针指向该修改的记录开头
    fwrite(&emploee,sizeof(struct emploee),1,fp);  //用newemp覆盖当前记录
    printf(" 修改后:\n");
    rewind(fp);        //显示修改后的文件数据
    printf(" 工资卡号 姓名  性别  基本工资  绩效工资  公积金  所得税  实发工资\n");
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp)!=0;i++)
           printf("%8s%10s%2c     %.1f      %.1f      %.1f      %.1f      %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
                  emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    fclose(fp);
}

 

