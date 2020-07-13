// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
// contains a Graph data structure and algorithms to use

#include "SearchResult.cpp"
#include <unordered_map>
#include <algorithm>

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
    void Dijkstra(std::string src);
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

class DState
{
    private:
        int  distance;
        bool permanent;
    public: 
        DState();
        int getDist();
        void updateDist(int amt);
        void markStart();
        bool isTemporary();
        void setPermanent();
};

DState::DState()
{
    distance = INFINITY;
    permanent = false;
}

void DState::setPermanent() { permanent = true; }
int DState::getDist() { return distance; }
void DState::updateDist(int amt) { distance = std::min(distance, amt); }
bool DState::isTemporary() { return !permanent; } 

void DState::markStart()
{
    distance = 0;
    permanent = true;
}


void Graph::Dijkstra(std::string src)
{
    // vertexStates is used to hold the information used by Dijkstra's algorithm
    std::unordered_map<std::string, DState> vertexStates =
        std::unordered_map<std::string, DState>{};
   
    // Initialization process
    for (auto pair : graph)
    {
        /* initialize all vertices to have infinite distance and label temporary  */
        vertexStates[pair.first] = DState();
        if (pair.first == src)
        {  /* starting node gets labeled permanent and has distance of 0*/
            vertexStates[pair.first].markStart(); 
        }
    }

    std::string current = src;
    
    Vertices reachable = getNeighbors(current);
    Vertices frontier = Vertices();

    Vertices visited = Vertices();
    Vertices queue = Vertices();
    queue.enqueue(current, 0);
    
    while (!queue.isEmpty()) 
    {
        Vertex * currentVertex = queue.pop();
        Vertices reachable = getNeighbors(currentVertex->name);
        while (!reachable.isEmpty())
        {
            Vertex * nextDoor = reachable.pop();
            DState nextDoorState = vertexStates[nextDoor->name];
            if (nextDoorState.isTemporary())
            {
                int newDist = nextDoor->weight + vertexStates[currentVertex->name].getDist();
                nextDoorState.updateDist(newDist);
                // frontier.addNode(nextDoor->name, newDist);
                Vertex * smallest = frontier.findSmallest();
                vertexStates[smallest->name].setPermanent();
                queue.enqueue(smallest->name, smallest->weight);
                // reachable.append(getNeighbors(current));
            }
        }
        // might need to consider if we've visited the node before?
    }
    
    // if all reachable nodes are permanent, stop
    // if we can't reach any temp node from current, done AND change all temp to permanent
   
}

int main()
{
    Graph test = Graph();
    test.addEdge("1", "6", 14);
	test.addEdge("1", "3", 9);
    test.addEdge("1", "2", 7);
    test.addEdge("2", "3", 10);
    test.addEdge("2", "4", 15);
    test.addEdge("3", "6", 2);
    test.addEdge("3", "4", 11);
    test.addEdge("4", "5", 6);
    test.addEdge("6", "5", 9);
    SearchResult res = test.BFSDriver("1", "5");
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
