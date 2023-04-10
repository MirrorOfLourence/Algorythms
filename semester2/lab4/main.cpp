#include <iostream>
#include <vector>
#include <fstream>


void DFS(int st, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited)  //�-�� ������ 
{
    int r=0;
    std::cout<<st<<" ";
    visited[st]=true;
    for (r=0; r<graph[0].size(); r++)
        if ((graph[st][r]!=0) && (!visited[r]))
            DFS(r, graph, visited);
}

int main()
{
   
    setlocale(LC_ALL, "Rus");
    std::vector<std::vector<int>> graph;    //����

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

    std::vector<bool> visited(graph.size(), false);
    for (std::vector<bool>::iterator i = std::find(visited.begin(), visited.end(), false); i != visited.end();)
    {
        int j = i - visited.begin();
        std::cout << "����� � ������� " << j << ": ";
        DFS(j, graph, visited);
        std::cout << std::endl;
        i = std::find(visited.begin(), visited.end(), false);
    }


    return 0;
}
