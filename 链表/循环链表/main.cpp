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

typedef struct DulNode
{
	ElemType data;
	struct DulNode* prior, * next;
}DulNode,*DuLinklist;
DulNode* GetElem_Dul(DuLinklist L, int i)
{
	DulNode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //���ɨ�裬ֱ��pָ���i��Ԫ�ػ�pΪ��
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) //��i��Ԫ�ز�����
		return ERROR;
	return p;
}
//˫��ѭ������Ĳ���
int ListInsert_Dul(DuLinklist& L, int i, ElemType e)
{
	ElemType m;
	DulNode* p;
	if(!(p=GetElem_Dul(L,i)))
		return ERROR;
	DulNode* s;
	s = (DulNode*)malloc(sizeof(DulNode));
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->next = s;
	return OK;
}
//˫�������ɾ��,ɾ����ͷ����˫��ѭ������L�ĵ�i��Ԫ�أ�����e����
int ListDelete_Dul(DuLinklist& L, int i, ElemType& e)
{
	DulNode* p;
	if (!(p = GetElem_Dul(L, i)))
		return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

int main(void)
{

	printf("hello word!\n");
	return 0;
}