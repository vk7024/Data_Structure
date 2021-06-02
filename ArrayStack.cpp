//  Stack - Array based implementation
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX_SIZE 101
int arr[MAX_SIZE];  // ����һ��������Ϊȫ�ֱ���
int top = -1;  // ջ��ָ��Ϊȫ�ֱ���, top = -1 ˵��ջΪ��

void Push(int x) 	// ��ջ
{
	if (top == MAX_SIZE - 1) // ��ջǰ�ж�ջ�Ƿ�����	
	{
		printf("Error: Stack over flow\n");
		return;
	}
	//top++;
	//arr[top] = x;
	arr[++top] = x;  // ջ���±��1, �ٰ�x����ջ��
}

void Pop()  // ��ջ
{
	if ( top == -1)// ��ջǰ�ж�ջ�Ƿ�Ϊ��
	{
		printf("Error: No element to pop\n");
		return;
	}
	top--;  // ջ��Ԫ�ؼ�1, ���ý�ԭջ����ֵ����, ������push�����Ḳ��ԭ����ֵ
}
int Top()  // ��ȡջ��Ԫ��
{
	if (top == -1)// ��ջǰ�ж�ջ�Ƿ�Ϊ��
	{
		printf("Error: Stack is empty. \n");
		return -1;
	}
	return arr[top];
}
void Print()  // ��ӡջ�е�Ԫ��
{
	printf("stack: ");
	for (int i = 0; i <= top; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void Reverse(char C[], int n)  // ��ת����
{
	for (int i = 0; i < n; i++)  //  �������ÿ��Ԫ����ջ
	{
		Push(C[i]);
	}
	for (int i = 0; i < n; i++)  // ��ջ��Ԫ�����γ�ջ
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
	
	Reverse(C, strlen(C));  // �����ַ������ַ�������
	printf("Output: %s", C);
}