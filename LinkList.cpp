#include<iostream>
#include<stdio.h>
using namespace std;

//����һ���ڵ�
struct Node
{
	int data;
	//struct Node* next;	//C���Ե�д��
	Node* next; //next����������������һ�����ĵ�ַ
};
//��������ǰ, �ȴ���һ��ָ��Node��ָ�����
//struct Node* head;	//C���Ե�д��
Node* head;

void Insert(int x);	//ͷ��
void Print(); //������ӡ��ǰ����Ԫ��
int main()
{
	//һ��ʼ�����ǿյ�
	head = NULL;
	cout << "How many numbers?" << endl;
	int n = 0;
	cin >> n;

	//����һ����, ��ӡһ�ε�ǰ������
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the number" << endl;
		int x = 0;
		cin >>x;
		Insert(x);
		Print();
	}
}

void Insert(int x)
{
	//mallo�������ص���һ����ָ��, ������Ҫ��ǿ������ת��, ������Ҫ��ָ������
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));	
	//(*temp).data = x;
	//(*temp).next = NULL;
	temp->data = x;
	temp->next = head;
	head = temp;

}

void Print()
{
	//��һ����ʱ��ָ��, ���ͷָ���ָ��ĵ�ַ
	Node* temp = head;
	cout << "List is : ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}