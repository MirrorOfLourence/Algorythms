#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::vector<int>> graph;
std::vector<bool> visited;

void DFS(int st)
{
    int r = 0;
    std::cout << st << " ";
    visited[st] = true;
    for (r = 0; r < graph[0].size(); r++)
    {
        if ((graph[st][r] != 0) && (!visited[r]))
        {
            DFS(r);
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

    for (int i = 0; i < graph[0].size(); i++)
    {
        visited.push_back(false);
    }
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i] == false)
        {
            std::cout << "Для вершины " << i << ": ";
            DFS(i);
            std::cout << std::endl;
        }
        
    }
    return 0;
}
