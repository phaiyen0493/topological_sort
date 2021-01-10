/*Name: Yen Pham
CS3110
Assignment 5
*/

#include<iostream> 
#include <vector> 
#include <sstream>
#include <fstream>
#include <string>

using namespace std; 

// Class to represent a graph 
class Graph 
{ 
	int vertice_count; // number of vertices' 
	vector<int> *adj_list; // pointer to an array containing adjacency lists
	void topological_sort_utility(int vertice, bool visited[], vector<int> &Stack); // A function used by topological sort 
	
	public: 
	Graph(int vertice_count); // Constructor 
	void add_edge(int vertice, int adj_vertice); // function to add an edge to graph 
	void topological_sort(); // prints a topological sort of the complete graph 
}; 

Graph::Graph(int vertice_count) 
{ 
	this->vertice_count = vertice_count; 
	adj_list = new vector<int>[vertice_count]; 
} 

void Graph::add_edge(int vertice, int adj_vertice) 
{ 
	adj_list[vertice-1].push_back(adj_vertice-1); // Add adjency vertices to vertex list
} 

// A recursive function used by topologicalSort 
void Graph::topological_sort_utility(int vertice_index, bool visited[], vector<int> &stack) 
{ 
	// Mark the current node as visited. 
	visited[vertice_index] = true; 

	// Recur for all the vertices adjacent to this vertex 
	for (int i = 0; i < adj_list[vertice_index].size(); ++i)
	{
		if (!visited[adj_list[vertice_index][i]])
		{ 
			topological_sort_utility(adj_list[vertice_index][i], visited, stack);
		}
	}

	// Push current vertex to stack which stores result 
	stack.push_back(vertice_index); 
} 

// The function to do Topological Sort. It uses recursive topological_sort_util() 
void Graph::topological_sort() 
{ 
	vector <int> stack; 
	ofstream fout;
	fout.open("out5.txt");

	// Mark all the vertices as not visited 
	bool *visited = new bool[vertice_count]; 
	for (int i = 0; i < vertice_count; i++)
	{
		visited[i] = false;
	}

	// Sort starting from all vertices one by one 
	for (int i = 0; i < vertice_count; i++)
	{ 
		if (visited[i] == false)
		{ 
			topological_sort_utility(i, visited, stack);
		}
	} 

	// Print contents of stack
	fout << "Topological ordering is: "; 
	while (stack.empty() == false) 
	{ 
		fout << stack.back()+1 << " "; 
		stack.pop_back(); 
	}
	fout.close();
} 

int count_vertices()
{
	int vertice_count = 0;
	string line;

	ifstream fin("data5.txt");
	if (fin.fail())
	{
		cout << "cannot open file data5.txt" << endl;
		exit(0);
	}

	while(getline(fin, line) && line.length() !=0 )
	{
		vertice_count++;
	}

	return vertice_count;
}

int main()
{
	ifstream fin("data5.txt"); //input file
	string line;

	if (fin.fail())
	{
		cout << "cannot open file data5.txt" << endl;
		exit(0);
	}

	int vertice_count = count_vertices();
	//cout << "vertice count: " << vertice_count << endl;

	Graph graph(vertice_count);

	int vertice;
	int adj_vertice;
	
	//read graph
	while(getline(fin, line) && line.length() != 0)
	{
		stringstream is(line);
		is >> vertice;

		while(is >> adj_vertice)
		{
			graph.add_edge(vertice, adj_vertice);
		}
	}

	graph.topological_sort();
	fin.close();

	return 0;
}

