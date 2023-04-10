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

int BFS(std::vector<std::vector<int>>& graph)  //ф-ия поиска 
{
    int length = graph[0].size();
    std::queue<int> q;  //очередь для обработки вершин
    std::vector<bool>  used(length);   //вектор использованных вершин
    std::vector<std::vector<int>> components;
    int count = 0;
    bool flag = 0;
    while (!flag)
    {
        for (int i = 0; i < length; i++)    //пока есть непомеченные вершины
        {
            if (used[i] == false)
            {
                q.push(i);      //обрабатываем непомеченную вершину
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
            while (!q.empty())   //пока очередь не пуста, выполняем обработку графа
            {
                int current = q.front();    //вытаскиваем текущую вершину из очереди
                q.pop();
                used[current] = true;
                components[count].push_back(current);

                for (int i = 0; i < length; i++)    //смотрим соседние к текущей вершины
                {
                    if ((graph[current][i] == 1) && (used[i] == false)) //если нашли непомеченную ещё соседнюю вершину, 
                    {
                        q.push(i);  //добавляем её в очередь

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

    std::cout << "Число компонент связности: " << BFS(graph) << std::endl;
    return 0;
}
