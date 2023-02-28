#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define List_INIT_SIZE 10  //˳���Ĵ�С
typedef int Status;
typedef int ElemType;
typedef struct SqList
{
	ElemType* elem;
	int length;
};
Status InitList_Sq(struct SqList& L)
{
	L.elem = (ElemType*)malloc(sizeof(ElemType) * List_INIT_SIZE);
	if (!L.elem)
		exit(OVERFLOW); //�˳���������Ϊ1�쳣�˳���0�����˳�
	L.length = 0;
	return OK;
}
//�������Ա�ĳ���
int GetLength(struct SqList L)
{
	return L.length;
}
Status List_voluation(struct SqList& L, ElemType e)
{
	L.elem[L.length] = e;
	L.length++;			//��+1
	return OK;
}
void MergeList_sq(SqList LA, SqList LB, SqList& LC)
{
	ElemType* pa = LA.elem;
	ElemType* pb = LB.elem;
	LC.length = LA.length + LB.length;
	LC.elem = (ElemType*)malloc(sizeof(ElemType) * LC.length);
	ElemType* pc = LC.elem;
	ElemType* pa_last = LA.elem + LA.length - 1;
	ElemType* pb_last = LB.elem + LB.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}

}



int main(void)
{
	int n;		//�洢�û������ֵ
	int i;
	SqList LA;  //�ϲ���1
	SqList LB;	//�ϲ���2
	InitList_Sq(LA);
	InitList_Sq(LB);
	printf("����˳���LA��ֵ��");
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &n);
		List_voluation(LA, n);
	}
	printf("\n");
	printf("����˳���LB��ֵ��");
	for (i = 0; i < 3; i++)
	{
		scanf("%d", &n);
		List_voluation(LB, n);
	}
	printf("\n");
	SqList LC; //�ϲ��ռ�
	MergeList_sq(LA, LB, LC);
	int j;
	for (j = 0; j < LC.length; j++)
	{
		printf("%d ", LC.elem[j]);
	}
	printf("\n");
	return 0;
}