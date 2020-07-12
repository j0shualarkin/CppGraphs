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
    Vertex * tail;  // And a pointer to the end of the list 
   
public: // invokable methods on Vertices objects
    Vertices();
    bool isEmpty();
    void addNodeFront(std::string name, int wgt); 
    void addNodeBack(std::string name, int wgt); 
    std::string peek();
    bool contains(std::string key); 
    int length();
    void append(Vertices vs); // TODO 3
    Vertex * popFront();
    void show();
}; // end class Vertices 

// Constructor for new list of vertices, initially no elements so set head to be a null pointer
Vertices::Vertices()
{ 
    head = nullptr; 
    tail = nullptr;
}

Vertex * popFront()
{
    if isEmpty() 
    {
        return head;
    }
    else
    {
        front = &Vertex{ head->name, head->wgt, nullptr };
        head = head->next;
        return front;
    }
}

// isEmpty : Void -> Boolean
// the list is empty if the head is a null pointer, meaning no elements have been added 
bool Vertices::isEmpty() { return head == nullptr; }

// addNodeFront : String -> Int -> Void
// Creates a new head of a Vertex object with the given attributes and a pointer to the previous head
void Vertices::addNodeFront(std::string name, int wgt)
{
    head = new Vertex{ name, wgt, head };
}

// addNodeBack : String -> Int -> Void
// Creates a new element at the end of the list 
void Vertices::addNodeBack(std::string name, int wgt)
{
    // not sure this is correct
    // does tail ever get updated when adding to front? 
    // if you follow the head do you eventually reach the tail?
    tail->next = new Vertex{ name, wgt, nullptr };
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

// append : Vertices -> Void 
void Vertices::append(Vertices vs)
{
    while !(vs.isEmpty())
    {
        Vertex * node = vs.popFront();
        addNodeBack(node->name, node->weight);
    }
}


// show : Void -> Void
// prints each vertex in the list 
void Vertices::show()
{
    Vertex * ptr = head;
    // std::cout << "Showing list:\n";
    while (ptr != nullptr)
    {
        std::cout << "[" << ptr->name << ", " << ptr->weight << "], ";
        ptr = ptr->next;
    } 
    std::cout << "[\\\\]\n";
}
