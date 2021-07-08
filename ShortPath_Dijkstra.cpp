/*
* �ڽӾ���洢
*/

#include<fstream>
#include<iostream>
using namespace std;
#define MaxV 101 // ������ֵ 
#define MAX_SIZE 101  // ջ������� 
#define INFINITY 65535 
typedef char VertexType;
struct MGraph // ͼ�Ľṹ��
{
	char vertex[MaxV];  // ���� 
	int edge[MaxV][MaxV];  // �ڽӾ��� 
	int v_num, e_num;  // ����� ���� 
};
MGraph* Graph = new MGraph;



void InitMGraph()  // ��ʼ��ͼ (��ͼ�и������� �� INFINITY)
{
	for (int i = 0; i < Graph->v_num; i++)
	{
		for (int j = 0; j < Graph->v_num; j++)
			Graph->edge[i][j] = INFINITY;
	}
}

char GetVerx(int i)  // �����±��ҵ���Ӧ�Ľ��
{
	return Graph->vertex[i];
}

int GetIndex(char c)  // ���ݽ���ҵ���Ӧ���±�
{
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (c == Graph->vertex[i])
		{
			return i;
		}
	}
	cout << "����: û�н��" << c << endl;
	return -1;  // ѭ������û���ҵ���㷵��-1 
}
void CreateMGraph()
{
	ifstream myfile;  //������� 
	myfile.open("E://graph_shortpath.txt");  //���ļ�
	myfile >> Graph->v_num >> Graph->e_num;  // �����һ������ 
	cout << "�����: " << Graph->v_num << endl;  // ������Ľڵ����ͱ������ 
	cout << "����: " << Graph->e_num << endl;
	for (int i = 0; i < Graph->v_num; i++) // ��������Ϣ 
	{
		myfile >> Graph->vertex[i];
	}
	cout << "�����: ";
	for (int i = 0; i < Graph->v_num; i++) // ��������Ϣ 
	{
		cout << Graph->vertex[i] << " ";

	}
	cout << endl;
	InitMGraph();  // ��ʼ���ڽӾ��� 
	for (int k = 0; k < Graph->e_num; k++)  // ����ߵ���Ϣ 
	{
		int i, j, weight;
		VertexType v1, v2;  // ���Ϊ�ַ��ͱ���
		myfile >> v1 >> v2 >> weight;  // ����һ����, ������������Ȩ�� 
		i = GetIndex(v1);  // ��ȡ����±� 
		j = GetIndex(v2);
		Graph->edge[i][j] = weight;
		Graph->edge[j][i] = weight;
		//		cout << Graph->edge[i][j]; 
		cout << "(" << v1 << ", " << v2 << ")" << " = " << weight << endl;
	}
}

void Print()  // ����ڽӾ��� 
{
	cout << "�ڽӾ���Ϊ: " << endl;
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


int s[MaxV];  // ���Դ����Ѿ��Ѿ����ɵ��յ�(����Ѿ�������Ľ��) 
int dist[MaxV];  // ��ǰ���·���ĳ���
int path[MaxV];  // ��ǰ���·�� 

int FindMinDist()  // ��dist�����в���s[i]Ϊ0����СԪ�� 
{
	int min = INFINITY;
	int min_index = -1;
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (s[i] == 0 && dist[i] < min)
		{
			min = dist[i];
			min_index = i;  // ���ص�ǰ���·�����±� 
		}
	}
	return min_index;
}


void ShortPath_Dijkstra(VertexType start_vex)
{
	int startVertexIndex = GetIndex(start_vex);  // ��ȡ�����±� 
	for (int i = 0; i < Graph->v_num; i++)  // ��ʼ��s, dis �������� 
	{
		s[i] = 0;  //��ʼ������s 
		dist[i] = Graph->edge[startVertexIndex][i];  // ��ʼ������dist 
		if (dist[i] == INFINITY)  // ���dist�е�ֵΪ�����, ��path���±���ͬ��ֵ��Ϊ-1 
		{
			path[i] = -1;
		}
		else
		{
			path[i] = startVertexIndex;  // ������ΪԴ���±� 
		}
	}
	s[startVertexIndex] = 1;  // ������뼯��S, 1�����������, 0�����ڼ����� 
	int cnt = 1;  // ����ͳ���Ѿ�������Ķ������ 
	while (cnt < Graph->v_num)  // ֻҪ�л�û������Ķ���, ��һֱѭ�� 
	{
		int min = FindMinDist();  // dist�����в���s[i]Ϊ0����СԪ��  
		s[min] = 1;  // ���µ����·�����յ���뼯��S, ���������
		for (int i = 0; i < Graph->v_num; i++)  // �޸�����dist �� path 
		{
			if ((s[i] == 0) && (dist[i] > dist[min] + Graph->edge[min][i]))
			{  // ѡ��û������Ľ��, ���Դ�㵽 i ��ľ��� �����������½ڵ㵽 i ��ľ��� 
				dist[i] = dist[min] + Graph->edge[min][i];  //  �����ҵ������·���޸Ķ�Ӧ��dist
				path[i] = min;  //  ����path�����ֵ 

			}
		}
		cnt++;  // ÿ������һ��ֵ, cnt    
	}
	for (int i = 0; i < Graph->v_num; i++)
	{
		if (i == GetIndex(start_vex)) continue;
		cout << start_vex << "->" << GetVerx(i) << " ���·������: " << dist[i] << endl;
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

void ChosePath()  // ѡ��Դ��, ������·�� 
{
	char start_vex = -1;
	while (true)
	{
		cout << "�������·����Դ��(��A~I��ѡ��, ����0����): ";
		cin >> start_vex;
		if (start_vex == '0') break;  // ����0ʱ�˳� 

		ShortPath_Dijkstra(start_vex);
	}
	while (true)
	{
		char start, end;
		cout << "�ٴ������Դ�������һ���յ�(��: AC), ����ʾ�������·��(A->B->C), ����00����: ";
		cin >> start >> end;
		if (start == '0') break;  // ����00ʱ�˳�
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
