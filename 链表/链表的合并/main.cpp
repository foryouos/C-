#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#define List_INIT_SIZE 100  //˳���Ĵ�С
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;   //���������ͣ���ֵ�Ǻ��������״̬����
typedef int ElemType;

typedef struct Lnode	//����������Ľṹ����
{
	ElemType data;		//������
	struct Lnode* next;		//��һ������ָ����Ƕ�׶���
}Lnode, * LinkList;  //LinkListΪָ��ṹ��Lnode��ָ������

//�������ʼ��
Status InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(Lnode)); //������C++: new Lnode
	L->next = NULL;  //��һ�����Ϊ��
	return OK;
}



//���س���ֵ
int ListLength(Lnode* L)
{
	LinkList p;
	p = L->next;
	int length = 0;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}



//β�巨
void CreateList_R(LinkList& L, int n)
{
	Lnode* r;
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p;
		p = (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p;
		r = p;
	}
}

//˳������ĺϲ�
void seq_uion(LinkList la, LinkList lb,LinkList &lc)
{
	LinkList p = la->next; //����p
	LinkList q = lb->next; 
	LinkList c = lc;
	while(p&&q) //���κ�һ�������Ϊ��
	{
		if (p->data <= q->data)    //�Ƚ�С��ֵ���룬β��
		{
			c->next = p;
			c = p;
			p = p->next;
		}
		else  
		{
			c->next = q;
			c = q;
			q = q->next;
		}
	}
	c->next = p ? p : q; //������Ϊ������ϵ�ȫ����������
}
void Print_seq(LinkList L)
{
	printf("����ϲ����˳������:\n");
	L = L->next;
	for (int i = 0; i < ListLength(L); i++)
	{
		printf("%d ", L->data);
		L = L->next;
	}
}

int main(void)
{
	LinkList la;  //�൱��Lnode* L;
	LinkList lb;
	LinkList lc;
	printf("la����5�����ÿո����:");
	CreateList_R(la, 5); //ͷ�巨
	printf("lb����4�����ÿո����:");
	CreateList_R(lb, 4);
	InitList(lc);
	seq_uion(la, lb, lc);
	Print_seq(lc);
	return 0;
}