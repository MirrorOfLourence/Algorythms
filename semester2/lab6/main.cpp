#include <iostream>
#include <vector>
#include <algorithm> 

std::vector<int> parent, rank;

void make_set(int vertex) {
	parent[vertex] = vertex;
	rank[vertex] = 0;
}

int find_set(int vertex) {
	if (vertex == parent[vertex])
		return vertex;
	return parent[vertex] = find_set(parent[vertex]);

}

void union_sets(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a != b) {
		if (rank[a] < rank[b])
			std::swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			rank[a]++;
	}
}

class Edge {
public:
	Edge(int u, int v, int weight)
		:u(u), v(v), weight(weight)
	{
	};
	int u, v, weight;
	bool operator<(Edge const& other) {
		return weight < other.weight;
	}

};

int main()
{
    setlocale(LC_ALL, "Rus");
	int vertex1, vertex2, weight, cost = 0;
	std::vector<Edge> edges;
	std::vector<Edge> result;
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
		std::cin >> vertex1 >> vertex2 >> weight;
	}
	int n=edges.size();
	
	parent.resize(n);
	rank.resize(n);
	for (int i = 0; i < n; i++)
		make_set(i);

	for (Edge e : edges) {
		if (find_set(e.u) != find_set(e.v)) {
			cost += e.weight;
			result.push_back(e);
			union_sets(e.u, e.v);
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