#include<stdio.h>
#include<iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define TURE 1
#define FALSE 0
typedef int Status; //通常作为函数返回值

//定义书这种结构体类型
typedef struct {
	char no[20];
	char name[40];
	double price;
}Book;  //Book只是变量类型, 和int char这些一样, 不是变量名

typedef Book ElemType; //把Book这种结构体类型重命名为 ElemType
ElemType error;
ElemType ok;	//定义两个Elemtype类型的变量, 用于后面的返回

typedef struct {
	ElemType* elem;
	int currentLength; //顺序表当前长度
}SqList;

SqList L; //定义一个结构体变量线性表L

Status InitSqList(SqList& L); //初始化顺序表

Status SqListInsert(SqList& L, int i, ElemType e); //在第 i 个位置插入元素

Status SqListDelete(SqList& L, int i); //删除第i个位置的元素

void TravelSqList(SqList& L);//遍历顺序表并输出

bool IsBookEqual(Book a, Book b);//判断是不是同一本书, 书号唯一, 只用比较书号

Status  DestorySqList(SqList& L); //销毁顺序表

int GetLength(SqList L); //求一个顺序表的长度

Status IsEmpty(SqList L); //判断一个线性表是否为空

int LocateElem(SqList L, ElemType e);//顺序表的查找(按值查找, 找到后返回位置)

void ReverseSqList(SqList& L); //反转顺序表

void SelectSort(SqList& L);//按价格排序

void InsertOrderSqList(SqList& L, ElemType e); //按序插入

void MergeOrderSqList1(SqList& L1, SqList& L2); //合并两个有序表, 将 L2合并到L1

void MergeOrderSqList2(SqList& L1, SqList& L2, SqList& L3); //把有序表L1 L2合并, 放到L3

void RemoveSameElem(SqList& L); //消除顺序数组中重复的元素

int main()
{
	SqList L1, L2, L3;

	Book book1, book2, book3, book4, book5, book6, book7, book8, book9;
	book1 = { "930421", "圣经\t\t\t", 69.9 };
	book2 = { "930422", "全球通史\t\t", 79.7 };
	book3 = { "930123", "华札\t\t\t", 48 };
	book4 = { "930424", "切尔诺贝利的悲鸣\t", 35 };
	book5 = { "930454","锌皮娃娃兵\t\t", 29.8 };
	book6 = { "930478", "一百个人的十年\t\t", 27.5 };
	book7 = { "930136", "霍乱时期的爱情\t\t", 19.8 };
	book8 = { "930139", "茵梦湖\t\t\t", 25 };
	book9 = { "930201", "人与永恒\t\t",23 };

	//初始化
	InitSqList(L1);
	InitSqList(L2);

	//插入
	SqListInsert(L1, 1, book1);
	SqListInsert(L1, 1, book2);
	SqListInsert(L1, 1, book3);
	SqListInsert(L1, 1, book4);
	SqListInsert(L2, 3, book5);
	SqListInsert(L2, 2, book6);
	SqListInsert(L2, 2, book7);
	SqListInsert(L2, 2, book8);

	//排序
	SelectSort(L1);
	SelectSort(L2);

	//遍历并输出
	TravelSqList(L1);
	TravelSqList(L2);

	//合并
	MergeOrderSqList2(L1, L2, L3);

	//消除L3中重复的元素
	RemoveSameElem(L3);
	cout << "L3" << endl;
	TravelSqList(L3);
	cout << "L3.currentLength = " << endl;

	//插入
	SqListInsert(L3, 8, book9);
	TravelSqList(L3);

	//删除第九本书(最后一本)
	SqListDelete(L3, 9);
	TravelSqList(L3);

	//查找
	cout << "book9的位置: " << LocateElem(L3, book9) << endl;

}

//遍历顺序表并输出
void TravelSqList(SqList& L)
{
	cout << "==================" << endl; //控制输出格式

	printf("书号\t书名\t\t\t价格\n");
	for (int i = 0; i < L.currentLength; i++)
	{
		
		printf("%s\t%s%.2f", L.elem[i].no, L.elem[i].name, L.elem[i].price);
		printf("\n");
	}
	
	cout << endl; //控制输出格式
}

//判断是不是同一本书, 书号唯一, 只用比较书号
bool IsBookEqual(Book a, Book b)
{
	if (strcmp(a.no, b.no) == 0)
	{
		return TURE; //相等返回1
	}
	return FALSE;
}
	

//初始化顺序表
Status InitSqList(SqList& L) 
{
	//new 类型名 [初值], new失败会返回NULL;
	//在堆里开辟一个大小为 sizeof(ElemType)* 100 的空间
	L.elem = new ElemType[100];
	if (L.elem == NULL)
	{
		return ERROR; //分配失败
	}
	L.currentLength = 0;
	return OK;
}

//在第 i 个位置插入元素e
Status SqListInsert(SqList& L, int i, ElemType e)
{
	if (L.currentLength == 0) //如果表里面一个元素也没有, 不做异常插入位置的判断
	{
		L.elem[0] = e;
		L.currentLength++;
		return OK;
	}
	if (i < 1 || i > L.currentLength + 1 )
	{
		return ERROR;
	}
	
	for (int j = L.currentLength; j >= i; j--) //这里一定要取等号
		{
			L.elem[j] = L.elem[j - 1];
		}
		L.elem[i - 1] = e;
		L.currentLength++;
		return OK;
	
}

//删除第 i 个位置的元素
Status SqListDelete(SqList& L, int i) 
{
	if (i < 0 || i > L.currentLength || L.currentLength == 0) //异常判断
	{
		return ERROR;
	}
	for (int j = i - 1; j < L.currentLength; j++)
	{
		L.elem[j] = L.elem[j + 1];
	}
	L.currentLength--;
	return OK;
}

//销毁顺序表
Status  DestorySqList(SqList& L)
{
	if (L.elem != NULL)//线性表存在
	{
		delete(L.elem); //释放顺序表的内存
		return OK;
	}
	return ERROR;
}

//求一个顺序表的长度
int GetLength(SqList L)
{
	return L.currentLength;
}

//判断一个线性表是否为空
Status IsEmpty(SqList L)
{
	if (L.currentLength == 0)
	{
		return TURE;
	}
	else
	{
		return FALSE;
	}
}

//顺序表的查找(按值查找, 找到后返回位置)
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.currentLength; i++)
	{
		if (IsBookEqual(L.elem[i], e)) //根据书号判断是否相同
		{
			return i + 1;
		}
	}
		return ERROR;
}

//反转顺序表
void ReverseSqList(SqList& L)
{
	for (int i = 0, j = L.currentLength - 1; i <= L.currentLength / 2; i++, j--)
	{
		ElemType temp = L.elem[i];
		L.elem[i] = L.elem[j];
		L.elem[j] = temp;
	}
}

//根据价格, 给顺序表从低到高排序
void SelectSort(SqList& L)
{
	for (int i = 0; i < L.currentLength - 1; i++)
	{
		//假设每轮循环的第一个结构体最小,并记录下标
		double currentMin = L.elem[i].price;
		int min_index = i;
		for (int j = i + 1; j < L.currentLength; j++)
		{
			if (currentMin > L.elem[j].price)
			{
				currentMin = L.elem[j].price;
				min_index = j;
			}
		}
		if (currentMin != L.elem[i].price)
		{
			ElemType temp = L.elem[i];
			L.elem[i] = L.elem[min_index];
			L.elem[min_index] = temp;
		}
	}
}

//向升序的线性表中插入一个元素, 并保持原来的顺序
void InsertOrderSqList(SqList& L, ElemType e)
{
	//从最后一个数据开始比较, 比到下标为0元素为止
	for (int i = L.currentLength - 1; i >= 0; i--)
	{
		//如果要插入的元素比它前面的大, 直接就放在最后一位, 表长加1
		if (e.price >= L.elem[i].price)
		{
			L.elem[i + 1] = e;
			break;
		}
		//如果e比前一个小, 把e放在它前一个元素的位置, 并把最后一个元素往后移, 表长加1
		L.elem[i + 1] = L.elem[i];
		L.elem[i] = e;
	}
	L.currentLength++;
}

//把L2合并到L1
void MergeOrderSqList1(SqList& L1, SqList& L2)
{
	//把L2 插入到 L1中, 将L2中的第 1 个元素按顺序插入到 L1中
	//InsertOrderSqList(L1, L2.elem[0]);
	//InsertOrderSqList(L1, L2.elem[1]);
	//InsertOrderSqList(L1, L2.elem[2]);
	//InsertOrderSqList(L1, L2.elem[3]);

	//写成一个循环
	for (int i = 0; i < L2.currentLength ; i++)
	{
		InsertOrderSqList(L1, L2.elem[i]);
	}
}

//把有序表L1 L2合并, 放到L3
void MergeOrderSqList2(SqList& L1, SqList& L2, SqList& L3)
{
	/*初始化L3*/
	InitSqList(L3);

	int i, j, k;
	i = 0; j = 0; k = 0;
	//L1.elem[i] < L2.elem[j]?
	//	是, L3.elem[k] = L1.elem[i]; i++; k++;
	//	否, L3.elem[k] = L2.elem[j]; j++; k++;
	while (i < L1.currentLength && j < L2.currentLength)
	{	
		if (L1.elem[i].price < L2.elem[j].price)
		{
			L3.elem[k] = L1.elem[i];
			i++;
			k++;
		}
		else
		{
			L3.elem[k] = L2.elem[j];
			j++; 
			k++;
		}
		L3.currentLength++;
	}

	// i < L1.currentLength? 是 说明 L1还有剩下的, 剩下的放到L3中
	while (i < L1.currentLength)
	{
		L3.elem[k] = L1.elem[i];
		i++;
		k++;
		L3.currentLength++;
	}

	// j < L2.currentLength? 是 说明 L2还有剩下的, 剩下的放到L3中
	while (j < L2.currentLength)
	{
		L3.elem[k] = L2.elem[j];
		j++;
		k++;
		L3.currentLength++;
	}

}

//消除顺序表中相同的项
void RemoveSameElem(SqList& L)
{
	//右指针一直往右
	int left = 0;
	for ( int right = 1; right < L.currentLength; right++)
	{
		int equal = IsBookEqual(L.elem[left], L.elem[right]);
		if (equal == 0)//如果两本书不相等
		{
			left++; //左指针右移
			L.elem[left] = L.elem[right]; //把右指针当前的值赋给左指针
		}
		//如果相等, 左指针不动
	}
	L.currentLength = left + 1; //左指针移动一次, 表长+1
}
