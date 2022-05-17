#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int ElemType;
//������
typedef struct BiTree {
	ElemType data;
	struct BiTree* lchild;
	struct BiTree* rchild;
}BiTree, * P_BiTree;
//���帨������
typedef struct Queue {
	P_BiTree tree;  //ʹ��ָ��ģʽ����ֱ�Ӹ��ݶ���������޸�����
	struct Queue* P_next;  //���м�¼���˳���Ա��ж�������������
}Queue, *P_Queue;
//��������������


//������α�����ʽ���У����У����ݣ���һ��ָ�ţ���ͷ��㣬β���


void BuildTree(P_BiTree* RootTree, P_Queue* Head, P_Queue* Tail, ElemType T)
{
	//�Զ������Ͷ��г�ʼ��
	BiTree* NewTree = (BiTree*)malloc(sizeof(BiTree));  //�¶�������¼�µ�����
	NewTree->lchild = NULL;
	NewTree->rchild = NULL;	
	P_Queue NewQueue = (P_Queue)malloc(sizeof(Queue));
	P_Queue QueueLin = *Head;
	//������ʱ���У�������
	NewTree->data = T;
	NewQueue->tree = NewTree;
	if (NULL == *RootTree) {
		*RootTree = NewTree;
		*Head = NewQueue;
		*Tail = NewQueue;
	}
	else {
		(*Tail)->P_next = NewQueue;
		*Tail = NewQueue;//βָ��ָ�������¶���
		if (NULL == QueueLin->tree->lchild) {
			QueueLin->tree->lchild = NewTree;
		}
		else {
			QueueLin->tree->rchild = NewTree;
			//Ȼ���������ǰ
			*Head = QueueLin->P_next;
			//ɾ����ʱ���У����ͷſռ�
			free(QueueLin);
			QueueLin = NULL;
		}
	}
}
//����������
void visit(P_BiTree RootTree) 
{
	printf("%d", RootTree->data);//ֱ�����������ֵ
}



//�������
void PreOrder(P_BiTree RootTree) {
	
	if (RootTree != NULL) {
		visit(RootTree);
		PreOrder(RootTree->lchild);
		PreOrder(RootTree->rchild);
	}

}
//�������
void InOrder(P_BiTree RootTree) {
	
	if (RootTree != NULL) {
		InOrder(RootTree->lchild);
		visit(RootTree);
		InOrder(RootTree->rchild);
	}

}
//�������
void PostOrder(P_BiTree RootTree) {
	
	if (RootTree != NULL) {
		PostOrder(RootTree->lchild);
		visit(RootTree);
		PostOrder(RootTree->rchild);
	}
	
}
//��α���
void LevelOrder(P_BiTree RootTree) {
	//ʹ�ö��и���
	if (RootTree != NULL) {
		                          
	}
}




//������
int main() {
	//������ڵ�
	P_BiTree RootTree = NULL;
	//����ͷ����
	//��¼���е�ͷָ�룬βָ�룬ͷָ����������������ָ��
	//βָ����������к��������
	P_Queue Head = NULL;
	//����β����
	P_Queue Tail = NULL;
	//��������ֵ
	ElemType T[10] = { 1,2,3,4,5,6,7,8 };
	/*ElemType T;
	while (scanf("%d", &T) != EOF)
	{
		if (T=='\n') {
			break;
		}
		BuildTree(&RootTree, &Head, &Tail, T);
	}*/
	for (int i = 0; T[i]; i++) {
		if (T[i] == 0) {
			break;
		}
		BuildTree(&RootTree, &Head, &Tail, T[i]);
	}


	//�������
	printf("\n�������");
	PreOrder(RootTree);
	//�������
	printf("\n�������");
	InOrder(RootTree);
	//�������
	printf("\n�������");
	PostOrder(RootTree);
	//��α���
	LevelOrder(RootTree); 



	return 0;
}