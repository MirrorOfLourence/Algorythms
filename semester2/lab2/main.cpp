#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

//нумерация вершин начинается с 0
void BFS(std::vector<std::vector<int>>& graph)  //ф-ия поиска 
{
    int length = graph[0].size();
    std::queue<int> q;  //очередь для обработки вершин
    std::vector<bool>  used(length);   //вектор использованных вершин
    std::vector<int> dist(length);
    
    //обрабатываем начальную вершину
    q.push(0);

    while (!q.empty())   //пока очередь не пуста, выполняем обработку графа
    {
        int current = q.front();    //вытаскиваем текущую вершину из очереди
        q.pop();
        used[current] = true;

        for (int i = 0; i < length; i++)    //смотрим соседние к текущей вершины
        {
            if ((graph[current][i] == 1) && (used[i] == false)) //если нашли непомеченную ещё соседнюю вершину, 
            {
                q.push(i);  //добавляем её в очередь
                dist[i] = dist[current] + 1;    //расстояние до неё = расстоянию до предыдущей +1
            }
        }
    }
    for (int i = 1; i < length; i++)
    {
        std::cout << "Расстояние от вершины А до вершины " << (char)(65+i) << ":\t" << dist[i] << std::endl;
    }

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
        for (c = in.get(); c!= EOF; c = in.get())   //проходим циклом до конца файла
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

    BFS(graph);

    return 0;
}
