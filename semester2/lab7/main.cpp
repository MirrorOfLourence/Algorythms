#include <iostream>
#include <vector>
#include <algorithm> 

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
	int vertex1, vertex2, weight, result = 0, cost = 0, n = 0;
	std::vector<Edge> edges;
	std::vector<Edge> operatedEdges;
	std::vector<bool> operatedVertexes;
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
	operatedVertexes.resize(n, false);

	for (int i = 0; i < n; i++)
	{
		if ((!operatedVertexes[i]) && (i < n-1))
		{
			int minWeight = INT_MAX;
			int minNum = 0;
			for (int j = 0; j < edges.size(); j++)
			{
				if (((edges[j].vertex1 == i) || (edges[j].vertex2 == i)) && (edges[j].weight < minWeight))
				{
					minWeight = edges[j].weight;
					minNum = j;
				}
			}
			operatedVertexes[i] = true;
			operatedEdges.push_back(edges[minNum]);
			edges.erase(edges.begin() + minNum);
			result+=minWeight;
			
		}
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