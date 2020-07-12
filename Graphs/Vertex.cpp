#include <string>
#include <iostream>
/* Basic data structures... */


class Vertices
{
private:
    struct Vertex
    {
        std::string name;
        int  weight;
        Vertex * next;
    };

    Vertex * head;  // Each class of Vertices has as pointer to the first element of the list 
    
    // makeNode creates a Vertex struct holding the data passed 
    Vertex* makeNode(std::string name, int weight)
    {
        struct Vertex * fresh = (struct Vertex*)malloc(sizeof(struct Vertex));
        fresh->name   = name;
        fresh->weight = weight;
        fresh->next   = nullptr;
        return fresh;
    }
   
public:
    Vertices();
    bool isEmpty();
    void addNode(std::string name, int wgt); 
    std::string peek();
    bool contains(std::string key); 
    int length();
    void show();
}; // end class Vertices 

Vertices::Vertices() { head = nullptr; }

bool Vertices::isEmpty() { return head == nullptr; }
 
void Vertices::addNode(std::string name, int wgt)
{
    head = new Vertex{ name, wgt, head };
}

std::string Vertices::peek() 
{ 
    return isEmpty() ? "\0" : head->name; 
}

 bool Vertices::contains(std::string key) 
 { 
     Vertex * ptr = head;
     while (ptr != nullptr)
     {
         if (ptr->name == key)
         {
             return true; 
         }
         ptr = ptr->next;
     }
     return false;
 }

 // length :: Void -> Int
 // returns the amount of nodes in the list of vertices
int Vertices::length()
{
   int count = 0;
   Vertex * ptr = head;
   while (ptr != nullptr)
   {
       ++count;
       ptr = ptr->next;
   } 
   return count;
}
 
void Vertices::show()
{
    Vertex * ptr = head;
    std::cout << "Showing list:\n";
    while (ptr != nullptr)
    {
        std::cout << "\t" << "[" << ptr->name << "," << ptr->weight << "]\n";
        ptr = ptr->next;
    } 
    std::cout << "\t[\\\\]\n";
}
