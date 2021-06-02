//  Stack - Array based implementation
#include<stdio.h>
#include<iostream>
using namespace std;
#define MAX_SIZE 5
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

int main()
{
	Push(5);  Print(); 
	Push(6);  Print();
	Push(8);  Print();
	Push(9);  Print();
	Push(10);  Print();
	Push(11);  Print();
	printf("Elem of top is %d\n", arr[top]);
	
	Pop();   Print();
	Pop();   Print();
	Pop();   Print();
	Pop();   Print();
	Pop();   Print();

	printf("top = %d\nElem of top is %d\n", Top(), arr[top]);

	
	


}