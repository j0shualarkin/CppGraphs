// Joshua Larkin
// Implementing a linked list called Vertices, whose elements are called Vertex

#include <string>
#include <iostream>

struct Vertex
{
    std::string name; // A vertex has an identifer
    int  weight;      // a cost to reach it 
    Vertex * next;    // and a pointer to another vertex (potentially null)
};

class Vertices
{
private:
    Vertex * head;  // Each class of Vertices has as pointer to the first element of the list 
   
public: // invokable methods on Vertices objects
    Vertices();
    bool isEmpty();
    void addNode(std::string name, int wgt); 
    void enqueue(std::string name, int wgt);
    std::string peek(); 
    bool contains(std::string key); 
    int length();
    Vertex * pop();
    void show();
    void append(Vertices vs);
    Vertex * findSmallest();
}; 

// Constructor for new list of vertices, initially no elements so set head to be a null pointer
Vertices::Vertices()
{ 
    head = nullptr; 
}

// findSmallest : Void -> String
// uses an accumulator to keep track of the node with the lowest weight seen while looking through the list
Vertex * Vertices::findSmallest()
{
    std::string smallestName = "\0";
    int smallestWeight = INFINITY;
    Vertex * ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->weight < smallestWeight)
        {
            smallestName   = ptr->name;
            smallestWeight = ptr->weight;
        }
        ptr = ptr->next;
    }
    return new Vertex{ smallestName, smallestWeight, nullptr };
}

// isEmpty : Void -> Boolean
// the list is empty if the head is a null pointer, meaning no elements have been added 
bool Vertices::isEmpty() { return head == nullptr; }

// pop : Void -> Vertex
// only called on nonempty Vertices, removes head element from list and returns head
Vertex * Vertices::pop()
{
    Vertex * elt = head;
    head = head->next;
    return elt;
}

// addNode : String -> Int -> Void
// Creates a new head of a Vertex object with the given attributes and a pointer to the previous head
void Vertices::addNode(std::string name, int wgt)
{
    head = new Vertex{ name, wgt, head };
}

// enqueue : String -> Int -> Void
// Creates a new Vertex node and inserts it at the end of the current list of Vertices
void Vertices::enqueue(std::string name, int wgt)
{
    if (head == nullptr)
    {
        addNode(name, wgt);
    }
    else 
    {
        Vertex * tmp = head;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new Vertex{ name, wgt, nullptr };
    }
}

// append : Vertices -> Void
// adds each of the vertex in the given list to the calling object's vertices
void Vertices::append(Vertices vs) 
{
    while (!vs.isEmpty())
    {
        Vertex * v = vs.pop();
        enqueue(v->name, v->weight);
    }
}

// peek :: Void -> String
// returns the 'name' attribute of the head node, unless the list is empty then return "\0"
std::string Vertices::peek() 
{ 
    return isEmpty() ? "\0" : head->name; 
}

// contains : String -> Boolean
// follow the pointers thru the list and return true if any 'name' attribute matches the given string 
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

// show : Void -> Void
// prints each vertex in the list on its own line
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
