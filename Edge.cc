#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include "Edge.h"
#include "General_Print_Functions.h"

using namespace std;

//static variables
static int times_Edge_default_constructor_is_called = 0;
static int times_Edge_string_input_constructor_is_called = 0;
static int times_Edge_copy_constructor_is_called = 0;
static int times_Edge_default_destructor_is_called = 0;

//default constructor
Edge::Edge() { times_Edge_default_constructor_is_called++; }

//default destructor
Edge::~Edge() { times_Edge_default_destructor_is_called++; }

//constructor created to load data from string lines in input file
Edge::Edge(string& str)
{
    times_Edge_string_input_constructor_is_called++;
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
    times_Edge_copy_constructor_is_called++;
    cout << "Copy Constructor Edge(Edge const& edge)" << *this << endl;
}

//friend allows the << operator to have access to information in the object so it can overload normal cout <<.
//https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
ostream& operator<<(ostream& os, const Edge& edge)
{
    os << "(" << edge.node_A << ", " << edge.node_B << ", " << edge.distance << ")";
    return os;
}

//defining a static read data function to be called from CityGraph class
int Edge::ReadData(string& data_file_name, list<Edge*>& edgeList)
{
    GeneralPrintFunctions::PrintBox("Read Data from File");
    cout << "Reading file: " << data_file_name << endl;
    ifstream dataFile(data_file_name);
    istreambuf_iterator<char> start_of_file(dataFile), end_of_file;
    string buffer;
    int graph_size = -1;
    while (start_of_file != end_of_file)
    {
        buffer += *start_of_file;
        if (*start_of_file == '\n')
        {
            if (graph_size == -1)
                graph_size = stoi(buffer);
            else
                edgeList.push_back(new Edge(buffer));
            buffer.clear();
        }
        ++start_of_file;
    }
    cout << "Graph Size: " << graph_size << endl;
    cout << "Size of edge_list: " << edgeList.size() << endl;
    cout << "First Edge: " << *edgeList.front() << endl;
    cout << "Last Edge: " << *edgeList.back() << endl;
    return graph_size;
}

//static function to erase Edge data from memory
void Edge::EraseReadData(list<Edge*>& edge_list)
{
    for (auto edge : edge_list)
        delete edge;

    edge_list.clear();

    //a check for memory leaks and copy constructor calls
    if (times_Edge_default_destructor_is_called == times_Edge_string_input_constructor_is_called
        && times_Edge_default_constructor_is_called == 0
        && times_Edge_copy_constructor_is_called == 0)
        cout << "Data read from input file efficiently and read data container cleared without memory leaks" << endl;
    else
        GeneralPrintFunctions::PrintErrorBox("PROGRAMMING ERROR in EDGE.CC", "Data NOT read from input file efficiently and read data container cleared without memory leaks");

}