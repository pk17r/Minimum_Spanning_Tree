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
#include "PrintFunctions.h"
#include "Edge.h"
#include "Neighbor.h"

using namespace std;

//static variables
static bool programming_error_found = false;

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
        programming_error_found = Edge::EraseReadData(edgeList);

        //print connectivity matrix
        PrintBox("Connectivity and Distance Matrices");
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

int main()
{
    PrintBox("Avg Path Length Using Dijkstras Algorithm");

    //test dataset
    CityGraph city_graph_object;

    //print results
    string avg_dist_string(6, '\0');
    auto written = snprintf(&avg_dist_string[0], avg_dist_string.size(), "%.2f", city_graph_object.avg_dist_);
    avg_dist_string.resize(written);
    string result_content = "Using Dijkstra's average distance: " + avg_dist_string;
    PrintBox("RESULTS", result_content);
    
    if (programming_error_found)
        PrintBox("PROGRAMMING ERROR FOUND", "Look deeper to know where", true);

    return 0;
}

