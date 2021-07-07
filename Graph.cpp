/*
* 邻接矩阵存储
*/

#include<fstream>
#include<iostream>
using namespace std;
#define MaxV 101 
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
	myfile.open("E://graph.txt");  //打开文件
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

void Print()
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

struct shortEdge
{
	VertexType adjvex;  // 最小边在集合U中的顶点 
	int lowcost;  // 最小边的权值 
};
shortEdge shortedge[MaxV];  //辅助数组, 记录从顶点集U到V-U的权值最下的边 

int MinEdge(shortEdge shortedge[], int v_num)  // 寻找最短边的邻接点
{
	int min = 65535;  // 将一个不会被取到的最大数值赋给最小值, 便于最小值更新 
	int min_index = -1;
	for (int i = 0; i < v_num; i++)
	{
		if (shortedge[i].lowcost != 0 && shortedge[i].lowcost < min)
		{
			min = shortedge[i].lowcost;
			min_index = i;
		}
	}
	return min_index;
}

void MiniSpanTree_Prim(char c)  // Prim算法生成最小生成树// change
{
	cout << "最小生成树为: " << endl;
	int start_index = GetIndex(c);  // 获取始点的下标 
	for (int i = 0; i < Graph->v_num; i++)  // 辅助数组初始化 
	{
		shortedge[i].lowcost = Graph->edge[start_index][i];  // 将邻接矩阵始点到各点的权重依次复制进lowcost数组 
		//cout << i <<",lowcost = " << shortedge[i].lowcost << endl; 
		shortedge[i].adjvex = c;  // 将始点赋给adjvex 
		//cout << i <<",adjvex = " << shortedge[i].adjvex << endl; 
	}
	shortedge[start_index].lowcost = 0;  // 始点start放入集合U

	for (int i = 1; i < Graph->v_num; i++)
	{
		start_index = MinEdge(shortedge, Graph->v_num);
		cout << "(" << shortedge[start_index].adjvex << ", " << Graph->vertex[start_index] << ")" << " = " << shortedge[start_index].lowcost << endl;
		shortedge[start_index].lowcost = 0;  // 将顶点k加入到集合U 
		for (int j = 0; j < Graph->v_num; j++)  //邻接矩阵k行逐个遍历
		{
			if (Graph->edge[start_index][j] < shortedge[j].lowcost)
			{
				shortedge[j].lowcost = Graph->edge[start_index][j];
				//	cout << "shortedge[" << j << "].lowcost = " << shortedge[j].lowcost << endl;  
				shortedge[j].adjvex = Graph->vertex[start_index];
				//	cout << "shortedge[" << j << "].adjvex = " << shortedge[j].adjvex << endl; 
			}
		}
	}
}
void ChoseTree()  // 输入结点生成最小生成树
{
	char start_vex = -1;
	while (true)
	{
		cout << "输入最小生成树的开始结点(从A~G中选择, 输入0结束): ";
		cin >> start_vex;
		if (start_vex == '0') return;
		MiniSpanTree_Prim(start_vex);
	}
}
int main()
{
	CreateMGraph();
	Print();
	ChoseTree();
	return 0;
}