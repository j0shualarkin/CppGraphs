// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
// contains a Graph data structure and algorithms to use

#include "SearchResult.cpp"
#include <unordered_map>


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
    SearchResult DFS(std::string src, std::string dest, Vertices visited, SearchResult resultSoFar);
    SearchResult DFSDriver(std::string src, std::string dest);
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
   returns the amount of neighbors the given node has in the graph 
   used mostly on the testing side of _the solution_ */
int Graph::neighborCount(std::string src)
{
    return graph[src].length(); // uses the Vertices::length function
}

/* DFS : String -> String -> Vertices -> SearchResult -> SearchResult 
    accumulates a path in the `resultSoFar` and avoid infinite loops with `visitedSoFar`
    terminates when src == dest or there are no elements adjacent to `src` that lead to `dest`
*/
SearchResult Graph::DFS(std::string src, std::string dest, Vertices visitedSoFar, SearchResult resultSoFar)
{
    if (src == dest) /* If we got where we're going*/
    {
        resultSoFar.pathFound(); /* signal that we found the destination */
        return resultSoFar;
    }
    else
    {
        visitedSoFar.addNode(src, 0);           /* don't come here again, 0 is arbitrary since `contains()` only cares about the string*/
        Vertices neighbors = getNeighbors(src);
        while (!neighbors.isEmpty())
        {
            Vertex * nextDoor = neighbors.pop();
            if (!visitedSoFar.contains(nextDoor->name))   /* don't go where we've been before */
            {
                SearchResult maybeAns = DFS(nextDoor->name, dest, visitedSoFar, resultSoFar); /* recursion */ 
                if (maybeAns.getBool()) 
                { 
                    maybeAns.addToPath(nextDoor->name, nextDoor->weight); /* we can get there from here, so remember this stop */
                    return maybeAns; 
                }
            }
        }
       return resultSoFar; 
    }
}

/* DFSDriver : String -> String -> SearchResult 
   Prepares the SearchResult passed to `DFS()` by adding the starting node to the path
*/
SearchResult Graph::DFSDriver(std::string src, std::string dest) 
{
    SearchResult resultSoFar = SearchResult();
    resultSoFar.addToPath(src, 0);  /* Don't forget where you came from */
    return DFS(src, dest, Vertices(), resultSoFar);  /* Invoke depth-first search algorithm */
}


int main()
{
    // Do nothing...
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
