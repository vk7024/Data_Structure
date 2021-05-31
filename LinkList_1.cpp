/*
	 单链表实现一:
	 头指针作为 全局变量
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

//定义结点
struct Node {
	int data;	//结点数据域
	Node* next;	//结点指针域
};

//typedef struct Node *LinkList, Node;

//定义一个头指针
Node* head;

void Print_1();	//	打印单链表
void Print_2(Node* temp);	//	顺序打印单链表_递归
void Print_3(Node* temp);	//	逆序打印单链表_递归

void Insert_head(int data);	//	头插
void Insert_tail(int data); //	尾插
void Insert_any(int data, int pos); //	任意位置插入

void Delete_pos(int pos);	//	删除位置pos的元素
void Delete_value(int value); //	删除第一个值为value的结点 (待改进 -> 删除所有值为value的结点)

void Reverse_1();	//	反转单链表_迭代
void Reverse_2(Node* head);	// 反转单链表_递归

int main()
{
	head = NULL;	// 	头指针置空
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
	//建立一个临时指针, 指向第一个元素
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
	cout << "链表中有" << cnt << "个结点";
	cout << endl;
}

void Print_2(Node* p)	// 递归打印 递去时打印 顺序打印
{
	if (p == NULL)	// exit condition 递归终止条件
	{
		return;
	}
	printf("%d ", p->data);
	Print_2(p->next);
}

void Print_3(Node* p)	//  递归打印 归来时打印
{
	/*
	* 递归终止条件: 
	*1.  链表为空直接返回 或
	*2.  到达链表结尾时返回, 由于前面调用递归函数时开辟了很多栈帧, 
	*	  所以每次返回后都会到从上次函数调用的下一条语句开始执行
	*/
	if (p == NULL)	
	{
		return;	// return每次会返回到调用递归函数的下一条语句
	}
	Print_3(p->next); // 继续打印下一个, 不理解递归时很难想到
	printf("%d ", p->data);	// 归来时打印, 所以会逆序打印
}



void Insert_head(int data)//头插
{
	//创建一个结点
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	if (head == NULL)
	{//如果只有一个结点, 直接插在后面
		head = temp;
		return;
	}
	temp->next = head;
	head = temp;
}

void  Insert_tail(int data)
{
	//创建一个结点
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	Node* temp2 = head;
	if (head == NULL)
	{
		head = temp;
	}
	//如果head != NULL 用另一个指针遍历到链表最后一个结点
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
	//创建一个结点
	Node* temp = new Node;
	temp->data = data;
	temp->next = NULL;

	//插入在第一个位置
	if (pos == 1)
	{//链表是否为空都可以用这个方法
		temp->next = head;
		head = temp;
		return;
	}

	//插入在其他位置
	Node* temp2 = head;
	for (int i = 0; i < pos - 2; i++)
	{ //特别注意这里要遍历到为什么pos-2
		temp2 = temp2->next; //temp指向要插入位置的前一个位置
	}
	temp->next = temp2->next;
	temp2->next = temp;
}

void Delete_pos(int pos)
{
	//定义两个指针
	Node* temp1 = head;

	//	只有一个结点
	if (pos == 1)
	{
		head = temp1->next;
		delete(temp1);
		return;
	}

	// temp1 指向要删结点的前一个结点
	for (int i = 0; i < pos - 2; i++)
	{
		temp1 = temp1->next;
	}
	// temp2 指向要删除的结点
	Node* temp2 = temp1->next;	// 第n个结点
	temp1->next = temp2->next;	// 第(n + 1) 个结点
	delete temp2;	// C free(temp2)

}

void Delete_value(int value)
{
	Node* temp1 = head;

	//如果在第一个结点
	if (temp1->data == value)
	{
		head = temp1->next;
		delete(temp1);
		return;
	}
}

void  Reverse_1()	  // 用迭代反转
{
	Node* current, * prev, * next;	//	定义三个指针, 分别指向当前结点, 前一个节点, 下一个结点
	current = head;
	prev = NULL;	//	开始时前一个结点指向空
	while (current != NULL)
	{
		next = current->next;	//	1. 先将当前节点的指针域保存
		current->next = prev;	//	2. 让当前结点的指针域指向前一个结点
		prev = current;		//	3. 前一个结点往后移
		current = next;		//	4. 当前结点指向下一个结点
	}
	//	循环结束时, current next 都指向空, prev指向最后一个结点
	head = prev;	//	将最后一个结点改为头结点

	//Node* cur, * prev, * next;
	//prev = NULL;
	//cur = head;
	//next = cur->next;
	//while (cur != NULL)
	//{
	//	/*
	//	  这段代码有一个错误, 当cur == NULL时
	//	  next 已经为NULL, 再执行next = next->next 时会出问题?
	//	*/
	//	cur->next = prev;
	//	prev = cur;
	//	cur = next;
	//	next = next->next; 
	//}
	//head = prev;
	return;
}

void Reverse_2(Node*p)	// 递归反转
{	// 将全局变量haed作为参数传入, 即 p = head;
	if (p->next == NULL)
	{//到达最后一个结点时, 修改head, 使他指向最后一个结点
		head = p;
		return;
	}
	Reverse_2(p->next);
	// 归来时结束时执行下面的语句
	//	以第一次归来为例, 由于最后一次递归函数调用结束, 此时p中保存的倒数第二个结点的地址
	Node* q = p->next;		// 新建一个指针, 让它指向最后一个结点
	q->next = p;	// 切割结点, 使它 (最后一个结点) 指向前一个结点 (倒数第二个结点)
	p->next = NULL;	// 然后让前一个结点 (倒数第二个结点) 指向NULL
}




