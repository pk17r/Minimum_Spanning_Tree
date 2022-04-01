#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
#include <list>
#include <string>

struct Edge
{
private:
    int node_A = -1;

    int node_B = -1;

    int distance = -1;

public:
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

    //making CityGraph class as friend of this struct so CityGraph can access ReadData and EraseReadData static functions
    friend class CityGraph;

    //defining a static read data function to be called from CityGraph class
    static int ReadData(std::string& data_file_name, std::list<Edge*>& edgeList);

    //static function to erase Edge data from memory
    static bool EraseReadData(std::list<Edge*>& edgeList);

};

#endif // !EDGE_H_