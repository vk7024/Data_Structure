#include<iostream>
#include<stdio.h>
using namespace std;

//定义一个节点
struct Node {
	int data;
	struct Node* next;
};

//定义头指针
Node* head;

void Insert(int data, int position);	//声明插入函数, 给出要插入的数据和要插入的位置
void Print();	//遍历打印链表

int main()
{
	head = NULL;//头指针最初为空
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
	//建立新节点
	Node* temp1 = new Node;
	temp1->data = data;
	temp1->next = NULL;
	
	//考虑链表为空的情况
	if (head == NULL)
	{
		head = temp1;
		return;
	}

	//遍历链表, 找到要插入位置的前一个结点
	Node* temp2 = head;

	for (int i = 0; i < position - 2; i++)
	{	//没有头结点, 直接从首元结点遍历, 所以是position - 2
		//如果从头结点开始, 则position - 1
		temp2 = temp2->next;
	}
	temp1->next = temp2->next;	//将新节点指向插入位置的结点
	temp2->next = temp1;	//将插入位置前的结点指向新节点
}

void Print()
{
	//用指向首元结点的临时指针temp来遍历链表
	Node* temp = head;
	cout << "List: ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}