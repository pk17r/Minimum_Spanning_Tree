// 
// C++ for C Programmers Part 1
// Week 4 Peer Graded Assignment Homework
//
// Minimum Spanning Tree Algorithm using Prim Algorithm
// 
//
// Prashant Kumar
// Mar 27th 2022
// 

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <queue>
#include <time.h>
#include <sstream>
#include <list>

using namespace std;

//static variables
static int times_Edge_default_constructor_is_called = 0;
static int times_Edge_string_input_constructor_is_called = 0;
static int times_Edge_copy_constructor_is_called = 0;
static int times_Edge_default_destructor_is_called = 0;
static bool programming_error_found = false;

//struct declarations
struct Neighbor;

//function declarations
void PrintBox(const string &heading, const string &content);
void PrintAllCityDistanceAndPathsToOrigin(const string& heading, const vector<Neighbor>& closed_set, const float& avg_dist_);

struct Neighbor
{
    int index = -1;
    int nearest_neighbor_index = -1;
    int distance = -1;
    //constructor
    Neighbor(int index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = -1;
        this->distance = distance;
    }
    //constructor
    Neighbor(int index, int nearest_neighbor_index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = nearest_neighbor_index;
        this->distance = distance;
    }
};
struct Edge
{
    int nodeA{ -1 };

    int nodeB{ -1 };

    int distance{ -1 };

    //default constructor
    Edge()
    {
        times_Edge_default_constructor_is_called++;
        //cout << "~Edge" << *this << endl;
    }

    //constructor created to load data from string lines in input file
    Edge(string &str)
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
                if (nodeA == -1) nodeA = int_found;
                else if (nodeB == -1) nodeB = int_found;
                else if (distance == -1) distance = int_found;
                else
                {
                    cout << "PROGRAMMING ERROR #1: Edge Read int_found=" << int_found << endl;
                    programming_error_found = true;
                }
            }
            temp.clear();
        }
        //cout << "Edge(string &str)" << *this << endl;
    }

    //copy constructor, to keep track of unnecessary copies being created by program
    //https://stackoverflow.com/questions/515071/destructor-called-on-object-when-adding-it-to-stdlist
    Edge(Edge const& edge) : nodeA(edge.nodeA), nodeB(edge.nodeB), distance(edge.distance)
    {
        times_Edge_copy_constructor_is_called++;
        cout << "Copy Constructor Edge(Edge const& edge)" << *this << endl;
    }

    ~Edge()
    {
        times_Edge_default_destructor_is_called++;
        //cout << "~Edge" << *this << endl;
    }

    //friend allows the << operator to have access to information in the object so it can overload normal cout <<.
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend ostream& operator<<(ostream& os, const Edge& edge)
    {
        os << "(" << edge.nodeA << ", " << edge.nodeB << ", " << edge.distance << ")";
        return os;
    }

    friend class CityGraph; //making CityGraph class as friend of this struct

    //defining a static read data function to be called from CityGraph class
    static int ReadData(string& data_file_name, list<Edge*>& edgeList)
    {
        PrintBox("Read Data from File", "");
        cout << "Reading file: " << data_file_name << endl;
        ifstream dataFile(data_file_name);
        istreambuf_iterator<char> start_of_file(dataFile), end_of_file;
        string buffer;
        int graphSize = -1;
        while (start_of_file != end_of_file)
        {
            buffer += *start_of_file;
            if (*start_of_file == '\n')
            {
                if (graphSize == -1)
                    graphSize = stoi(buffer);
                else
                    edgeList.push_back(new Edge(buffer));
                buffer.clear();
            }
            ++start_of_file;
        }
        cout << "Graph Size: " << graphSize << endl;
        cout << "Size of edgeList: " << edgeList.size() << endl;
        cout << "First Edge: " << *edgeList.front() << endl;
        cout << "Last Edge: " << *edgeList.back() << endl;
        return graphSize;
    }

    //static function to erase Edge data from memory
    static void EraseReadData(list<Edge*>& edgeList)
    {
        for (auto edge : edgeList)
            delete edge;
        edgeList.clear();

        //a check for memory leaks and copy constructor calls
        if (times_Edge_default_destructor_is_called == times_Edge_string_input_constructor_is_called
            && times_Edge_default_constructor_is_called == 0
            && times_Edge_copy_constructor_is_called == 0)
            cout << "Data read from input file efficiently and read data container cleared without memory leaks" << endl;
        else
        {
            cout << "PROGRAMMING ERROR #2: Data NOT read from input file efficiently and read data container cleared without memory leaks" << endl;
            programming_error_found = true;
        }
    }
};

class CityGraph 
{
    bool** city_connectivity_matrix_;
    int** city_distance_matrix_;
    int size_ = -1;
    const int kmax_print_columns_to_show_per_page_ = 13;
    void InitializeCityMatrices()
    {
        //heap created 2D array of graph
        //allocate row pointers
        city_connectivity_matrix_ = new bool* [size_];
        city_distance_matrix_ = new int* [size_];
        //allocate column pointers
        for (int i = 0; i < size_; i++) {
            city_connectivity_matrix_[i] = new bool[size_];
            city_distance_matrix_[i] = new int[size_];
        }
        //initialize default values
        for (int i = 0; i < size_; i++)
            for (int j = 0; j < size_; j++)
            {
                city_connectivity_matrix_[i][j] = false;
                city_distance_matrix_[i][j] = 0;
            }
    }
    void PopulateCityMatrices(list<Edge*>& edgeList)
    {
        for (auto edge : edgeList)
        {
            city_connectivity_matrix_[edge->nodeA][edge->nodeB] = city_connectivity_matrix_[edge->nodeB][edge->nodeA] = 1;
            city_distance_matrix_[edge->nodeA][edge->nodeB] = city_distance_matrix_[edge->nodeB][edge->nodeA] = static_cast<int>(edge->distance);
        }
    }
public:
    float avg_dist_ = 0;
    //constructor
    CityGraph()
    {
        string data_file_name = "cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt";

        //read input file data into a temporary list
        list<Edge*> edgeList;
        this->size_ = Edge::ReadData(data_file_name, edgeList);

        //Initialize and populate matrices
        InitializeCityMatrices();
        PopulateCityMatrices(edgeList);

        //clear edgeList
        Edge::EraseReadData(edgeList);

        //print connectivity matrix
        PrintBox("Connectivity and Distance Matrices", "");
        PrintCityMatrixFn(true);
        PrintCityMatrixFn(false);

        //call avg distance to origin city method
        DijkstrasAlgorithmImplementation();
    }

    //destructor
    ~CityGraph() 
    {
        for (int i = 0; i < size_; i++) 
        {
            delete[] city_connectivity_matrix_[i];
            delete[] city_distance_matrix_[i];
        }
        delete[] city_connectivity_matrix_;
        delete[] city_distance_matrix_;

        cout << "City Graph with graphSize " << size_ << " deleted.\n" << endl;
    }

    void PrintCityMatrixFn(bool printConnectivityMatrix)
    {
        cout << (printConnectivityMatrix ? "Connectivity Matrix:\n\n" : "Distance Matrix:\n\n");

        int pages = size_ / kmax_print_columns_to_show_per_page_;
        for (int p = 0; p <= pages; p++)
        {
            cout << "Cities:\t";
            for (int i = p * kmax_print_columns_to_show_per_page_; i < min(size_, (p + 1) * kmax_print_columns_to_show_per_page_); i++)
                printf("|  %2d\t", i);
            cout << endl << "--------";
            for (int i = p * kmax_print_columns_to_show_per_page_; i < min(size_, (p + 1) * kmax_print_columns_to_show_per_page_); i++)
                cout << "|-------";
            cout << endl;
            for (int i = 0; i < size_; i++)
            {
                cout << "   " << i << "\t";
                for (int j = p * kmax_print_columns_to_show_per_page_; j < min(size_, (p + 1) * kmax_print_columns_to_show_per_page_); j++)
                {
                    cout << "|  ";
                    if (i == j)
                        printf(" -");
                    else if (city_connectivity_matrix_[i][j])
                        if(printConnectivityMatrix)
                            cout << " E";
                        else
                            printf("%2d", city_distance_matrix_[i][j]);
                    cout << "\t";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    int get_size_()
    {
        return this->size_;
    }

    vector<Neighbor> GetNeighbors(int cityIndex)
    {
        vector<Neighbor> neighborsList;
        for (int i = 0; i < size_; i++)
        {
            if (city_connectivity_matrix_[cityIndex][i])
            {
                Neighbor neighbor = Neighbor(i, city_distance_matrix_[cityIndex][i]);
                neighborsList.push_back(neighbor);
            }
        }
        return neighborsList;
    }

    int GetNeighborDistance(int cityIndex, int neighborIndex)
    {
        return city_distance_matrix_[cityIndex][neighborIndex];
    }

    void DijkstrasAlgorithmImplementation();
};

template <typename T>
void PrintOpenSet(T p)
{
    T q = p;
    cout << "Open Set: ";
    while (!q.empty())
    {
        cout << '\t' << static_cast<Neighbor>(q.top()).distance;
        q.pop();
    }
    cout << endl;
}

void CityGraph::DijkstrasAlgorithmImplementation()
{
    //define open set
    //using priority_queue to learn how to use it
    auto cmpFn = [](Neighbor left, Neighbor right) {return left.distance > right.distance; };
    priority_queue<Neighbor, vector<Neighbor>, decltype(cmpFn)> open_set(cmpFn);

    //define closed set
    vector<Neighbor> closed_set;

    //Step 1: add origin city to closed set
    closed_set.push_back(Neighbor(0, 0));

    //Step 2: add neighbors of origin city to open set
    vector<Neighbor> current_neighbors = this->GetNeighbors(0);
    for (Neighbor neighbor_city : current_neighbors)
    {
        neighbor_city.nearest_neighbor_index = 0;
        open_set.push(neighbor_city);
    }

    while (open_set.size() > 0)
    {
        //Step 3: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Neighbor current_city = open_set.top();
        open_set.pop();
        closed_set.push_back(current_city);

        //Step 4: for each neighbor city of current city which is not in closed set
        current_neighbors = this->GetNeighbors(current_city.index);
        for (Neighbor neighbor_city : current_neighbors)
        {
            bool found_neighbor_city_in_closed_set = false;
            for (auto iterator : closed_set)
                if (iterator.index == neighbor_city.index)
                {
                    found_neighbor_city_in_closed_set = true;
                    break;
                }

            if (!found_neighbor_city_in_closed_set)
            {
                //Step 4a: if neighbor city is in open set then update its distance in open set
                bool found_neighbor_city_in_open_set = false;
                vector<Neighbor> open_set_temp;
                while (!open_set.empty())
                {
                    Neighbor open_set_top = open_set.top();
                    if (open_set_top.index == neighbor_city.index)
                    {
                        found_neighbor_city_in_open_set = true;
                        if (current_city.distance + this->GetNeighborDistance(current_city.index, neighbor_city.index) < open_set_top.distance)
                        {
                            open_set_top.distance = current_city.distance + this->GetNeighborDistance(current_city.index, neighbor_city.index);
                            open_set_top.nearest_neighbor_index = current_city.index;
                        }
                    }
                    open_set_temp.push_back(open_set_top);
                    open_set.pop();
                }
                for (Neighbor open_set_temp_city : open_set_temp)
                    open_set.push(open_set_temp_city);

                //Step 4b: if did not find neighbor city in open set then add it to open set
                if (!found_neighbor_city_in_open_set)
                {
                    neighbor_city.nearest_neighbor_index = current_city.index;
                    neighbor_city.distance += current_city.distance;
                    open_set.push(neighbor_city);
                }
                //PrintOpenSet(open_set);
            }
        }
    }
    //dijkstras algoritm completed

    //calculate sum of distances of cities to origin city
    for (Neighbor city : closed_set)
        this->avg_dist_ += static_cast<float>(city.distance) / (closed_set.size() - 1);

    PrintAllCityDistanceAndPathsToOrigin("Dijkstras Algorithm Nearest City Paths and Distance to Origin", closed_set, this->avg_dist_);
}

void PrintAllCityDistanceAndPathsToOrigin(const string& heading, const vector<Neighbor> &closed_set, const float &avg_dist_)
{
    PrintBox(heading, "");

    cout << "##  ( City # | Shortest distance to origin city )  ->  Shortest Path" << endl;

    int cityCount = -1;
    for (Neighbor city : closed_set)
    {
        //print city and distance to origin
        ++cityCount;
        if (city.nearest_neighbor_index >= 0)
            printf("%2d  ( %3d | %2d )", cityCount, city.index, city.distance);
        else
        {
            printf("%2d  (  origin  )\n", cityCount);
            continue;
        }

        //print shortest path to origin city
        Neighbor nearest_city = city;
        do
        {
            for (Neighbor next_city : closed_set)
                if (next_city.index == nearest_city.nearest_neighbor_index)
                {
                    nearest_city = next_city;
                    break;
                }
            cout << "  ->  ";
            if (nearest_city.nearest_neighbor_index >= 0)
                printf("( %3d | %2d )", nearest_city.index, nearest_city.distance);
            else
                printf("(  origin  )");
        } while (nearest_city.nearest_neighbor_index >= 0);

        cout << endl;
    }
    cout << "\nconnected cities " << closed_set.size();
    printf(" | avg path length %0.2f\n\n", avg_dist_);
}

void PrintBox(const string &heading, const string &content)
{
    //making sure it is even number
    int headerSize = heading.size() + heading.size() % 2;
    int contentSize = content.size() + content.size() % 2;
    
    int boxContentSize = max(headerSize, contentSize);
    int sideBannerSize = 5;
    string borderLine = "*";
    string emptyLine = "*";
    for (int i = 0; i < sideBannerSize + boxContentSize + sideBannerSize; i++)
    {
        borderLine.append("*");
        emptyLine.append(" ");
    }
    borderLine.append("*");
    emptyLine.append("*");

    cout << endl << endl;
    cout << borderLine << endl;
    cout << emptyLine << endl;
    cout << "*";
    for (int i = 0; i < sideBannerSize + (boxContentSize - headerSize) / 2; i++) cout << " ";
    cout << heading << (heading.size() % 2 == 1 ? " " : "");
    for (int i = 0; i < sideBannerSize + (boxContentSize - headerSize) / 2; i++) cout << " ";
    cout << "*" << endl;
    cout << emptyLine << endl;
    if (content.size() > 0)
    {
        cout << "*";
        for (int i = 0; i < sideBannerSize + (boxContentSize - contentSize) / 2; i++) cout << " ";
        cout << content << (content.size() % 2 == 1 ? " " : "");;
        for (int i = 0; i < sideBannerSize + (boxContentSize - contentSize) / 2; i++) cout << " ";
        cout << "*" << endl;
        cout << emptyLine << endl;
    }
    cout << borderLine << endl;
    cout << endl;
}

int main()
{
    PrintBox("Avg Path Length Using Dijkstras Algorithm", "");

    //test dataset
    CityGraph city_graph_object;

    //print results
    string avg_dist_string(6, '\0');
    auto written = snprintf(&avg_dist_string[0], avg_dist_string.size(), "%.2f", city_graph_object.avg_dist_);
    avg_dist_string.resize(written);
    string result_content = "Using Dijkstra's average distance: " + avg_dist_string;
    PrintBox("RESULTS", result_content);
    
    if (programming_error_found)
        cout << "******** PROGRAMMING ERROR FOUND ********\n\n";

    return 0;
}

