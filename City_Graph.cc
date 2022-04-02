#include <algorithm>
#include <climits>
#include <chrono>
#include <cmath>
#include <inttypes.h>
#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <vector>
#include "Edge.h"
#include "Neighbor.h"
#include "City_Graph.h"
#include "My_Priority_Queue.h"
#include "General_Print_Functions.h"

using namespace std;
using namespace std::chrono;

void CityGraph::InitializeCityMatrices()
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

void CityGraph::PopulateCityMatrices(list<Edge*>& edgeList)
{
    for (auto &edge : edgeList)
    {
        city_connectivity_matrix_[edge->node_A][edge->node_B] = city_connectivity_matrix_[edge->node_B][edge->node_A] = 1;
        city_distance_matrix_[edge->node_A][edge->node_B] = city_distance_matrix_[edge->node_B][edge->node_A] = static_cast<int>(edge->distance);
    }
}

static string FormatThousandSeparators(string input_str)
{
    int digits = input_str.size();
    int counter = 1;
    reverse(input_str.begin(), input_str.end());
    //if (digits > 3)
    //    input_str.insert(3,",");
    //if (digits > 6)
    //    input_str.insert(7, ",");
    //
    while (digits > 3 * counter)
    {
        input_str.insert(3 * counter + counter - 1, ",");
        counter++;
    }
    input_str.resize(15, ' ');
    reverse(input_str.begin(), input_str.end());
    return input_str;
}

static string CalculateTimeTaken(string description, high_resolution_clock::time_point t0, high_resolution_clock::time_point t1)
{
    description.resize(50, ' ');
    description += ":";
    auto time_span = duration_cast<microseconds>(t1 - t0);
    double time_difference = static_cast<double>(time_span.count());
    const int digits_in_time = 15;
    char time_difference_char_arr[digits_in_time];
    snprintf(time_difference_char_arr, digits_in_time, "%.0f", time_difference);
    string time_difference_string(time_difference_char_arr);
    return description + FormatThousandSeparators(time_difference_string) + " microseconds";
}

//constructor
CityGraph::CityGraph(const bool& kRunTestData)
{
    string data_file_name;
    if(kRunTestData)
        data_file_name = "testDataSet.txt";
    else
        data_file_name = "cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt";

    auto start_timer = high_resolution_clock::now();    //clock time

    //read input file data into a temporary list
    list<Edge*> edgeList;
    this->size_ = Edge::ReadData(data_file_name, edgeList);

    //Initialize and populate matrices
    InitializeCityMatrices();
    PopulateCityMatrices(edgeList);

    //clear edgeList
    Edge::EraseReadData(edgeList);

    //clock time
    auto end_timer = high_resolution_clock::now();
    program_time_taken.push_back(CalculateTimeTaken("Input file read time", start_timer, end_timer));
    start_timer = high_resolution_clock::now();

    //call avg distance to origin city method
    DijkstrasAlgorithmImplementation();

    //call minimum spanning tree to origin city method
    PrimsMinimumSpanningTreeAlgorithmImplementation();

    //clock time
    end_timer = high_resolution_clock::now();
    program_time_taken.push_back(CalculateTimeTaken("Graph Algorithms with My Priority Queue time", start_timer, end_timer));
    start_timer = high_resolution_clock::now();

    PrintEverythingToTerminal();

    //clock time
    end_timer = high_resolution_clock::now();
    program_time_taken.push_back(CalculateTimeTaken("Print things to terminal time", start_timer, end_timer));
}

void CityGraph::PrintEverythingToTerminal()
{
    //print connectivity matrix
    GeneralPrintFunctions::PrintBox("Connectivity and Distance Matrices");
    PrintCityGraphMatrix(true);
    PrintCityGraphMatrix(false);

    GeneralPrintFunctions::PrintBox("Dijkstras Algorithm Nearest City Paths and Distance to Origin");
    cout << "##  ( City # | Shortest distance to origin city )  ->  Shortest Path to Origin City" << endl;
    GeneralPrintFunctions::PrintAllCityDistanceAndPathsToOrigin(this->closed_set_dijkstras);
    printf(" | avg city distance to origin city %0.2f \n\n", this->avg_dist_dijkstras_);

    GeneralPrintFunctions::PrintBox("Prim's Minimum Spanning Tree");
    cout << "Branch # ( City # | Edge Lenth )  ->  MST Branch" << endl;
    GeneralPrintFunctions::PrintMSTPathsToOrigin(this->closed_set_prims_mst);
    printf(" | total mst length %d\n\n", this->total_dist_primsMst_);

}

//destructor
CityGraph::~CityGraph()
{
    cout << "~CityGraph()" << endl;

    for (int i = 0; i < size_; i++)
    {
        delete[] city_connectivity_matrix_[i];
        delete[] city_distance_matrix_[i];
    }
    delete[] city_connectivity_matrix_;
    delete[] city_distance_matrix_;

    cout << "City Graph with graphSize " << size_ << " deleted.\n" << endl;
}

int CityGraph::get_size_()
{
    return this->size_;
}

static const int kMaxPrintColumnsToShowPerPage = 13;

void CityGraph::PrintCityGraphMatrix(bool print_connectivity_matrix)
{
    cout << (print_connectivity_matrix ? "Connectivity Matrix:\n\n" : "Distance Matrix:\n\n");

    int pages = size_ / kMaxPrintColumnsToShowPerPage;
    for (int p = 0; p <= pages; p++)
    {
        cout << "Cities:\t";
        for (int i = p * kMaxPrintColumnsToShowPerPage; i < min(size_, (p + 1) * kMaxPrintColumnsToShowPerPage); i++)
            printf("|  %2d\t", i);
        cout << endl << "--------";
        for (int i = p * kMaxPrintColumnsToShowPerPage; i < min(size_, (p + 1) * kMaxPrintColumnsToShowPerPage); i++)
            cout << "|-------";
        cout << endl;
        for (int i = 0; i < size_; i++)
        {
            cout << "   " << i << "\t";
            for (int j = p * kMaxPrintColumnsToShowPerPage; j < min(size_, (p + 1) * kMaxPrintColumnsToShowPerPage); j++)
            {
                cout << "|  ";
                if (i == j)
                    printf(" -");
                else if (city_connectivity_matrix_[i][j])
                {
                    if (print_connectivity_matrix)
                        cout << " E";
                    else
                        printf("%2d", city_distance_matrix_[i][j]);
                }
                cout << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
}

vector<Neighbor> CityGraph::GetNeighbors(int city_index)
{
    vector<Neighbor> neighbors_list;
    for (int i = 0; i < size_; i++)
    {
        if (city_connectivity_matrix_[city_index][i])
        {
            Neighbor neighbor = Neighbor(i, city_distance_matrix_[city_index][i]);
            neighbors_list.push_back(neighbor);
        }
    }
    return neighbors_list;
}

int CityGraph::GetNeighborDistance(int city_index, int neighbor_index)
{
    return city_distance_matrix_[city_index][neighbor_index];
}

void CityGraph::DijkstrasAlgorithmImplementation()
{
    //define open set. Defining my own priority queue list to learn how to use it
    MyPriorityQueue open_set;

    //define closed set
    vector<Neighbor>* closed_set_ptr = &(this->closed_set_dijkstras);

    //track cities put into closed set
    vector<bool> city_in_closed_set(this->get_size_(), false);

    //Step 1: add origin city to closed set
    closed_set_ptr->push_back(Neighbor(Neighbor::kOriginCityIndex, 0));
    city_in_closed_set[Neighbor::kOriginCityIndex] = true;

    //Step 2: add neighbors of origin city to open set
    vector<Neighbor> current_neighbors = this->GetNeighbors(Neighbor::kOriginCityIndex);
    for (Neighbor& neighbor_city : current_neighbors)
    {
        neighbor_city.nearest_neighbor_index = Neighbor::kOriginCityIndex;
        open_set.push(neighbor_city);
    }

    //loop over open set until it is empty
    while (open_set.size() > 0)
    {
        //Step 3: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Neighbor current_city = open_set.get_and_pop_top();

        closed_set_ptr->push_back(current_city);
        city_in_closed_set[current_city.index] = true;

        //Step 4: for each neighbor city of current city which is not in closed set
        current_neighbors = this->GetNeighbors(current_city.index);

        for (Neighbor neighbor_city : current_neighbors)
        {
            if (!city_in_closed_set[neighbor_city.index])
            {
                //Step 4a: if neighbor city is in open set and its distance to origin city through current city is lower than its current distance to origin city, then update its distance to origin city and nearest neighbor index in open set
                if (open_set.contains_index(neighbor_city.index))
                {
                    Neighbor* open_set_city_ptr = open_set.member_with_index(neighbor_city.index);
                    if (current_city.distance + this->GetNeighborDistance(current_city.index, neighbor_city.index) < open_set_city_ptr->distance)
                    {
                        open_set_city_ptr->distance = current_city.distance + this->GetNeighborDistance(current_city.index, neighbor_city.index);
                        open_set_city_ptr->nearest_neighbor_index = current_city.index;
                        open_set.sort();
                    }

                }
                else   //Step 4b: if did not find neighbor city in open set then add it to open set with nearest neighbor index as current city index
                {
                    neighbor_city.nearest_neighbor_index = current_city.index;
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
    vector<bool> city_in_closed_set(this->get_size_(), false);

    //Step 1: Add all cities to Open Set. Distances of every city except origin city to be INT_MAX and origin city's distance is 0.
    for (int id = Neighbor::kOriginCityIndex; id < this->get_size_(); id++)
        open_set.push(Neighbor(id, (id == Neighbor::kOriginCityIndex ? 0 : INT_MAX)));

    while (open_set.size() > 0)
    {
        //Step 2: move nearest city, which is the top member of open set, to closed set. Call it current city.
        Neighbor current_city = open_set.get_and_pop_top();

        closed_set_ptr->push_back(current_city);
        city_in_closed_set[current_city.index] = true;

        //Step 3: for each neighbor city of current city which is not in closed set
        vector<Neighbor> current_neighbors = this->GetNeighbors(current_city.index);

        for (Neighbor& neighbor_city : current_neighbors)
        {
            if (!city_in_closed_set[neighbor_city.index])
            {
                //Step 4a: if neighbor city is in open set and its distance with current city is lower than its distance with its current neighbor city, then update its nearest neighbor as current city and distance as well in open set
                if (open_set.contains_index(neighbor_city.index))
                {
                    Neighbor* open_set_city_ptr = open_set.member_with_index(neighbor_city.index);
                    if (this->GetNeighborDistance(current_city.index, neighbor_city.index) < open_set_city_ptr->distance)
                    {
                        open_set_city_ptr->distance = this->GetNeighborDistance(current_city.index, neighbor_city.index);
                        open_set_city_ptr->nearest_neighbor_index = current_city.index;
                        open_set.sort();
                    }
                }
                else   //Step 4b: if did not find neighbor city in open set then add this neighbor city to open set with nearest neighbor index as current city index
                {
                    neighbor_city.nearest_neighbor_index = current_city.index;
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