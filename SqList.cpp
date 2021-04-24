#include<stdio.h>
#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define TURE 1
#define FALSE 0
typedef int Status; //ͨ����Ϊ��������ֵ

//���������ֽṹ������
typedef struct {
	char no[20];
	char name[40];
	double price;
}Book;  //Bookֻ�Ǳ�������, ��int char��Щһ��, ���Ǳ�����

typedef Book ElemType; //��Book���ֽṹ������������Ϊ ElemType
ElemType error;
ElemType ok;	//��������Elemtype���͵ı���, ���ں���ķ���

typedef struct {
	ElemType* elem;
	int currentLength; //˳���ǰ����
}SqList;

SqList L; //����һ���ṹ��������Ա�L

Status InitSqList(SqList& L); //��ʼ��˳���

Status SqListInsert(SqList& L, int i, ElemType e); //�ڵ� i ��λ�ò���Ԫ��

Status SqListDelete(SqList& L, int i); //ɾ����i��λ�õ�Ԫ��

void TravelSqList(SqList& L);//����˳������

bool IsBookEqual(Book a, Book b);//�ж��ǲ���ͬһ����, ���Ψһ, ֻ�ñȽ����

Status  DestorySqList(SqList& L); //����˳���

int GetLength(SqList L); //��һ��˳���ĳ���

Status IsEmpty(SqList L); //�ж�һ�����Ա��Ƿ�Ϊ��

int LocateElem(SqList L, ElemType e);//˳���Ĳ���(��ֵ����, �ҵ��󷵻�λ��)

void ReverseSqList(SqList& L); //��ת˳���

void SelectSort(SqList& L);//���۸�����

void InsertOrderSqList(SqList& L, ElemType e); //�������

void MergeOrderSqList1(SqList& L1, SqList& L2); //�ϲ����������, �� L2�ϲ���L1

void MergeOrderSqList2(SqList& L1, SqList& L2, SqList& L3); //�������L1 L2�ϲ�, �ŵ�L3

void RemoveSameElem(SqList& L); //����˳���������ظ���Ԫ��

int main()
{
	SqList L1, L2, L3;

	Book book1, book2, book3, book4, book5, book6, book7, book8, book9;
	book1 = { "930421", "ʥ��\t\t\t", 69.9 };
	book2 = { "930422", "ȫ��ͨʷ\t\t", 79.7 };
	book3 = { "930123", "����\t\t\t", 48 };
	book4 = { "930424", "�ж�ŵ�����ı���\t", 35 };
	book5 = { "930454","пƤ���ޱ�\t\t", 29.8 };
	book6 = { "930478", "һ�ٸ��˵�ʮ��\t\t", 27.5 };
	book7 = { "930136", "����ʱ�ڵİ���\t\t", 19.8 };
	book8 = { "930139", "���κ�\t\t\t", 25 };
	book9 = { "930201", "��������\t\t",23 };

	//��ʼ��
	InitSqList(L1);
	InitSqList(L2);

	//����
	SqListInsert(L1, 1, book1);
	SqListInsert(L1, 1, book2);
	SqListInsert(L1, 1, book3);
	SqListInsert(L1, 1, book4);
	SqListInsert(L2, 3, book5);
	SqListInsert(L2, 2, book6);
	SqListInsert(L2, 2, book7);
	SqListInsert(L2, 2, book8);

	//����
	SelectSort(L1);
	SelectSort(L2);

	//���������
	TravelSqList(L1);
	TravelSqList(L2);

	//�ϲ�
	MergeOrderSqList2(L1, L2, L3);

	//����L3���ظ���Ԫ��
	RemoveSameElem(L3);
	cout << "L3" << endl;
	TravelSqList(L3);
	cout << "L3.currentLength = " << endl;

	//����
	SqListInsert(L3, 8, book9);
	TravelSqList(L3);

	//ɾ���ھű���(���һ��)
	SqListDelete(L3, 9);
	TravelSqList(L3);

	//����
	cout << "book9��λ��: " << LocateElem(L3, book9) << endl;

}

//����˳������
void TravelSqList(SqList& L)
{
	cout << "==================" << endl; //���������ʽ

	printf("���\t����\t\t\t�۸�\n");
	for (int i = 0; i < L.currentLength; i++)
	{
		
		printf("%s\t%s%.2f", L.elem[i].no, L.elem[i].name, L.elem[i].price);
		printf("\n");
	}
	
	cout << endl; //���������ʽ
}

//�ж��ǲ���ͬһ����, ���Ψһ, ֻ�ñȽ����
bool IsBookEqual(Book a, Book b)
{
	if (strcmp(a.no, b.no) == 0)
	{
		return TURE; //��ȷ���1
	}
	return FALSE;
}
	

//��ʼ��˳���
Status InitSqList(SqList& L) 
{
	//new ������ [��ֵ], newʧ�ܻ᷵��NULL;
	//�ڶ��￪��һ����СΪ sizeof(ElemType)* 100 �Ŀռ�
	L.elem = new ElemType[100];
	if (L.elem == NULL)
	{
		return ERROR; //����ʧ��
	}
	L.currentLength = 0;
	return OK;
}

//�ڵ� i ��λ�ò���Ԫ��e
Status SqListInsert(SqList& L, int i, ElemType e)
{
	if (L.currentLength == 0) //���������һ��Ԫ��Ҳû��, �����쳣����λ�õ��ж�
	{
		L.elem[0] = e;
		L.currentLength++;
		return OK;
	}
	if (i < 1 || i > L.currentLength + 1 )
	{
		return ERROR;
	}
	
	for (int j = L.currentLength; j >= i; j--) //����һ��Ҫȡ�Ⱥ�
		{
			L.elem[j] = L.elem[j - 1];
		}
		L.elem[i - 1] = e;
		L.currentLength++;
		return OK;
	
}

//ɾ���� i ��λ�õ�Ԫ��
Status SqListDelete(SqList& L, int i) 
{
	if (i < 0 || i > L.currentLength || L.currentLength == 0) //�쳣�ж�
	{
		return ERROR;
	}
	for (int j = i - 1; j < L.currentLength; j++)
	{
		L.elem[j] = L.elem[j + 1];
	}
	L.currentLength--;
	return OK;
}

//����˳���
Status  DestorySqList(SqList& L)
{
	if (L.elem != NULL)//���Ա����
	{
		delete(L.elem); //�ͷ�˳�����ڴ�
		return OK;
	}
	return ERROR;
}

//��һ��˳���ĳ���
int GetLength(SqList L)
{
	return L.currentLength;
}

//�ж�һ�����Ա��Ƿ�Ϊ��
Status IsEmpty(SqList L)
{
	if (L.currentLength == 0)
	{
		return TURE;
	}
	else
	{
		return FALSE;
	}
}

//˳���Ĳ���(��ֵ����, �ҵ��󷵻�λ��)
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.currentLength; i++)
	{
		if (IsBookEqual(L.elem[i], e)) //��������ж��Ƿ���ͬ
		{
			return i + 1;
		}
	}
		return ERROR;
}

//��ת˳���
void ReverseSqList(SqList& L)
{
	for (int i = 0, j = L.currentLength - 1; i <= L.currentLength / 2; i++, j--)
	{
		ElemType temp = L.elem[i];
		L.elem[i] = L.elem[j];
		L.elem[j] = temp;
	}
}

//���ݼ۸�, ��˳���ӵ͵�������
void SelectSort(SqList& L)
{
	for (int i = 0; i < L.currentLength - 1; i++)
	{
		//����ÿ��ѭ���ĵ�һ���ṹ����С,����¼�±�
		double currentMin = L.elem[i].price;
		int min_index = i;
		for (int j = i + 1; j < L.currentLength; j++)
		{
			if (currentMin > L.elem[j].price)
			{
				currentMin = L.elem[j].price;
				min_index = j;
			}
		}
		if (currentMin != L.elem[i].price)
		{
			ElemType temp = L.elem[i];
			L.elem[i] = L.elem[min_index];
			L.elem[min_index] = temp;
		}
	}
}

//����������Ա��в���һ��Ԫ��, ������ԭ����˳��
void InsertOrderSqList(SqList& L, ElemType e)
{
	//�����һ�����ݿ�ʼ�Ƚ�, �ȵ��±�Ϊ0Ԫ��Ϊֹ
	for (int i = L.currentLength - 1; i >= 0; i--)
	{
		//���Ҫ�����Ԫ�ر���ǰ��Ĵ�, ֱ�Ӿͷ������һλ, ����1
		if (e.price >= L.elem[i].price)
		{
			L.elem[i + 1] = e;
			break;
		}
		//���e��ǰһ��С, ��e������ǰһ��Ԫ�ص�λ��, �������һ��Ԫ��������, ����1
		L.elem[i + 1] = L.elem[i];
		L.elem[i] = e;
	}
	L.currentLength++;
}

//��L2�ϲ���L1
void MergeOrderSqList1(SqList& L1, SqList& L2)
{
	//��L2 ���뵽 L1��, ��L2�еĵ� 1 ��Ԫ�ذ�˳����뵽 L1��
	//InsertOrderSqList(L1, L2.elem[0]);
	//InsertOrderSqList(L1, L2.elem[1]);
	//InsertOrderSqList(L1, L2.elem[2]);
	//InsertOrderSqList(L1, L2.elem[3]);

	//д��һ��ѭ��
	for (int i = 0; i < L2.currentLength ; i++)
	{
		InsertOrderSqList(L1, L2.elem[i]);
	}
}

//�������L1 L2�ϲ�, �ŵ�L3
void MergeOrderSqList2(SqList& L1, SqList& L2, SqList& L3)
{
	/*��ʼ��L3*/
	InitSqList(L3);

	int i, j, k;
	i = 0; j = 0; k = 0;
	//L1.elem[i] < L2.elem[j]?
	//	��, L3.elem[k] = L1.elem[i]; i++; k++;
	//	��, L3.elem[k] = L2.elem[j]; j++; k++;
	while (i < L1.currentLength && j < L2.currentLength)
	{	
		if (L1.elem[i].price < L2.elem[j].price)
		{
			L3.elem[k] = L1.elem[i];
			i++;
			k++;
		}
		else
		{
			L3.elem[k] = L2.elem[j];
			j++; 
			k++;
		}
		L3.currentLength++;
	}

	// i < L1.currentLength? �� ˵�� L1����ʣ�µ�, ʣ�µķŵ�L3��
	while (i < L1.currentLength)
	{
		L3.elem[k] = L1.elem[i];
		i++;
		k++;
		L3.currentLength++;
	}

	// j < L2.currentLength? �� ˵�� L2����ʣ�µ�, ʣ�µķŵ�L3��
	while (j < L2.currentLength)
	{
		L3.elem[k] = L2.elem[j];
		j++;
		k++;
		L3.currentLength++;
	}

}

//����˳�������ͬ����
void RemoveSameElem(SqList& L)
{
	//��ָ��һֱ����
	int left = 0;
	for ( int right = 1; right < L.currentLength; right++)
	{
		int equal = IsBookEqual(L.elem[left], L.elem[right]);
		if (equal == 0)//��������鲻���
		{
			left++; //��ָ������
			L.elem[left] = L.elem[right]; //����ָ�뵱ǰ��ֵ������ָ��
		}
		//������, ��ָ�벻��
	}
	L.currentLength = left + 1; //��ָ���ƶ�һ��, ��+1
}
