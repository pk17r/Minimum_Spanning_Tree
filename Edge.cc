#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include "Edge.h"
#include "General_Print_Functions.h"

using namespace std;

//initializing static members of struct Edge to zero
int Edge::times_Edge_default_constructor_is_called = 0;
int Edge::times_Edge_string_input_constructor_is_called = 0;
int Edge::times_Edge_copy_constructor_is_called = 0;
int Edge::times_Edge_default_destructor_is_called = 0;

//default constructor
Edge::Edge() { Edge::times_Edge_default_constructor_is_called++; }

//default destructor
Edge::~Edge() { Edge::times_Edge_default_destructor_is_called++; }

//constructor created to load data from string lines in input file
Edge::Edge(string& str)
{
    Edge::times_Edge_string_input_constructor_is_called++;
    /* Storing the whole string into string stream */
    stringstream ss;
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int int_found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> int_found)
        {
            if (node_A == -1) node_A = int_found;
            else if (node_B == -1) node_B = int_found;
            else if (distance == -1) distance = int_found;
            else
                GeneralPrintFunctions::PrintErrorBox("PROGRAMMING ERROR EDGE.CC STRING READ CONSTRUCTOR", "Edge Read int_found=" + to_string(int_found));
        }
        temp.clear();
    }
    //cout << "Edge(string &str)" << *this << endl;
}

//copy constructor, to keep track of unnecessary copies being created by program
//https://stackoverflow.com/questions/515071/destructor-called-on-object-when-adding-it-to-stdlist
Edge::Edge(Edge const& edge) : node_A(edge.node_A), node_B(edge.node_B), distance(edge.distance)
{
    Edge::times_Edge_copy_constructor_is_called++;
    cout << "Copy Constructor Edge(Edge const& edge)" << *this << '\n';
}

//friend allows the << operator to have access to information in the object so it can overload normal cout <<.
//https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
ostream& operator<<(ostream& os, const Edge& edge)
{
    os << "(" << edge.node_A << ", " << edge.node_B << ", " << edge.distance << ")";
    return os;
}
