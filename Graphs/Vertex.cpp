// Joshua Larkin
// Implementing a linked list called Vertices, whose elements are called Vertex

#include <string>
#include <iostream>


class Vertices
{
private:
    struct Vertex
    {
        std::string name; // A vertex has an identifer
        int  weight;      // a cost to reach it 
        Vertex * next;    // and a pointer to another vertex (potentially null)
    };
    Vertex * head;  // Each class of Vertices has as pointer to the first element of the list 
   
public: // invokable methods on Vertices objects
    Vertices();
    bool isEmpty() const;
    void addNode(std::string name, int wgt); 
    std::string peek();
    bool contains(std::string key); 
    int length();
    void show();
    template<typename F>
    void traverse(F &const action); // TODO
    // void traverse(F const& action);
}; // end class Vertices 

// Constructor for new list of vertices, initially no elements so set head to be a null pointer
Vertices::Vertices() { head = nullptr; }

// isEmpty : Void -> Boolean
// the list is empty if the head is a null pointer, meaning no elements have been added 
bool Vertices::isEmpty() const { return head == nullptr; }

// addNode : String -> Int -> Void
// Creates a new head of a Vertex object with the given attributes and a pointer to the previous head
void Vertices::addNode(std::string name, int wgt)
{
    head = new Vertex{ name, wgt, head };
}

// peek :: Void -> String
// returns the 'name' attribute of the head node, unless the list is empty then return "\0"
std::string Vertices::peek() 
{ 
    return isEmpty() ? "\0" : head->name; 
}

void Vertices::traverse(F action)
{
    Vertex * ptr = head;
    while (ptr != nullptr)
    {
        action(ptr->name, ptr->weight);
        ptr = ptr->next;
    }

}

// contains : String -> Boolean
// follow the pointers thru the list and return true if any 'name' attribute matches the given string 
 bool Vertices::contains(std::string key) 
 { 
    /* traverse([key](std::string name, int wgt) { if (name == key) { return true; } });
     return false;
    */
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
   traverse([count]() mutable { ++count; });
   return count;
   /* Vertex * ptr = head;
   while (ptr != nullptr)
   {
       ++count;
       ptr = ptr->next;
   } 
   return count;
   */
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
