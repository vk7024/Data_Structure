//  Stack - Linked List implementation
#include<stdio.h>
#include<iostream>
using namespace std;
struct Node {  //定义结点
	int data;
	Node* link;
};
Node* top = NULL;  //  头指针作为全局变量, 初始指向空
void Push(int x);   // 入栈
void Pop();  // 出栈
int Top();  // 获取栈顶元素
void Print_1();  //常规打印
void Print_2(Node* temp);  // 递归打印
void Reverse(char c[], int n);  // 反转字符串
bool IsBalance(char c[], int n);  // 所有括号匹配
bool IsBalance_2(char opening, char closing);  // 某一对括号是否匹配




int main()
{
	//char c[51];  
	//printf("Enter a string: ");
	//gets_s(c);  // 将输入的字符串存到字符数组c
	//Reverse(c, strlen(c));
	//printf("Output = %s", c);

	char C[51];
	printf("输入符号: ");
	gets_s(C);
	if (IsBalance(C, strlen(C)))
	{
		printf("符号匹配\n");
	}
	else printf("符号不匹配\n");
}

void Push(int x)  //入栈
{
	// 创建结点
	Node* temp = new Node;
	temp->data = x;
	temp->link = top;
	top = temp;
}
void Pop()  // 出栈, 要借助一个指针
{
	if (top == NULL)  // 链表为空, 直接返回
	{
		printf("Error: Stack is empty.");
		return;
	}
	Node* temp = top;
	top = top->link;
	delete temp;  // 释放内存
}
int Top()  // 获取栈顶元素
{
	if (top == NULL)  // 链表为空, 直接返回
	{
		printf("Error: Stack is empty.");
		return 0;
	}
	return top->data;
}
void Print_1()  // 打印栈中的元素
{
	Node* temp = top;
	printf("Stack: ");
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->link;
	}
	printf("\n");
}
void Print_2(Node* temp)  // 递归打印栈中的元素 
{
	if (temp == NULL)
	{
		return;
	}
	printf("%d ", temp->data);
	Print_2(temp->link);
}
void Reverse(char c[], int n) 
{
	//  将数组的每个元素入栈
	for (int i = 0; i < n; i++)
	{
		Push(c[i]);
	}
	for (int i = 0; i < n; i++)
	{
		c[i] = Top();
		Pop();
	}
}
bool IsBalance(char exp[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')  // 如果为开放符号, 直接入栈
		{
			Push(exp[i]);
			continue;
		}
		else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')  // 如果为关闭符号
		{
			if (top == NULL)  // 判断栈是否为空
			{
				return false;  // 为空直接返回不匹配
			}
			else if (!IsBalance_2(Top(), exp[i]))  return false;
			else
			{
				Pop();  // 不为空或者符号匹配就将栈顶元素出栈
			}
		}
	}
	if (top == NULL)  // 最后判断栈是否为空
		return true;  // 栈空说明匹配  
	else 
		return false;  //否则说明不匹配
}
bool IsBalance_2(char opening, char closing)  // 判断某对符号是否相等
{
	if (opening == '(' && closing == ')')  return true;
	else if (opening == '[' && closing == ']')  return true;
	else if (opening == '{' && closing == '}')  return true;
	return false;
}