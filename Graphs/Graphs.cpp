// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Vertex.cpp"
#include <iostream>
#include <unordered_map>
#include <string>

class Graph 
{
typedef std::unordered_map<std::string, Vertices> EdgeMap;

private:
    EdgeMap graph;

public:
    Graph();
    void addEdge(std::string src, std::string dst, int wgt);
    void addNode(std::string src);
    Vertices getNeighbors(std::string src);
	int neighborCount(std::string src);
	void show();
	bool pathBetween(std::string src, std::string dest);
};

// Constructor for Graph class object : contains a pointer to a map from strings to Vertices 
Graph::Graph() 
{
    graph = std::unordered_map<std::string, Vertices>{};
}


/* addEdge : String -> String -> Int -> Void
   adds a vertex with name 'dst' and weight 'wgt' to the neighbors of 'src' */
void Graph::addEdge(std::string src, std::string dst, int wgt)
{
    graph[src].addNodeFront(dst, wgt);
    graph[dst].addNodeFront(src, wgt);
}

/* addNode : String -> Void
   adds an entry in the map for the node with no neighbors (empty list of vertices) */
void Graph::addNode(std::string src)
{
    graph.insert(EdgeMap::value_type(src, Vertices()));
}

/* getNeighbors : String -> [List Vertex] 
   returns a list of pairs of neighbors and the cost to reach them */
Vertices Graph::getNeighbors(std::string src)
{
    return graph[src];
}

/* neighborCount : String -> Int
	returns the amount of neighbors reachable by 1 step from 'src' */
int Graph::neighborCount(std::string src)
{
	return graph[src].length();
}

void Graph::show() 
{
	for (auto elt : graph)
	{
		std::cout << elt.first << " --> ";
		elt.second.show();
		std::cout << "\n";
	}
}

bool Graph::pathBetween(std::string src, std::string dest)
{
	if (src == dest)
	{
		std::cout << "arrived: " << dest << "\n";
		return true;
	}
	Vertices visited = Vertices();
	// pathBetweenAcc(src, dest, visited);

}

int main()
{
    std::cout << "Hello World! Don't mind me!\n";

	std::string firelink = "Firelink Shrine";
	std::string burg = "Undead Burg";
	std::string asylum = "Northern Undead Asylum";
	std::string catacombs = "Catacombs";
	std::string parish = "Undead Parish";
	std::string garden = "Darkroot Garden";
	std::string anor = "Anor Londo";
	std::string tomb = "Tomb of the Giants";
	std::string valley = "Valley of the Drakes";
	std::string londo = "New Londo Ruins";
	std::string blight = "Blighttown";
	std::string depths = "Depths";
	std::string sens = "Sen's Fortress";

	Graph ds1 = Graph();
	ds1.addEdge(firelink, catacombs, 50);
	ds1.addEdge(firelink, parish, 20);
	ds1.addEdge(firelink, depths, 30);
	ds1.addEdge(firelink, londo, 10);
	ds1.addEdge(firelink, burg, 1);

	ds1.addEdge(burg, parish, 20);
	ds1.addEdge(burg, depths, 20);

	ds1.addEdge(catacombs, tomb, 15);

	ds1.addEdge(valley, londo, 10);
	ds1.addEdge(valley, blight, 5);

	ds1.addEdge(londo, garden, 30);
	ds1.addEdge(depths, blight, 15);

	ds1.addEdge(parish, sens, 2);
	ds1.addEdge(parish, garden, 5);

	ds1.addEdge(sens, anor, 50);

	ds1.show();

	std::cout << "-------------------------------------------------\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
