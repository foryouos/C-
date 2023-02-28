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

typedef struct 
{
	ElemType* base;
	ElemType* top;
	int stacksize;  //ջ�����������
}SqStack;
Status InitStack(SqStack* &S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = MAXSIZE;
}
Status StackEmpty(SqStack* S)
{
	if (S->top == S->base)
		return TRUE;
	else
		return FALSE;
}
int StackLength(SqStack* S)
{
	return S->top - S->base;
}
//����˳��ջ
Status DestoryStack(SqStack*& S)
{
	if (S->base)
	{
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}
//��ջ
Status Push(SqStack* &S, ElemType e)
{
	if (S->top - S->base == S->stacksize)
		return ERROR;
	*S->top++ = e;
	/*�൱��
	*S->top=e;
	S->top++*/
	return OK;
}
//��ջ
Status Pop(SqStack*& S, ElemType& e)
{
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S->top == S->base)
		return ERROR;
	e = *--S->top;
	//�൱��
	//--S->top;
	//e=*S->top;

	return OK;
}
void Print_Stack(SqStack* S)
{
	while (S->base != S->top)
	{
		S->top--;
		printf("%d\n", *S->top);
		
	}
		

}
int main(void)
{
	SqStack* S;
	int e;
	int n;
	char ch;
	S = (SqStack*)malloc(sizeof(SqStack));
	InitStack(S);
	//StackEmpty(S);
	//DestoryStack(S);
	printf("��ջ��������������Ҫ��ջ�ĸ�����");
	scanf("%d", &n);
	for (int j = 0; j < n; j++)
	{
		printf("������%d��ջ", j + 1);
		scanf("%d", &e);
		Push(S, e);
		scanf("%c", &ch);
	}
	Print_Stack(S);
	printf("ջ�����ϣ�\n");
	return 0;
}
