#ifndef EDGE_H
#define EDGE_H

using namespace std;

struct Edge
{
private:
    int nodeA{ -1 };

    int nodeB{ -1 };

    int distance{ -1 };

public:
    //default constructor
    Edge();

    //constructor created to load data from string lines in input file
    Edge(string& str);

    //copy constructor, to keep track of unnecessary copies being created by program
    //https://stackoverflow.com/questions/515071/destructor-called-on-object-when-adding-it-to-stdlist
    Edge(Edge const& edge);

    ~Edge();

    //friend allows the << operator to have access to information in the object so it can overload normal cout <<.
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend ostream& operator<<(ostream& os, const Edge& edge)
    {
        os << "(" << edge.nodeA << ", " << edge.nodeB << ", " << edge.distance << ")";
        return os;
    }

    //making CityGraph class as friend of this struct so it can access ReadData and EraseReadData static functions
    friend class CityGraph;

    //defining a static read data function to be called from CityGraph class
    static int ReadData(string& data_file_name, list<Edge*>& edgeList);

    //static function to erase Edge data from memory
    static bool EraseReadData(list<Edge*>& edgeList);
};

#endif // !EDGE_H
