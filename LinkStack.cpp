//  Stack - Linked List implementation
#include<stdio.h>
#include<iostream>
using namespace std;
struct Node {  //������
	int data;
	Node* link;
};
Node* top = NULL;  //  ͷָ����Ϊȫ�ֱ���, ��ʼָ���
void Push(int x);   // ��ջ
void Pop();  // ��ջ
int Top();  // ��ȡջ��Ԫ��
void Print_1();  //�����ӡ
void Print_2(Node* temp);  // �ݹ��ӡ
void Reverse(char c[], int n);  // ��ת�ַ���
bool IsBalance(char c[], int n);  // ��������ƥ��
bool IsBalance_2(char opening, char closing);  // ĳһ�������Ƿ�ƥ��




int main()
{
	//char c[51];  
	//printf("Enter a string: ");
	//gets_s(c);  // ��������ַ����浽�ַ�����c
	//Reverse(c, strlen(c));
	//printf("Output = %s", c);

	char C[51];
	printf("�������: ");
	gets_s(C);
	if (IsBalance(C, strlen(C)))
	{
		printf("����ƥ��\n");
	}
	else printf("���Ų�ƥ��\n");
}

void Push(int x)  //��ջ
{
	// �������
	Node* temp = new Node;
	temp->data = x;
	temp->link = top;
	top = temp;
}
void Pop()  // ��ջ, Ҫ����һ��ָ��
{
	if (top == NULL)  // ����Ϊ��, ֱ�ӷ���
	{
		printf("Error: Stack is empty.");
		return;
	}
	Node* temp = top;
	top = top->link;
	delete temp;  // �ͷ��ڴ�
}
int Top()  // ��ȡջ��Ԫ��
{
	if (top == NULL)  // ����Ϊ��, ֱ�ӷ���
	{
		printf("Error: Stack is empty.");
		return 0;
	}
	return top->data;
}
void Print_1()  // ��ӡջ�е�Ԫ��
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
void Print_2(Node* temp)  // �ݹ��ӡջ�е�Ԫ�� 
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
	//  �������ÿ��Ԫ����ջ
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
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')  // ���Ϊ���ŷ���, ֱ����ջ
		{
			Push(exp[i]);
			continue;
		}
		else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')  // ���Ϊ�رշ���
		{
			if (top == NULL)  // �ж�ջ�Ƿ�Ϊ��
			{
				return false;  // Ϊ��ֱ�ӷ��ز�ƥ��
			}
			else if (!IsBalance_2(Top(), exp[i]))  return false;
			else
			{
				Pop();  // ��Ϊ�ջ��߷���ƥ��ͽ�ջ��Ԫ�س�ջ
			}
		}
	}
	if (top == NULL)  // ����ж�ջ�Ƿ�Ϊ��
		return true;  // ջ��˵��ƥ��  
	else 
		return false;  //����˵����ƥ��
}
bool IsBalance_2(char opening, char closing)  // �ж�ĳ�Է����Ƿ����
{
	if (opening == '(' && closing == ')')  return true;
	else if (opening == '[' && closing == ']')  return true;
	else if (opening == '{' && closing == '}')  return true;
	return false;
}