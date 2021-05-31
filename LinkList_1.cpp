/*
	 ������ʵ��һ:
	 ͷָ����Ϊ �ֲ�����
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//������
struct Node {
	int data;	//���������
	Node* next;	//���ָ����
};

//typedef struct Node *LinkList, Node;

//����һ��ͷָ��
Node* head;

void Print_1();	//	��ӡ������
void Print_2(Node* temp);	//	˳���ӡ������_�ݹ�
void Print_3(Node* temp);	//	�����ӡ������_�ݹ�

void Insert_head(int data);	//	ͷ��
void Insert_tail(int data); //	β��
void Insert_any(int data, int pos); //	����λ�ò���

void Delete_pos(int pos);	//	ɾ��λ��pos��Ԫ��
void Delete_value(int value); //	ɾ����һ��ֵΪvalue�Ľ�� (���Ľ� -> ɾ������ֵΪvalue�Ľ��)

void Reverse_1();	//	��ת������_����
void Reverse_2(Node* head);	// ��ת������_�ݹ�

int main()
{
	head = NULL;	// 	ͷָ���ÿ�
	Insert_tail(1);
	Insert_tail(2);
	Insert_tail(3);
	Insert_tail(4);
	Insert_tail(5);	

	Print_2(head);	// List : 1 2 3 4 5
	printf("\n");

	Reverse_2(head);
	Print_1();	// List : 5 4 3 2 1

	return 0;
}

void Print_1()	
{
	//����һ����ʱָ��, ָ���һ��Ԫ��
	Node* temp = head;
	int cnt = 0;
	cout << "List is: ";
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
		cnt++;
	}
	cout << endl;
	cout << "��������" << cnt << "�����";
	cout << endl;
}

void Print_2(Node* p)	// �ݹ��ӡ ��ȥʱ��ӡ ˳���ӡ
{
	if (p == NULL)	// exit condition �ݹ���ֹ����
	{
		return;
	}
	printf("%d ", p->data);
	Print_2(p->next);
}

void Print_3(Node* p)	//  �ݹ��ӡ ����ʱ��ӡ
{
	/*
	* �ݹ���ֹ����: 
	*1.  ����Ϊ��ֱ�ӷ��� ��
	*2.  ���������βʱ����, ����ǰ����õݹ麯��ʱ�����˺ܶ�ջ֡, 
	*	  ����ÿ�η��غ󶼻ᵽ���ϴκ������õ���һ����俪ʼִ��
	*/
	if (p == NULL)	
	{
		return;		// returnÿ�λ᷵�ص����õݹ麯������һ�����
	}
	Print_3(p->next); //	������ӡ��һ��, �����ݹ�ʱ�����뵽
	printf("%d ", p->data);	// ����ʱ��ӡ, ���Ի������ӡ
}



void Insert_head(int data)//ͷ��
{
	//����һ�����
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	if (head == NULL)
	{//���ֻ��һ�����, ֱ�Ӳ��ں���
		head = temp;
		return;
	}
	temp->next = head;
	head = temp;
}

void  Insert_tail(int data)
{
	//����һ�����
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	Node* temp2 = head;
	if (head == NULL)
	{
		head = temp;
	}
	//���head != NULL ����һ��ָ��������������һ�����
	else
	{
		while (temp2->next != NULL) {
			temp2 = temp2->next;
		}
		temp2->next = temp;
	}
}

void Insert_any(int data, int pos)
{
	//����һ�����
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	//�����ڵ�һ��λ��
	if (pos == 1)
	{//�����Ƿ�Ϊ�ն��������������
		temp->next = head;
		head = temp;
		return;
	}

	//����������λ��
	Node* temp2 = head;
	for (int i = 0; i < pos - 2; i++)
	{ //�ر�ע������Ҫ������Ϊʲôpos-2
		temp2 = temp2->next; //tempָ��Ҫ����λ�õ�ǰһ��λ��
	}
	temp->next = temp2->next;
	temp2->next = temp;
}

void Delete_pos(int pos)
{
	//��������ָ��
	Node* temp1 = head;

	//	ֻ��һ�����
	if (pos == 1)
	{
		head = temp1->next;
		delete(temp1);
		return;
	}

	//	temp1 ָ��Ҫɾ����ǰһ�����
	for (int i = 0; i < pos - 2; i++)
	{
		temp1 = temp1->next;
	}
	//	temp2 ָ��Ҫɾ���Ľ��
	Node* temp2 = temp1->next;	//	��n�����
	temp1->next = temp2->next;	//	��(n + 1) �����
	delete temp2;	//	C free(temp2)

}

void Delete_value(int value)
{
	Node* temp1 = head;

	//����ڵ�һ�����
	if (temp1->data == value)
	{
		head = temp1->next;
		delete(temp1);
		return;
	}
}

void  Reverse_1()	  // �õ�����ת
{
	Node* current, * prev, * next;	//	��������ָ��, �ֱ�ָ��ǰ���, ǰһ���ڵ�, ��һ�����
	current = head;
	prev = NULL;	//	��ʼʱǰһ�����ָ���
	while (current != NULL)
	{
		next = current->next;	//	1. �Ƚ���ǰ�ڵ��ָ���򱣴�
		current->next = prev;	//	2. �õ�ǰ����ָ����ָ��ǰһ�����
		prev = current;	//	3.	ǰһ�����������
		current = next;		//	4. ��ǰ���ָ����һ�����
	}
	//	ѭ������ʱ, current next ��ָ���, prevָ�����һ�����
	head = prev;	//	�����һ������Ϊͷ���

	//Node* cur, * prev, * next;
	//prev = NULL;
	//cur = head;
	//next = cur->next;
	//while (cur != NULL)
	//{
	//	/*
	//	  ��δ�����һ������, ��cur == NULLʱ
	//	  next �Ѿ�ΪNULL, ��ִ��next = next->next ʱ�������?
	//	*/
	//	cur->next = prev;
	//	prev = cur;
	//	cur = next;
	//	next = next->next; 
	//}
	//head = prev;
	return;
}

void Reverse_2(Node*p)	// �ݹ鷴ת
{	// ��ȫ�ֱ���haed��Ϊ��������, �� p = head;
	if (p->next == NULL)
	{//�������һ�����ʱ, �޸�head, ʹ��ָ�����һ�����
		head = p;
		return;
	}
	Reverse_2(p->next);
	// ����ʱ����ʱִ����������
	//	�Ե�һ�ι���Ϊ��, �������һ�εݹ麯�����ý���, ��ʱp�б���ĵ����ڶ������ĵ�ַ
	Node* q = p->next;		// �½�һ��ָ��, ����ָ�����һ�����
	q->next = p;	// �и���, ʹ�� (���һ�����) ָ��ǰһ����� (�����ڶ������)
	p->next = NULL;	// Ȼ����ǰһ����� (�����ڶ������) ָ��NULL
}




