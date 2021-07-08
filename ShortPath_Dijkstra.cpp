/*
* 邻接矩阵存储
*/

#include<fstream>
#include<iostream>
using namespace std;
#define MaxV 101 // 结点最大值 
#define MAX_SIZE 101  // 栈最大容量 
#define INFINITY 65535 
typedef char VertexType;
struct MGraph // 图的结构体
{
	char vertex[MaxV];  // 结点表 
	int edge[MaxV][MaxV];  // 邻接矩阵 
	int v_num, e_num;  // 结点数 边数 
};
MGraph* Graph = new MGraph;



void InitMGraph()  // 初始化图 (将图中各点置零 或 INFINITY)
{
	for (int i = 0; i < Graph->v_num; i++)
	{
		for (int j = 0; j < Graph->v_num; j++)
			Graph->edge[i][j] = INFINITY;
	}
}

char GetVerx(int i)  // 根据下标找到对应的结点
{
	return Graph->vertex[i];
}

int GetIndex(char c)  // 根据结点找到对应的下标
{
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (c == Graph->vertex[i])
		{
			return i;
		}
	}
	cout << "错误: 没有结点" << c << endl;
	return -1;  // 循环结束没有找到结点返回-1 
}
void CreateMGraph()
{
	ifstream myfile;  //定义变量 
	myfile.open("E://graph_shortpath.txt");  //打开文件
	myfile >> Graph->v_num >> Graph->e_num;  // 读入第一行数据 
	cout << "结点数: " << Graph->v_num << endl;  // 将读入的节点数和边数输出 
	cout << "边数: " << Graph->e_num << endl;
	for (int i = 0; i < Graph->v_num; i++) // 读入结点信息 
	{
		myfile >> Graph->vertex[i];
	}
	cout << "结点有: ";
	for (int i = 0; i < Graph->v_num; i++) // 输出结点信息 
	{
		cout << Graph->vertex[i] << " ";

	}
	cout << endl;
	InitMGraph();  // 初始化邻接矩阵 
	for (int k = 0; k < Graph->e_num; k++)  // 读入边的信息 
	{
		int i, j, weight;
		VertexType v1, v2;  // 结点为字符型变量
		myfile >> v1 >> v2 >> weight;  // 读入一条边, 包括两个结点和权重 
		i = GetIndex(v1);  // 获取结点下标 
		j = GetIndex(v2);
		Graph->edge[i][j] = weight;
		Graph->edge[j][i] = weight;
		//		cout << Graph->edge[i][j]; 
		cout << "(" << v1 << ", " << v2 << ")" << " = " << weight << endl;
	}
}

void Print()  // 输出邻接矩阵 
{
	cout << "邻接矩阵为: " << endl;
	for (int i = 0; i < Graph->v_num; i++)
	{
		for (int j = 0; j < Graph->v_num; j++)
		{
			cout.width(8);
			cout << Graph->edge[i][j];
		}
		cout << endl;
	}
}


int s[MaxV];  // 存放源点和已经已经生成的终点(存放已经处理过的结点) 
int dist[MaxV];  // 当前最短路径的长度
int path[MaxV];  // 当前最短路径 

int FindMinDist()  // 在dist数组中查找s[i]为0的最小元素 
{
	int min = INFINITY;
	int min_index = -1;
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (s[i] == 0 && dist[i] < min)
		{
			min = dist[i];
			min_index = i;  // 返回当前最短路径的下标 
		}
	}
	return min_index;
}


void ShortPath_Dijkstra(VertexType start_vex)
{
	int startVertexIndex = GetIndex(start_vex);  // 获取结点的下标 
	for (int i = 0; i < Graph->v_num; i++)  // 初始化s, dis 两个数组 
	{
		s[i] = 0;  //初始化数组s 
		dist[i] = Graph->edge[startVertexIndex][i];  // 初始化数组dist 
		if (dist[i] == INFINITY)  // 如果dist中的值为无穷大, 则将path中下标相同的值设为-1 
		{
			path[i] = -1;
		}
		else
		{
			path[i] = startVertexIndex;  // 否则设为源点下标 
		}
	}
	s[startVertexIndex] = 1;  // 顶点放入集合S, 1代表带集合中, 0代表不在集合中 
	int cnt = 1;  // 用于统计已经处理过的顶点个数 
	while (cnt < Graph->v_num)  // 只要有还没处理过的顶点, 就一直循环 
	{
		int min = FindMinDist();  // dist数组中查找s[i]为0的最小元素  
		s[min] = 1;  // 将新的最短路径的终点放入集合S, 代表处理过了
		for (int i = 0; i < Graph->v_num; i++)  // 修改数组dist 和 path 
		{
			if ((s[i] == 0) && (dist[i] > dist[min] + Graph->edge[min][i]))
			{  // 选择没处理过的结点, 如果源点到 i 点的距离 大于它经过新节点到 i 点的距离 
				dist[i] = dist[min] + Graph->edge[min][i];  //  用已找到的最短路径修改对应的dist
				path[i] = min;  //  更新path数组的值 

			}
		}
		cnt++;  // 每处理完一个值, cnt    
	}
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (i == GetIndex(start_vex)) continue;
		cout << start_vex << "->" << GetVerx(i) << " 最短路径长度: " << dist[i] << endl;
	}
}

void PrintPath(VertexType start, VertexType end)
{
	int start_index = GetIndex(start);
	int end_index = GetIndex(end);
	if (path[end_index] == path[start_index])
	{
		return;
	}
	else
	{
		PrintPath(start, GetVerx(path[end_index]));
		cout << GetVerx(path[end_index]) << "->";
	}
}

void ChosePath()  // 选择源点, 输出最短路径 
{
	char start_vex = -1;
	while (true)
	{
		cout << "输入最短路径的源点(从A~I中选择, 输入0结束): ";
		cin >> start_vex;
		if (start_vex == '0') break;  // 输入0时退出 

		ShortPath_Dijkstra(start_vex);
	}
	while (true)
	{
		char start, end;
		cout << "再次输入该源点和任意一个终点(如: AC), 将显示完整最短路径(A->B->C), 输入00结束: ";
		cin >> start >> end;
		if (start == '0') break;  // 输入00时退出
		PrintPath(start, end);
		cout << end << endl;
	}
}


int main()
{
	CreateMGraph();
	Print();
	ChosePath();
	return 0;
} 
