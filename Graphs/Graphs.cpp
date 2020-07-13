// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Vertex.cpp"
#include <iostream>
#include <unordered_map>
#include <string>

struct SearchResult
{
    bool found;
    Vertices path;
};

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
    Vertices searchDepth(std::string src, std::string dest);
    SearchResult searchV2(std::string src, std::string dest, Vertices visited, SearchResult resultSoFar);
    SearchResult searchDriver(std::string src, std::string dest);
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
    graph[src].addNode(dst, wgt);
    graph[dst].addNode(src, wgt);
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
   returns the amount of neighbors the given node has in the graph */
int Graph::neighborCount(std::string src)
{
    return graph[src].length(); // uses the Vertices::length function
}

Vertices Graph::searchDepth(std::string src, std::string dest)
{
    Vertices path = Vertices();
    if (src == dest)
    {
        path.addNode(src, 0);
    }
    else
    {
        Vertices neighbors = getNeighbors(src);
        Vertices visited = Vertices();
        visited.addNode(src,0);        // don't try this place again
        path.addNode(src,0);        // don't try this place again
        while (!neighbors.isEmpty())
        {
            Vertex * nghbr = neighbors.pop();
            if (!visited.contains(nghbr->name)) 
            {
                std::string nghbrName = nghbr->name;
                int nghbrWght = nghbr->weight;
                
                if (nghbrName == dest)  // have we found it in one step?
                {
                    path.addNode(nghbrName, nghbrWght);
                    return path;
                }
                else // this neighbor wasn't it, but maybe they lead to the path
                { 
                    visited.addNode(nghbrName, 0);      // don't loop forever!
                    path.addNode(nghbrName, nghbrWght); // don't forget we came through here
                    neighbors.append(getNeighbors(nghbrName)); // expand the list of nodes to visit
                }
            } 
        }
    }
    return path;
}

SearchResult updateSearchResultPath(SearchResult res, std::string nodeName, int nodeWgt) 
{
    Vertices pathSoFar = res.path;
    pathSoFar.addNode(nodeName, nodeWgt);
    res.path = pathSoFar;
    return res;
}

SearchResult returnFoundResult(SearchResult resultSoFar, std::string name, int weight)
{ 
    resultSoFar.found = true;
    return updateSearchResultPath(resultSoFar, name, weight);
}

SearchResult Graph::searchDriver(std::string src, std::string dest) 
{
    return searchV2(src, dest, Vertices(), SearchResult{ false,Vertices() });
}

SearchResult Graph::searchV2(std::string src, std::string dest, Vertices visited, SearchResult resultSoFar) 
{
    if (src == dest)
    {
        return returnFoundResult(resultSoFar, src, 0);
    }
    else 
    {
        Vertices neighbors = getNeighbors(src);
        visited.addNode(src,0);
        while (!neighbors.isEmpty())
        {
            Vertex * neighbor = neighbors.pop();
            SearchResult followNeighbor = updateSearchResultPath(resultSoFar, neighbor->name, neighbor->weight);
            SearchResult recur = searchV2(neighbor->name, dest, visited, followNeighbor);
            if (recur.found)
            {
                return recur;
            }
            else 
            {
                if (!visited.contains(neighbor->name))
                {
                    neighbors.append(getNeighbors(neighbor->name));
                    visited.addNode(neighbor->name,neighbor->weight);
                }
            }
        }
    }
}

int main()
{
    std::cout << "Hello World! Don't mind me!\n";
    Graph testGraph = Graph();
    testGraph.addEdge("Start", "B", 9);
    testGraph.addEdge("Start", "A", 7);
    testGraph.addEdge("B", "E", 10);
    testGraph.addEdge("A", "C", 3);
    testGraph.addEdge("C", "D", 8);
    // testGraph.addEdge("D", "E", 5);
    SearchResult sr = testGraph.searchDriver("Start", "E");
    sr.path.show();
    std::cout << "=========== end program ===========";
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
