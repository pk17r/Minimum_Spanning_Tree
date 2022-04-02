#ifndef CITY_GRAPH_H_
#define CITY_GRAPH_H_

#include <list>
#include <vector>
#include "Edge.h"
#include "Neighbor.h"

class CityGraph
{
    bool** city_connectivity_matrix_;

    int** city_distance_matrix_;

    int size_ = -1;

    void InitializeCityMatrices();

    void PopulateCityMatrices(std::list<Edge*>& edgeList);

    void PrintCityGraphMatrix(bool print_connectivity_matrix);

public:
    //constructor
    CityGraph(const bool &kRunTestData);

    //destructor
    ~CityGraph();

    int get_size_();

    std::vector<Neighbor> GetNeighbors(int cityIndex);

    int GetNeighborDistance(int cityIndex, int neighborIndex);

    void DijkstrasAlgorithmImplementation();

    void PrimsMinimumSpanningTreeAlgorithmImplementation();

    float avg_dist_dijkstras_ = 0;

    std::vector<Neighbor> closed_set_dijkstras;

    int total_dist_primsMst_ = 0;

    std::vector<Neighbor> closed_set_prims_mst;

    std::string file_read_time_str;
    std::string populate_matrices_and_clear_edgeList_time_str;
    std::string graph_algorithms_time_str;
    std::string print_to_terminal_time_str;
};

#endif // CITY_GRAPH_H_