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

    std::ifstream in;   //поток на вход
    in.open("input.txt");   //загружаем в поток файл ввода
    if (in.is_open())   //если файл открылся, то
    {
        char c; //сюда считываем очередной символ
        std::vector<int> line;  //вектор, в который загружаем строку
        for (c = in.get(); c != EOF; c = in.get())   //проходим циклом до конца файла
        {
            if (c == '\n')  //если дошли до конца строки, пушим её в вектор
            {
                graph.push_back(line);
                line.clear();
            }
            else    //иначе пушим в строку очередной символ
            {
                line.push_back(c - '0');
            }

        }
        graph.push_back(line);  //пушим в вектор последнюю строку, т.к. не обрабатывается в цикле из-за EOF в конце файла
        line.clear();
    }
    else    //если файл не открылся, то
    {
        std::cout << "ОШИБКА: Не удалось открыть файл!" << std::endl;   //выдаём ошибку
    }

    invertedGraph=graph;    //создаём инвертированный граф
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
    processingTime--;   //убираем лишнюю насчитанную компоненту
    while (processingTime > 0)  //выводим все компоненты на экран
    {
        std::cout << "Компонента №" << processingTime << ":";
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
