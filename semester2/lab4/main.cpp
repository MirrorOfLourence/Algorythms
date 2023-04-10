#include <iostream>
#include <vector>
#include <fstream>


void DFS(int st, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited)  //ф-ия поиска 
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
    std::vector<std::vector<int>> graph;    //Граф

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

    std::vector<bool> visited(graph.size(), false);
    for (std::vector<bool>::iterator i = std::find(visited.begin(), visited.end(), false); i != visited.end();)
    {
        int j = i - visited.begin();
        std::cout << "Старт в вершине " << j << ": ";
        DFS(j, graph, visited);
        std::cout << std::endl;
        i = std::find(visited.begin(), visited.end(), false);
    }


    return 0;
}
