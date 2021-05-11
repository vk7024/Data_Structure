#include<iostream>
#include<stdio.h>
using namespace std;

//����һ���ڵ�
struct Node {
	int data;
	struct Node* next;
};

//����ͷָ��
Node* head;

void Insert(int data, int position);	//�������뺯��, ����Ҫ��������ݺ�Ҫ�����λ��
void Print();	//������ӡ����

int main()
{
	head = NULL;//ͷָ�����Ϊ��
	Insert(2, 1); //List is: 2
	Print();
	Insert(5, 2); //List is: 2 5
	Print();
	Insert(1, 3); //List is: 2 5 1
	Print();
	Insert(7, 2); //List is: 2 7 5 1
	Print();
}

void  Insert(int data, int position)
{
	//�����½ڵ�
	Node* temp1 = new Node;
	temp1->data = data;
	temp1->next = NULL;
	
	//��������Ϊ�յ����
	if (head == NULL)
	{
		head = temp1;
		return;
	}

	//��������, �ҵ�Ҫ����λ�õ�ǰһ�����
	Node* temp2 = head;

	for (int i = 0; i < position - 2; i++)
	{	//û��ͷ���, ֱ�Ӵ���Ԫ������, ������position - 2
		//�����ͷ��㿪ʼ, ��position - 1
		temp2 = temp2->next;
	}
	temp1->next = temp2->next;	//���½ڵ�ָ�����λ�õĽ��
	temp2->next = temp1;	//������λ��ǰ�Ľ��ָ���½ڵ�
}

void Print()
{
	//��ָ����Ԫ������ʱָ��temp����������
	Node* temp = head;
	cout << "List: ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}