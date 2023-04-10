#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

void remove(std::vector<int>& v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}

int BFS(std::vector<std::vector<int>>& graph)  //�-�� ������ 
{
    int length = graph[0].size();
    std::queue<int> q;  //������� ��� ��������� ������
    std::vector<bool>  used(length);   //������ �������������� ������
    std::vector<std::vector<int>> components;
    int count = 0;
    bool flag = 0;
    while (!flag)
    {
        for (int i = 0; i < length; i++)    //���� ���� ������������ �������
        {
            if (used[i] == false)
            {
                q.push(i);      //������������ ������������ �������
                break;
            }
            if (i == length - 1)
            {
                flag = true;
            }

        }
        if (!flag)
        {
            components.push_back(std::vector<int> {});
            while (!q.empty())   //���� ������� �� �����, ��������� ��������� �����
            {
                int current = q.front();    //����������� ������� ������� �� �������
                q.pop();
                used[current] = true;
                components[count].push_back(current);

                for (int i = 0; i < length; i++)    //������� �������� � ������� �������
                {
                    if ((graph[current][i] == 1) && (used[i] == false)) //���� ����� ������������ ��� �������� �������, 
                    {
                        q.push(i);  //��������� � � �������

                    }
                }
            }
            remove(components[count]);
            count++;

        }
    }
    
    for (std::vector<int> v : components)
    {
        for (int e : v)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl << std::endl;
    }

    return count;
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

    std::cout << "����� ��������� ���������: " << BFS(graph) << std::endl;
    return 0;
}
