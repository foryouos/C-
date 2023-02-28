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
}Lnode,*LinkList;  //LinkListΪָ��ṹ��Lnode��ָ������

//�������ʼ��
Status InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(Lnode)); //������C++: new Lnode
	L->next = NULL;  //��һ�����Ϊ��
	return OK;
}
//�ж������Ƿ�Ϊ��
int ListEmpty(LinkList L)
{
	if (L->next) //�ǿ�,����
	{
		return 0;
	}
	else
		return 1;
}
//����������٣���ͷָ�뿪ʼ�������ͷ����н��
Status DestoryList_L(LinkList& L)
{
	Lnode* P;
	while (L)//��L���ǿ�ʹ
	{
		P = L;
		L = L->next;
		free(P);
	}
	return OK;
}
//���������ͷָ���ͷ����Դ���)
Status ClearList(LinkList& L)
{
	Lnode* p, * q;
	p = L->next;  //����ͷָ��
	while (p)   //��ĩβ
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; //ͷ���ָ����Ϊ��
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
//ȡֵ��ȡ�������е�i��Ԫ�أ�ֵ���ظ�e
Status GetElem_L(LinkList L, int i, ElemType& e)
{
	Lnode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //���ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) //��i��Ԫ�ز�����
		return ERROR;
	e = p->data;
	return OK;
}
//������Ĳ���
/*�����Ա�L�в���ֵΪe������Ԫ�أ��ҵ�����L��ֵΪe������Ԫ�صĵ�ַ��ʧ�ܷ���NULL*/
Lnode* LocateElem(LinkList L, ElemType e)
{
	Lnode* p;
	p = L->next;
	while (p && p->data != e)
	{
		p = p->next;
	}
	return p;  //��������Ԫ�صĵ�ַ
}
//����Ԫ�ض�Ӧ�����
int LocateElem_L(LinkList L, ElemType e)
{
	Lnode* p;
	p = L->next;
	int j = 1;
	while (p && p->data != e)
	{
		p = p->next;
		j++;
	}
	if (p)
	{
		return j;
	}
	else
	{
		return 0;
	}
}
//��L�е�i��Ԫ��֮ǰ��������Ԫ��e
Status ListInsert_L(LinkList& L, int i, ElemType e)
{
	Lnode* s;
	Lnode* p=L;
	int j= 0;
	while (p && j < i - 1)//��i����L�ĳ��ȣ�pѭ�����ա�����iΪ����
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	s = (Lnode*)malloc(sizeof(Lnode));  //�����½ڵ㣬�����s����������Ϊe
	s->data = e;
	s->next = p->next; //�����s����L��
	p->next = s;
}
//�����Ա�L�е�i������Ԫ��ɾ��
Status ListDelete_L(LinkList& L, int i, ElemType& e)
{
	Lnode* p = L;
	int j = 0;
	while (p->next && j < i - 1) //��pָ����ǰ��
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)  //ɾ��λ�ò�����
	{
		return ERROR;
	}
	Lnode* q = p->next;  //��ʱ���汻ɾ���ĵ�ַ�Ա��ͷ�
	p->next = q->next;
	e = p->data;
	free(p);
	return OK;
}
//ͷ�巨
void CreateList_L(LinkList& L, int n)
{
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = n; i > 0; i--)
	{
		Lnode* p;
		p = (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
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
		p= (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p;
		r = p;
	}
}
//���Ա�ĺϲ�
void Union(LinkList& la, LinkList lb)
{
	int e;
	int la_len =ListLength(la);
	int lb_len = ListLength(lb);
	for (int i = 1; i < lb_len; i++)
	{
		GetElem_L(lb, i, e);
		if (!LocateElem(la, e))
		{
			ListInsert_L(la, ++la_len, e);
		}
	}

}


int main(void)
{
	LinkList L;  //�൱��Lnode* L;
	//�������ʼ��
	//InitList(L);
	//�ж������Ƿ�Ϊ�� ,������ָ�����Ƿ�Ϊ��
	//ListEmpty(L);
	//�����������
	//DestoryList_L(L);
	//�����������ͷָ���ͷ���
	//ClearList(L);
	//������ı�
	//int length = ListLength(L);
	//��ȡ�����е�i��Ԫ�ص�ֵ
	int e;
	//GetElem_L(L, 2, e);
	//�����������ڵ�λ��  ��ַ/���
	//��ַ
	//LocateElem(L, 3);//����ֵΪ3������Ԫ�ص�ַ
	//����3�ķ������
	//LocateElem_L(L, 3);//����ֵΪ3�����
	//�ڵ�i�����ǰ����ֵΪe���½��
	//ListDelete_L(L, 3, e);
	//������Ľ���
	//ͷ�巨
	//printf("ʹ��β�巨��������Ԫ��:");
	//CreateList_L(L, 3);
	
	

	return 0;
}