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
    SearchResult BFS(std::string src, std::string dest, Vertices visited, SearchResult resultSoFar);
    SearchResult BFSDriver(std::string src, std::string dest);
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

/************************************************************************************************************/

/* BFSDriver : String -> String -> SearchResult 
   Prepares the SearchResult passed to `BFS()` by adding the starting node to the path
*/
SearchResult Graph::BFSDriver(std::string src, std::string dest) 
{
    SearchResult resultSoFar = SearchResult();
    resultSoFar.addToPath(src, 0);  /* Don't forget where you came from */
    return BFS(src, dest, Vertices(), resultSoFar);  /* Invoke depth-first search algorithm */
}


// BFS  : String -> String -> Vertices -> SearchResult -> SearchResult
// uses a queue of nodes called `frontier` to search through 
// currently doesn't construct the correct path found, but does do BFS and searches correctly
//   this worked nicely in DFS because we could 'backtrack' with the recursion, but here we need
//   a way to annotate where a node came from when putting it into the frontier.
//     so it is convenient for frontier to be a list of vertices,
//     but perhaps a different data-structure is needed;
//   or a new approach in total
SearchResult Graph::BFS(std::string src, std::string dest, Vertices visitedSoFar, SearchResult resultSoFar)
{
    if (src == dest)
    {
        resultSoFar.pathFound();
        return resultSoFar;
    }
    else 
    {
        Vertices frontier = getNeighbors(src);
        visitedSoFar.addNode(src, 0);
        while (!frontier.isEmpty())
        {
            Vertex * node = frontier.pop();
            if (!visitedSoFar.contains(node->name)) /* don't do the same thing twice */
            {
                if (node->name == dest) // we found it!
                {
                    resultSoFar.addToPath(node->name, node->weight);
                    resultSoFar.pathFound();
                    return resultSoFar;
                }
                else
                { 
                    Vertices nearBy = getNeighbors(node->name);
                    frontier.append(nearBy);
                }
            }
        }
        return resultSoFar;
    }
}

int main()
{
    Graph test = Graph();
    test.addEdge("Start", "A", 7);
	test.addEdge("Start", "B", 9);
    test.addEdge("B", "E", 10);
    test.addEdge("A", "C", 3);
    test.addEdge("C", "D", 8);
    test.addEdge("D", "E", 5);
    SearchResult res = test.BFSDriver("Start", "E");
    res.show();
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
