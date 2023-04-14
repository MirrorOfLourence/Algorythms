#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> invertedGraph;
std::vector<bool> visitedVertaxes;
std::vector<int> components;
std::stack<int> order;
int processingTime = 1;

void DFS(int st)
{
    int r = 0;
    visitedVertaxes[st] = true;
    for (r = 0; r < graph[0].size(); r++)
    {
        if ((graph[st][r] != 0) && (!visitedVertaxes[r]))
        {
            DFS(r);
        }
    }  
    order.push(st);
}
void DFSInverted(int st)
{
    components[st] = processingTime;
    for (int i = st; i < invertedGraph[0].size(); i++)
    {
        if (components[i] == 0)
        {
            DFSInverted(i);
        }
    }

}
int main()
{

    setlocale(LC_ALL, "Rus");

    std::ifstream in;   //����� �� ����
    in.open("input.txt");   //��������� � ����� ���� �����
    if (in.is_open())   //���� ���� ��������, ��
    {
        char c; //���� ��������� ��������� ������
        std::vector<int> line;  //������, � ������� ��������� ������
        for (c = in.get(); c != EOF; c = in.get())   //�������� ������ �� ����� �����
        {
            if (c == '\n')  //���� ����� �� ����� ������, ����� � � ������
            {
                graph.push_back(line);
                line.clear();
            }
            else    //����� ����� � ������ ��������� ������
            {
                line.push_back(c - '0');
            }

        }
        graph.push_back(line);  //����� � ������ ��������� ������, �.�. �� �������������� � ����� ��-�� EOF � ����� �����
        line.clear();
    }
    else    //���� ���� �� ��������, ��
    {
        std::cout << "������: �� ������� ������� ����!" << std::endl;   //����� ������
    }

    invertedGraph=graph;    //������ ��������������� ����
    for (int i = 0; i < invertedGraph.size(); i++)
    {
        for (int j = i; j < invertedGraph[0].size(); j++)
        {
            if (((invertedGraph[i][j] == 1) && (invertedGraph[j][i] == 0)) || ((invertedGraph[j][i] == 1) && (invertedGraph[i][j] == 0)))
            {
                int temp = invertedGraph[i][j];
                invertedGraph[i][j] = invertedGraph[j][i];
                invertedGraph[j][i] = temp;
            }
        }
    }
        
    for (int i = 0; i < graph[0].size(); i++)
    {
        visitedVertaxes.push_back(false);
        components.push_back(0);
    }
    for (int i = 0; i < visitedVertaxes.size(); i++)
    {
        if (visitedVertaxes[i] == false)
        {
            DFS(i);
        }
    }
    while (!order.empty())
    {
        int currentVertex = order.top(); order.pop();
        if (components[currentVertex] == 0)
        {
            DFSInverted(currentVertex);
            processingTime++;
        }
    }
    processingTime--;   //������� ������ ����������� ����������
    while (processingTime > 0)  //������� ��� ���������� �� �����
    {
        std::cout << "���������� �" << processingTime << ":";
        for (int i = 0; i < components.size(); i++)
        {
            if (components[i] == processingTime)
            {
                std::cout << " " << i;
            }
        }
        std::cout << std::endl;
        processingTime--;
    }
    return 0;
}
