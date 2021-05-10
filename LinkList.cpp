#include<iostream>
#include<stdio.h>
using namespace std;

//定义一个节点
struct Node
{
	int data;
	//struct Node* next;	//C语言的写法
	Node* next; //next用来储存链表中下一个结点的地址
};
//创建链表前, 先创建一个指向Node的指针变量
//struct Node* head;	//C语言的写法
Node* head;

void Insert(int x);	//头插
void Print(); //遍历打印当前链表元素
int main()
{
	//一开始链表是空的
	head = NULL;
	cout << "How many numbers?" << endl;
	int n = 0;
	cin >> n;

	//输入一个数, 打印一次当前的链表
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
	//mallo函数返回的是一个空指针, 所以需要用强制类型转换, 换成需要的指针类型
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
	//用一个临时的指针, 存放头指针的指向的地址
	Node* temp = head;
	cout << "List is : ";
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}