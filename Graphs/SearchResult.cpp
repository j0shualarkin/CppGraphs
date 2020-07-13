#include "Vertex.cpp"
#include <iostream>
#include <string>

class SearchResult
{
private:
    bool found;
    Vertices path;
public:
    SearchResult();
    void addToPath(std::string src, int wgt);
    void show();
    Vertices getPath();
};

// Constructor, initial result is false and path is empty
SearchResult::SearchResult()
{
    found = false;
    path = Vertices();
}


/// <summary>
/// addToPath : String -> Int -> Void
/// updates the path field of the SearchResult to additionally hold the given node
/// </summary>
/// <param name="name"> identifier of vertex to be added </param>
/// <param name="wgt"> cost to reach this vertex </param>
void SearchResult::addToPath(std::string name, int wgt)
{
    path.addNode(name, wgt);
}

/// <summary>
/// Calls the path's show() method if a successful result was found
/// </summary>
void SearchResult::show()
{
    if (found)
    {
        path.show();
    }
    else
    {
        std::cout << "Result failed to find a path\n";
    }
}

Vertices SearchResult::getPath()
{
    return path;
}
