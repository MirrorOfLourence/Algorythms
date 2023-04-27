#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

class Edge {
public:
	Edge(int vertex1, int vertex2)
		:vertex1(vertex1), vertex2(vertex2)
	{
	};
	int vertex1, vertex2;
};

std::string color[] =
{
	"", "CИНИЙ", "ЗЕЛЁНЫЙ", "КРАСНЫЙ", "ЖЁЛТЫЙ", "ОРАНЖЕВЫЙ", "РОЗОВЫЙ",
	"ЧЁРНЫЙ", "КОРИЧНЕВЫЙ", "БЕЛЫЙ", "СИРЕНЕВЫЙ", "ФИОЛЕТОВЫЙ"

};

int main()
{
    setlocale(LC_ALL, "Rus");

	int vertex1, vertex2, n = 0;	
	std::vector<std::vector<int>> adjacency;
	std::vector<Edge> edges;
	std::unordered_map<int,int> colorsOfVertexes;

	std::cout << 
		"Введите данные в формате: вершина1, вершина2, вес ребра(для прекращени¤ ввода введите любые отрицательные значения)"
		<< std::endl;
	std::cin >> vertex1 >> vertex2;
	while ((vertex1 >= 0) && (vertex2 >= 0))	//считываем входящий граф
	{
		edges.push_back(Edge(vertex1, vertex2)); 
		if(vertex1 > n) 
			n = vertex1;
		if(vertex2 > n)
			n = vertex2;

		std::cin >> vertex1 >> vertex2;
	}
	n++;
	
	adjacency.resize(n, std::vector<int>(n,0));	//формируем матрицу смежности
	for (Edge edge : edges)
	{
		adjacency[edge.vertex1][edge.vertex2] = 1;
		adjacency[edge.vertex2][edge.vertex1] = 1;
	}

	for (int i = 0; i < n; i++)
	{
		std::set<int> assigned;	//сет для хранения цвета смежных вершин

		for (int j = 0; j < n; j++)
		{
			if (adjacency[i][j])	//если вершина смежная с i
			{
				assigned.insert(colorsOfVertexes[j]);	//то добавляем цвет окрашенной вершины в сет
			}
		}

		int col = 1;	//проверяем первый свободный цвет
		if (assigned.size() > 1)
		{
			for (auto& c : assigned)
			{
				if((c >= assigned.size()-1) && (col != c))
					break;
				col++;
			}
		}
		colorsOfVertexes[i] = col;	//назначаем текущей вершине первый свободный цвет
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << "Цвет вершины " << i << ": "
			<< color[colorsOfVertexes[i]] << std::endl;
	}
    return 0;
}

/*0 1
0 4
0 5
4 5
1 4
1 3
2 3
2 4
-1 -1*/