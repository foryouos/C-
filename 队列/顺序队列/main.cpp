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

typedef struct SqQueue
{
	ElemType* base;//��ʼ����̬����洢�ռ�
	int front;  //ͷָ��
	int rear;   //βָ��
}SqQueue;
Status InitQueue(SqQueue* &Q)
{
	Q->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	if (!Q->base)
		exit(OVERFLOW);
	Q->front = Q->rear = 0;  //ͷָ�룬βָ����Ϊ�գ�����Ϊ��
	return OK;
}
//����еĳ���
int QueueLength(SqQueue* Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;  //ѭ������
}
//ѭ�����е����
Status EnQueue(SqQueue*& Q, ElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;//����
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}
//����
Status DeQueue(SqQueue*& Q, ElemType& e)
{
	if (Q->front == Q->rear)
		return ERROR;//�ӿ�
	e = Q->base[Q->front];		//�����ͷԪ��
	Q->front = (Q->front + 1) % MAXSIZE;  //��ͷָ��+1
	return OK;
}
ElemType GetHead(SqQueue* Q)
{
	if (Q->front != Q->rear)   //���в�Ϊ��
		return Q->base[Q->front];  //���ض�ͷָ��Ԫ�ص�ֵ����ͷָ�벻��
}


int main(void)
{
	SqQueue* S;

	return 0;
}

