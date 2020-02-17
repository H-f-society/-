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



struct emploee         //ְ�����ݽṹ
{
    char num[7];      //Ա�����ʿ���
    char name[10];    //Ա������
    char gender;      //Ա���Ա�
    float wage1;      //Ա���Ļ�������
    float wage2;      //Ա���ļ�Ч����
    float funds;      //Ա����ס��������
    float TAXfee;     //Ա���ĸ�������˰
    float wage3;      //Ա����ʵ������
}emp[Max],emploee;

struct manager          //����Ա�ṹ��
{
    char account[10];      //����Ա�˺�
    char password[10];     //����Ա����
}manag;

void enter();
void search_num();
void search_name();
void browse();
void delete_num();
int LoginSystem();
void menu();
void modi_num();

int n;   //Ա��������

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
    printf("********* ��ӭʹ��ְ�����ʹ���ϵͳ ************\n");
    printf("          �˺�:");
    gets(account);
    printf("          ����:");
    gets(password);
    fp=fopen("E:\\admin.txt","r");
    
    while (n) {
        while (!feof(fp)) {
            fscanf(fp,"%s %s",manag.account,manag.password);
            if (strcmp(manag.account,account)==0 && strcmp(manag.password,password)==0){
                printf("��¼�ɹ�,���س������������\n");
                getchar();
                return 1;
            }
            
        }
		printf("       �����˺Ų���ȷ,����������,�㻹��%d�λ���\n",n--);
        rewind(fp);
        printf("          �˺�:");
        gets(account);
        printf("          ����:");
        gets(password);
    }
    printf("           ����������࣬���س����˳�\n");
    fclose(fp);
    getchar();
    return 0;
}

void menu(){
    int choose,w1;
	char w2='N';
	do{
		do{
			printf("************* ְ�����ʹ���ϵͳ **************\n");
			printf("*            1-----����ְ����Ϣ                   *\n");
			printf("*            2-----���ݹ��ʿ��Ų�ѯְ����Ϣ         *\n");
			printf("*            3-----����������ѯְ����Ϣ            *\n");
			printf("*            4-----���չ��ʿ����������ȫ��ְ����Ϣ  *\n");
			printf("*            5-----���չ��ʿ����޸�ְ����Ϣ  *\n");
			printf("*            6-----���ݹ��ʿ���ɾ��ְ����Ϣ         *\n");
			printf("*            7-----�˳�����                      *\n");
			printf("***************************************************\n");
			printf("       ��������ѡ��(1-7):[ ]\b\b");
			scanf("%d",&choose);
			if(choose<1||choose>6)                                    //��ѡ����������ж�
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
			case 7:printf("\n�����������������ʹ���ϵͳ�˳��ɹ�����������������\n");
			default:exit(0);  //�˳�ϵͳ,exit(0)�����������˳�����
		}
		printf("�Ƿ������������Y/N��");
		scanf(" %c",&w2);
	}while(w2=='Y'||w2=='y');
    
}


void enter()
{
    FILE *fp;
    int n,i;
    if ((fp=fopen("E:\\emp.txt","wb"))==NULL)
    {
        
        printf("���������ļ�ʧ��\n");
        exit(1);
    }
    printf("����ְ������:");
    scanf("%d",&n);
    printf("�����ʽ: ���ʿ���    ����  �Ա�  �������� ��Ч���� ������ ����˰ \n");
    for(i=0;i<n;i++)   /*  ѭ����ȡn��ְ����¼ */
    {
        printf("��%d��ְ��:",i+1);
        scanf("%s%s %c%f%f%f%f",emp[i].num,emp[i].name,&emp[i].gender,
              &emp[i].wage1,&emp[i].wage2,&emp[i].funds,&emp[i].TAXfee);
        emp[i].wage3=emp[i].wage1+emp[i].wage2-emp[i].funds-emp[i].TAXfee;
    }
    for(i=0;i<n;i++)      /*��n��ְ����¼д���ļ�*/
        fwrite(&emp[i],sizeof(struct emploee),1,fp);
    fclose(fp);
}

void search_num(){
    FILE *fp;
    int i;
    char num[5];
    if((fp=fopen("E:\\emp.txt","rb"))==NULL)
    {
        printf("�򿪹����ļ�ʧ��\n");
        exit(1);
    }
    printf("Ҫ��ѯ�Ĺ��ʿ�:");
    scanf("%s",num);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++){
        if(!strcmp(emp[i].num,num)) break;
    }
    if(feof(fp))
    {
        printf("\t���޴���\n");
        exit(2);
    }
    printf(" ���ʿ���   ����  �Ա�  ��������  ��Ч����  ������  ����˰  ʵ������\n");
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
        printf("�򿪹����ļ�ʧ��\n");
        exit(1);
    }
    printf("Ҫ��ѯ������:");
    scanf("%s",name);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++){
        if(!strcmp(emp[i].name,name)) break;
    }
    if(feof(fp))
    {
        printf("\t���޴���\n");
        exit(2);
    }
    printf(" ���ʿ��� ����  �Ա�  ��������  ��Ч����  ������  ����˰  ʵ������\n");
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
        printf("�򿪹����ļ�ʧ��\n");
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
        printf(" ���ʿ��� ����  �Ա�  ��������  ��Ч����  ������  ����˰  ʵ������\n");
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
        printf("���ܴ�emp�ļ�\n");
        exit(1);
    }
    for(n=0;fread(emp+n,sizeof(struct emploee),1,fp);n++);
    fclose(fp);
    printf("Ҫɾ����ְ����:");
    scanf("%s",num);
    for(i=0;(strcmp(emp[i].num,num)&&i<n);i++);
    if(i>=n)
    {
        printf("\tû��%sְ���ŵ�ְ��\n",num);
        exit(2);
    }
    fp=fopen("E:\\emp.txt","wb");
    if(n==1)  /*һ����¼�Ѿ�ɾ����*/
    {
        printf("ֻ��һ�������Զ����\n");
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
        printf("���ܴ�emp�ļ�\n");
        exit(1);
    }
    printf("Ҫ�޸ĵ�ְ����:");
    scanf("%s",num);
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp);i++)
        if(!strcmp(emp[i].num,num))break;
    if(feof(fp))
    {
        printf("\tû��%sְ���ŵ�ְ��\n",num);
        return;
    }
    printf(" ���ʿ��� ����  �Ա�  ��������  ��Ч����  ������  ����˰  ʵ������\n");
           printf("%8s%10s%2c     %.1f      %.1f      %.1f      %.1f      %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
                  emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    printf("�����ʽ: ���ʿ���    ����  �Ա�  �������� ��Ч���� ������ ����˰ \n");
    printf("��%d����¼:",i+1);
           scanf("%s%s %c%f%f%f%f",emploee.num,emploee.name,&emploee.gender,
                 &emploee.wage1,&emploee.wage2,&emploee.funds,&emploee.TAXfee);
           emploee.wage3=emploee.wage1+emploee.wage2-emploee.funds-emploee.TAXfee;
    fseek(fp,-(long)sizeof(struct emploee),SEEK_CUR);  //�ļ�ָ��ָ����޸ĵļ�¼��ͷ
    fwrite(&emploee,sizeof(struct emploee),1,fp);  //��newemp���ǵ�ǰ��¼
    printf(" �޸ĺ�:\n");
    rewind(fp);        //��ʾ�޸ĺ���ļ�����
    printf(" ���ʿ��� ����  �Ա�  ��������  ��Ч����  ������  ����˰  ʵ������\n");
    for(i=0;fread(&emp[i],sizeof(struct emploee),1,fp)!=0;i++)
           printf("%8s%10s%2c     %.1f      %.1f      %.1f      %.1f      %.1f\n",emp[i].num,emp[i].name,emp[i].gender,
                  emp[i].wage1,emp[i].wage2,emp[i].funds,emp[i].TAXfee,emp[i].wage3);
    fclose(fp);
}

 

