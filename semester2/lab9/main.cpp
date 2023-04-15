#include <iostream>
#include <vector>

class Edge {
public:
	Edge(int vertex1, int vertex2, int weight)
		:vertex1(vertex1), vertex2(vertex2), weight(weight)
	{
	};
	int vertex1, vertex2, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}

};

int main()
{
    setlocale(LC_ALL, "Rus");
	int vertex1, vertex2, weight, n = 0;
	std::vector<Edge> edges;
	std::vector<bool> visitedVertexes;
	std::vector<int> tagsOfVertexes;
	//ВВОД ДАННЫХ
	std::cout << 
		"Введите данные в формате: вершина1, вершина2, вес ребра(для прекращения ввода введите любые отрицательные значения)"
		<< std::endl;
	std::cin >> vertex1 >> vertex2 >> weight;
	while ((vertex1 >= 0) && (vertex2 >= 0) && (weight >= 0))
	{
		edges.push_back(Edge(vertex1, vertex2, weight)); 
		int current = edges.size() - 1;
		if (current > 1)
		{
			while ((current > 0) && (edges[current - 1].weight > edges[current].weight))//сортируем вершины по неубыванию
			{
				std::swap(edges[current - 1],edges[current]);
				current--;
			}
		}
		if(vertex1 > n) 
			n = vertex1;
		if(vertex2 > n)
			n = vertex2;

		std::cin >> vertex1 >> vertex2 >> weight;
	}
	n++;
	tagsOfVertexes.resize(n, 200000000);
	visitedVertexes.resize(n, false);
	std::vector<std::vector<int>> adjacency(n, std::vector<int>(n,0));
	for (Edge edge : edges)
	{
		adjacency[edge.vertex1][edge.vertex2] = edge.weight;
		adjacency[edge.vertex2][edge.vertex1] = edge.weight;
	}
	tagsOfVertexes[0] = 0;
	for (int i = 1; i <= n; i++)	//перебираем вершины
	{
		int numOfEdges = edges.size();
		for (int j = 0; j < numOfEdges; j++)
		{
			if(tagsOfVertexes[edges[j].vertex2] > tagsOfVertexes[edges[j].vertex1] + edges[j].weight)
				tagsOfVertexes[edges[j].vertex2] = tagsOfVertexes[edges[j].vertex1] + edges[j].weight;
			if(tagsOfVertexes[edges[j].vertex1] > tagsOfVertexes[edges[j].vertex2] + edges[j].weight)
				tagsOfVertexes[edges[j].vertex1] = tagsOfVertexes[edges[j].vertex2] + edges[j].weight;
		}
	}
	std::cout << "Кратчайшие пути:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "0 - " << i << "\t" << tagsOfVertexes[i] << std::endl;
	}
    return 0;
}

/*
0 1 7
0 2 8
1 2 11
1 3 2
2 3 6
2 4 9
3 4 11
3 5 9
4 5 10
-1 -1 -1*/