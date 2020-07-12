// Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Vertex.cpp"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Graph 
{
private:
    std::unordered_map<string, Vertices> *graph;

public:
    Graph()
    {
        graph = &(std::unordered_map<string, Vertices>{});
    }

    /* addEdge : String -> String -> Int -> Void
       adds a vertex with name 'dst' and weight 'wgt' to the neighbors of 'src' */
    void addEdge(string src, string dst, int wgt)
    {
        (*graph)[src].addNode(dst, wgt);
    }

    /* For adding a node that has no neighbors */
    void addNode(string src)
    {
        (*graph)[src] = Vertices();
    }
    
    /* getNeighbors : String -> [List Vertex] 
       returns a list of pairs of neighbors and the cost to reach them */
    Vertices getNeighbors(string src)
    {
        return (*graph)[src];
    }



};


int main()
{
    cout << "Hello World! Don't mind me!\n";
    Vertices test = Vertices();
    test.addNode("Sen's Fortress", 12);
    test.show();
    test.addNode("Anor Londo", 33);
    test.show();
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
