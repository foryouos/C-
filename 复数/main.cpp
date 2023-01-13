#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//�����ṹ��
typedef struct Complex
{
	float realpart;  //ʵ��
	float imagpart;  //�鲿
};
//����ṹ��
void Print_Comples(struct Complex z)
{
	//���ʵ��Ϊ��
	//���������ʽ���鲿Ϊ����Ϊ��
	if (z.realpart - 0.00000001 < 0.00000001&& z.realpart - 0.00000001 > 0.00000001)//��ʵ��Ϊ��
	{
		printf("����ĸ���Ϊ��%.1fi\n",z.imagpart);
	}
	else //ʵ����Ϊ��
	{
		if (z.imagpart > 0)
		{
			printf("����ĸ���Ϊ��%.1f+%.1fi\n", z.realpart, z.imagpart);//�������ĸ���
		}
		else
		{
			printf("����ĸ���Ϊ��%.1f%.1fi\n", z.realpart, z.imagpart);//�������ĸ���
		}
	}
}
bool Check_Complex(struct Complex z)//�������ĸ����Ƿ�Ϲ�
{
	if (z.imagpart - 0.00000001 < 0.0000001)
	{
		system("title error!!");
		system("color 4");
		printf("�������鲿����Ϊ��\n");
		return true; //�����Ϲ棬������
	}
	else
	{
		printf("��������ϣ����ϣ�\n");
		return false;
	}
}
void Entry_Complex(struct Complex* z) //ʹ��ָ�룬Ҫ�ı�ֵ
{
	printf("�����븴����ʵ�����鲿\n��\"a+bi\"����ʽ:");
	scanf("%f %fi", &z->realpart, &z->imagpart);
	//������
	if (Check_Complex(*z))
	{
		abort();
	}
}
//�����ļӷ�
//Ŀ��ṹ�壬��ӵ������ṹ��
void add(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart + z2.realpart;
	z->imagpart = z2.imagpart + z2.imagpart;
	printf("\n**********�������*********\t");
	Print_Comples(*z);

}
//�������
void minus(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart - z2.realpart;
	z->imagpart = z1.imagpart - z2.imagpart;
	printf("\n**********�������*********\t");
	Print_Comples(*z);

}
//�������
void multiply(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart*z2.realpart - z1.imagpart*z2.imagpart;
	z->imagpart = z1.imagpart*z2.realpart + z1.realpart*z2.imagpart;
	printf("\n**********�������*********\t");
	Print_Comples(*z);

}
//�������
void divide(struct Complex* z, struct Complex z1, struct Complex z2)
{
	float cd = z2.realpart * z2.realpart + z2.imagpart * z2.imagpart;
	z->realpart = (z1.realpart * z2.realpart + z1.imagpart * z2.imagpart)/cd;
	z->imagpart = (z1.imagpart * z1.realpart - z1.realpart * z2.imagpart)/cd;
	printf("\n**********�������*********\t");
	Print_Comples(*z);

}
int main(void)
{
	//����ʵ�����������ļ򵥲���
	Complex z, z1, z2;
	Entry_Complex(&z1);
	Entry_Complex(&z2);
	//���
	Print_Comples(z1);
	Print_Comples(z2);

	//���������
	add(&z, z1, z2);
	//�����ļ���
	minus(&z, z1, z2);
	//�����ĳ˷�
	multiply(&z, z1, z2);
	//�����ĳ���
	divide(&z, z1, z2);

	return 0;
}
