//  Stack - Array based implementation
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX_SIZE 101
int arr[MAX_SIZE];  // 定义一个数组做为全局变量
int top = -1;  // 栈顶指针为全局变量, top = -1 说明栈为空

void Push(int x) 	// 入栈
{
	if (top == MAX_SIZE - 1) // 入栈前判断栈是否满了	
	{
		printf("Error: Stack over flow\n");
		return;
	}
	//top++;
	//arr[top] = x;
	arr[++top] = x;  // 栈顶下标加1, 再把x放入栈顶
}

void Pop()  // 出栈
{
	if ( top == -1)// 出栈前判断栈是否为空
	{
		printf("Error: No element to pop\n");
		return;
	}
	top--;  // 栈顶元素减1, 不用将原栈顶的值重置, 后续的push操作会覆盖原来的值
}
int Top()  // 获取栈顶元素
{
	if (top == -1)// 出栈前判断栈是否为空
	{
		printf("Error: Stack is empty. \n");
		return -1;
	}
	return arr[top];
}
void Print()  // 打印栈中的元素
{
	printf("stack: ");
	for (int i = 0; i <= top; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void Reverse(char C[], int n)  // 逆转数组
{
	for (int i = 0; i < n; i++)  //  将数组的每个元素入栈
	{
		Push(C[i]);
	}
	for (int i = 0; i < n; i++)  // 将栈顶元素依次出栈
	{
		C[i] = Top();
		Pop();	
	}
}

int main()
{
	char C[51];
	printf("Enter a string: ");
	gets_s(C);
	
	Reverse(C, strlen(C));  // 传入字符串和字符串长度
	printf("Output: %s", C);
}