#ifndef EDGE_H_
#define EDGE_H_

#include <string>

struct Edge
{
public:
    int node_A = -1;

    int node_B = -1;

    int distance = -1;

    //static variables
    static int times_Edge_default_constructor_is_called;
    static int times_Edge_string_input_constructor_is_called;
    static int times_Edge_copy_constructor_is_called;
    static int times_Edge_default_destructor_is_called;

    Edge();

    ~Edge();

    //constructor created to load data from string lines in input file
    Edge(std::string& str);

    //copy constructor, to keep track of unnecessary copies being created by program
    //https://stackoverflow.com/questions/515071/destructor-called-on-object-when-adding-it-to-stdlist
    Edge(Edge const& edge);

    //friend allows the << operator to have access to information in the object so it can overload normal cout <<.
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge);

    //making CityGraph class as friend of this struct so CityGraph can access private members of this class - node_A, node_B and distance
    friend class CityGraph;

};

#endif // !EDGE_H_