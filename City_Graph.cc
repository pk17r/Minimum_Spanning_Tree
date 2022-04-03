#include <algorithm>
#include <climits>
#include <chrono>
#include <cmath>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <queue>
#include <sstream>
#include "City_Graph.h"
#include "My_Priority_Queue.h"
#include "General_Print_Functions.h"

using namespace std;
using namespace std::chrono;

//constructor
CityGraph::CityGraph(string &data_file_name)
{
    auto start_timer = high_resolution_clock::now();    //clock time

    //read input file data into a temporary list
    list<Edge*> edgeList;
    set_size_(ReadData(data_file_name, edgeList));

    //Initialize and populate matrices
    InitializeCityMatrices();
    PopulateCityMatrices(edgeList);

    //clear edgeList
    EraseReadData(edgeList);

    //clock time
    auto end_timer = high_resolution_clock::now();
    program_time_taken.push_back(GeneralPrintFunctions::CalculateTimeTaken("Input file read time", start_timer, end_timer));
    start_timer = high_resolution_clock::now();

    //call avg distance to origin city method
    DijkstrasAlgorithmImplementation();

    //call minimum spanning tree to origin city method
    PrimsMinimumSpanningTreeAlgorithmImplementation();

    //clock time
    end_timer = high_resolution_clock::now();
    program_time_taken.push_back(GeneralPrintFunctions::CalculateTimeTaken("Graph Algorithms with My Priority Queue time", start_timer, end_timer));
    start_timer = high_resolution_clock::now();

    PrintEverythingToTerminal();

    //clock time
    end_timer = high_resolution_clock::now();
    program_time_taken.push_back(GeneralPrintFunctions::CalculateTimeTaken("Print things to terminal time", start_timer, end_timer));
}

//destructor
CityGraph::~CityGraph()
{
    cout << "~CityGraph()" << '\n';

    for (int i = 0; i < get_size_(); i++)
    {
        delete[] city_connectivity_matrix_[i];
        delete[] city_distance_matrix_[i];
    }
    delete[] city_connectivity_matrix_;
    delete[] city_distance_matrix_;

    cout << "Heap allocated memory of City Graph with graphSize " << get_size_() << " deleted.\n" << endl;
}

int CityGraph::ReadData(string& data_file_name, list<Edge*>& edgeList)
{
    GeneralPrintFunctions::PrintBox("Read Data from File");

    cout << "Reading file: " << data_file_name << '\n';
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
    cout << "Graph Size: " << graph_size << '\n';
    cout << "Size of edge_list: " << edgeList.size() << '\n';
    cout << "First Edge: " << *edgeList.front() << '\n';
    cout << "Last Edge: " << *edgeList.back() << '\n';
    return graph_size;
}

void CityGraph::EraseReadData(list<Edge*>& edge_list)
{
    for (auto edge : edge_list)
        delete edge;

    edge_list.clear();

    //a check for memory leaks and copy constructor calls
    if (Edge::times_Edge_default_destructor_is_called == Edge::times_Edge_string_input_constructor_is_called
        && Edge::times_Edge_default_constructor_is_called == 0
        && Edge::times_Edge_copy_constructor_is_called == 0)
        cout << "Data read from input file efficiently and heap allocated memory cleared without memory leaks" << '\n';
    else
        GeneralPrintFunctions::PrintErrorBox("PROGRAMMING ERROR in EDGE.CC", "Data NOT read from input file efficiently and read data container cleared without memory leaks");

}

void CityGraph::InitializeCityMatrices()
{
    int size = get_size_();
    //heap created 2D array of graph
    //allocate row pointers
    city_connectivity_matrix_ = new bool* [size];
    city_distance_matrix_ = new int* [size];
    //allocate column pointers
    for (int id = 0; id < size; id++) {
        city_connectivity_matrix_[id] = new bool[size];
        city_distance_matrix_[id] = new int[size];
    }
    //initialize default values
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            city_connectivity_matrix_[i][j] = false;
            city_distance_matrix_[i][j] = 0;
        }
}

void CityGraph::PopulateCityMatrices(list<Edge*>& edgeList)
{
    for (auto& edge : edgeList)
    {
        city_connectivity_matrix_[edge->node_A][edge->node_B] = city_connectivity_matrix_[edge->node_B][edge->node_A] = 1;
        city_distance_matrix_[edge->node_A][edge->node_B] = city_distance_matrix_[edge->node_B][edge->node_A] = static_cast<int>(edge->distance);
    }
}

int CityGraph::get_size_()
{
    return this->size_;
}

void CityGraph::set_size_(int size)
{
    this->size_ = size;
}

void CityGraph::PrintEverythingToTerminal()
{
    //print connectivity matrix
    GeneralPrintFunctions::PrintBox("Connectivity and Distance Matrices");
    PrintCityGraphMatrix(true);
    PrintCityGraphMatrix(false);

    //print dijkstras output
    GeneralPrintFunctions::PrintBox("Dijkstras Algorithm Nearest City Paths and Distance to Origin");
    cout << "##  ( City # | Shortest distance to origin city )  ->  Shortest Path to Origin City" << '\n';
    GeneralPrintFunctions::PrintAllCityDistanceAndPathsToOrigin(this->closed_set_dijkstras);
    std::cout << " | avg city distance to origin city ";
    std::cout << GeneralPrintFunctions::FormatSmallNumber<float>("%0.2f", this->avg_dist_dijkstras_, 6);
    std::cout << '\n' << '\n';

    //print prims mst
    GeneralPrintFunctions::PrintBox("Prim's Minimum Spanning Tree");
    cout << "Branch # ( City # | Edge Lenth )  ->  MST Branch" << '\n';
    GeneralPrintFunctions::PrintMSTPathsToOrigin(this->closed_set_prims_mst);
    std::cout << " | total mst length ";
    std::cout << GeneralPrintFunctions::FormatSmallNumber<int>("%4d", this->total_dist_primsMst_, 6);
    std::cout << '\n' << '\n';

    cout << flush;   //to transfer cout stream output to terminal
}

static const int kMaxPrintColumnsToShowPerPage = 13;

void CityGraph::PrintCityGraphMatrix(bool print_connectivity_matrix)
{
    cout << (print_connectivity_matrix ? "Connectivity Matrix:\n\n" : "Distance Matrix:\n\n");

    int pages = get_size_() / kMaxPrintColumnsToShowPerPage;
    for (int p = 0; p <= pages; p++)
    {
        cout << "Cities:\t";
        for (int i = p * kMaxPrintColumnsToShowPerPage; i < min(get_size_(), (p + 1) * kMaxPrintColumnsToShowPerPage); i++)
            cout << "|  " << GeneralPrintFunctions::FormatSmallNumber<int>("%2d", i, 2) << '\t';
        cout << '\n' << "--------";
        for (int i = p * kMaxPrintColumnsToShowPerPage; i < min(get_size_(), (p + 1) * kMaxPrintColumnsToShowPerPage); i++)
            cout << "|-------";
        cout << '\n';
        for (int i = 0; i < get_size_(); i++)
        {
            cout << "   " << i << "\t";
            for (int j = p * kMaxPrintColumnsToShowPerPage; j < min(get_size_(), (p + 1) * kMaxPrintColumnsToShowPerPage); j++)
            {
                cout << "|  ";
                if (i == j)
                    cout << " -";
                else if (city_connectivity_matrix_[i][j])
                {
                    if (print_connectivity_matrix)
                        cout << " E";
                    else
                        cout << GeneralPrintFunctions::FormatSmallNumber<int>("%2d", city_distance_matrix_[i][j], 2);
                }
                cout << "\t";
            }
            cout << '\n';
        }
        cout << '\n';
    }
}

vector<Neighbor> CityGraph::GetNeighbors(int city_id)
{
    vector<Neighbor> neighbors_list;
    for (int id = 0; id < get_size_(); id++)
    {
        if (city_connectivity_matrix_[city_id][id])
        {
            Neighbor neighbor = Neighbor(id, city_distance_matrix_[city_id][id]);
            neighbors_list.push_back(neighbor);
        }
    }
    return neighbors_list;
}

int CityGraph::GetNeighborDistance(int city_id, int neighbor_id)
{
    return city_distance_matrix_[city_id][neighbor_id];
}

void CityGraph::DijkstrasAlgorithmImplementation()
{
    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    vector<Neighbor>* closed_set_ptr = &(this->closed_set_dijkstras);

    //track cities put into closed set
    vector<bool> city_in_closed_set(get_size_(), false);

    //Step 1: add origin city to closed set
    closed_set_ptr->push_back(Neighbor(Neighbor::kOriginCityId, 0));
    city_in_closed_set[Neighbor::kOriginCityId] = true;

    //Step 2: add neighbors of origin city to open set
    vector<Neighbor> current_neighbors = GetNeighbors(Neighbor::kOriginCityId);
    for (Neighbor& neighbor_city : current_neighbors)
    {
        neighbor_city.nearest_neighbor_id = Neighbor::kOriginCityId;
        open_set.push(neighbor_city);
    }

    //loop over open set until it is empty
    while (open_set.size() > 0)
    {
        //Step 3: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Neighbor current_city = open_set.get_and_pop_top();

        closed_set_ptr->push_back(current_city);
        city_in_closed_set[current_city.id] = true;

        //Step 4: for each neighbor city of current city which is not in closed set
        current_neighbors = GetNeighbors(current_city.id);

        for (Neighbor neighbor_city : current_neighbors)
        {
            if (!city_in_closed_set[neighbor_city.id])
            {
                //Step 4a: if neighbor city is in open set and its distance to origin city through current city is lower than its current distance to origin city, then update its distance to origin city and nearest neighbor id in open set
                if (open_set.contains_id(neighbor_city.id))
                {
                    Neighbor* open_set_city_ptr = open_set.member_with_id(neighbor_city.id);
                    if (current_city.distance + GetNeighborDistance(current_city.id, neighbor_city.id) < open_set_city_ptr->distance)
                    {
                        open_set_city_ptr->distance = current_city.distance + GetNeighborDistance(current_city.id, neighbor_city.id);
                        open_set_city_ptr->nearest_neighbor_id = current_city.id;
                        open_set.sort();
                    }

                }
                else   //Step 4b: if did not find neighbor city in open set then add it to open set with nearest neighbor id as current city id
                {
                    neighbor_city.nearest_neighbor_id = current_city.id;
                    neighbor_city.distance += current_city.distance;
                    open_set.push(neighbor_city);
                }
                //open_set.print();
            }
        }
    }
    //dijkstras algoritm completed

    //calculate sum of distances of cities to origin city
    for (Neighbor &city : *closed_set_ptr)
        this->avg_dist_dijkstras_ += static_cast<float>(city.distance) / (closed_set_ptr->size() - 1);

}

void CityGraph::PrimsMinimumSpanningTreeAlgorithmImplementation()
{
    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    vector<Neighbor>* closed_set_ptr = &(this->closed_set_prims_mst);

    //track cities put into closed set
    vector<bool> city_in_closed_set(get_size_(), false);

    //Step 1: Add all cities to Open Set. Distances of every city except origin city to be INT_MAX and origin city's distance is 0.
    for (int id = Neighbor::kOriginCityId; id < get_size_(); id++)
        open_set.push(Neighbor(id, (id == Neighbor::kOriginCityId ? 0 : INT_MAX)));

    while (open_set.size() > 0)
    {
        //Step 2: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Neighbor current_city = open_set.get_and_pop_top();

        closed_set_ptr->push_back(current_city);
        city_in_closed_set[current_city.id] = true;

        //Step 3: for each neighbor city of current city which is not in closed set
        vector<Neighbor> current_neighbors = GetNeighbors(current_city.id);

        for (Neighbor& neighbor_city : current_neighbors)
        {
            if (!city_in_closed_set[neighbor_city.id])
            {
                //Step 4a: if neighbor city is in open set and its distance with current city is lower than its distance with its current neighbor city, then update its nearest neighbor as current city and distance as well in open set
                if (open_set.contains_id(neighbor_city.id))
                {
                    Neighbor* open_set_city_ptr = open_set.member_with_id(neighbor_city.id);
                    if (GetNeighborDistance(current_city.id, neighbor_city.id) < open_set_city_ptr->distance)
                    {
                        open_set_city_ptr->distance = GetNeighborDistance(current_city.id, neighbor_city.id);
                        open_set_city_ptr->nearest_neighbor_id = current_city.id;
                        open_set.sort();
                    }
                }
                else   //Step 4b: if did not find neighbor city in open set then add this neighbor city to open set with nearest neighbor id as current city id
                {
                    neighbor_city.nearest_neighbor_id = current_city.id;
                    open_set.push(neighbor_city);
                }
                //PrintOpenSet(open_set);
            }
        }
    }
    //prim's algoritm completed

    //calculate sum of edges of MST
    for (Neighbor& city : *closed_set_ptr)
        this->total_dist_primsMst_ += city.distance;

}