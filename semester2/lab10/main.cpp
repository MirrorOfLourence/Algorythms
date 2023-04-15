#include <iostream>
#include <vector>
#include <stack>

class Edge {
public:
	Edge(int vertex1, int vertex2)
		:vertex1(vertex1), vertex2(vertex2)
	{
	};
	int vertex1, vertex2;
};

std::vector<Edge> edges;	//вектор рЄбер
std::vector<int> degreesOfVertexes;	//степени вершин

void countDegrees()
{
	for (int i = 0; i < degreesOfVertexes.size(); i++)
	{
		degreesOfVertexes[i] = 0;
	}
	for (Edge edge : edges)
	{
		degreesOfVertexes[edge.vertex1]++; degreesOfVertexes[edge.vertex2]++;
	}
}

int main()
{
    setlocale(LC_ALL, "Rus");
	int vertex1, vertex2, n = 0;
	
	std::vector<int> answer;	
	
	//¬¬ќƒ ƒјЌЌџ’
	std::cout << 
		"¬ведите данные в формате: вершина1, вершина2, вес ребра(дл€ прекращени€ ввода введите любые отрицательные значени€)"
		<< std::endl;
	std::cin >> vertex1 >> vertex2;
	while ((vertex1 >= 0) && (vertex2 >= 0))
	{
		edges.push_back(Edge(vertex1, vertex2)); 
		if(vertex1 > n) 
			n = vertex1;
		if(vertex2 > n)
			n = vertex2;

		std::cin >> vertex1 >> vertex2;
	}
	n++;
	
	degreesOfVertexes.resize(n, 0);
	std::vector<std::vector<int>> adjacency(n, std::vector<int>(n,0));	//матрица смежности
	countDegrees();
	bool isEuler = true;
	for (int degree : degreesOfVertexes)
	{
		if(degree % 2 == 1) { isEuler = false; break; }
	}
	if (isEuler)	//провер€ем граф на Ёйлеровость
	{
		std::stack<int> operatingVertexes;
		operatingVertexes.push(0);

		while (!operatingVertexes.empty())
		{
			int currentVertex = operatingVertexes.top(); 
			if (degreesOfVertexes[currentVertex] == 0)
			{
				answer.push_back(currentVertex);
				operatingVertexes.pop();
			}
			else
			{
				for (int i = 0; i < edges.size(); i++)
				{
					if (edges[i].vertex1 == currentVertex)
					{
						operatingVertexes.push(edges[i].vertex2);
						edges.erase(edges.begin() + i);
						countDegrees();
						break;
					}
					else if (edges[i].vertex2 == currentVertex)
					{
						operatingVertexes.push(edges[i].vertex1);
						edges.erase(edges.begin() + i);
						countDegrees();
						break;
					}
				}
			}
		}
		std::cout << "Ёйлеров цикл: ";
		for (int vertex : answer)
		{
			std::cout << " " << vertex;
		}
		std::cout << std::endl;
	}
	else
		std::cout << "√раф не €вл€етс€ Ёйлеровым!" << std::endl;

    return 0;
}

/*
0 1
0 2
1 2
2 3
2 4
3 4
-1 -1 */