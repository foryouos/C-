#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#define MAXSIZE 100  //˳���Ĵ�С
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;   //���������ͣ���ֵ�Ǻ��������״̬����
typedef int ElemType;
//��ջ�Ľṹ��---���޵ĵ�����
typedef struct StackNode
{
	ElemType data;
	struct StackNode* next;
}StackNode,*LinkStack;

Status InitStack(LinkStack& S)
{
	//�����ս
	S = NULL;
	return OK;
}
//�ж���ջ�Ƿ�Ϊ��
Status StackEmpty(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	else
		return FALSE;
}
//��ջ����ջ
Status Push(LinkStack& S, ElemType e)
{
	LinkStack p;
	p = (StackNode*)malloc(sizeof(StackNode));  //�����½��p
	p->data = e;			//���½��������Ϊe
	p->next = S;			//���½�����ջ��
	S = p;					//�޸�ջ��ָ��
	return OK;

}

//��ջ�ĳ�ջ
Status Pop(LinkStack& S, ElemType& e)
{
	LinkStack p;
	if (S == NULL)
		return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	free(p);
	return OK;

}
//ȥջ��Ԫ��
ElemType GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}

int main(void)
{
	LinkStack S;
	InitStack(S);
	StackEmpty(S);

	return 0;
}