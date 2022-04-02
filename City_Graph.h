#ifndef CITY_GRAPH_H_
#define CITY_GRAPH_H_

#include <list>
#include <vector>
#include "Edge.h"
#include "Neighbor.h"

class CityGraph
{
public:

    float avg_dist_dijkstras_ = 0;

    int total_dist_primsMst_ = 0;

    std::vector<std::string> program_time_taken;
    
    //constructor
    CityGraph(const bool& kRunTestData);

    //destructor
    ~CityGraph();

    int get_size_();

    int GetNeighborDistance(int cityIndex, int neighborIndex);

    std::vector<Neighbor> GetNeighbors(int cityIndex);

private:
    bool** city_connectivity_matrix_;

    int** city_distance_matrix_;

    int size_ = -1;

    std::vector<Neighbor> closed_set_dijkstras;

    std::vector<Neighbor> closed_set_prims_mst;

    void InitializeCityMatrices();

    void PopulateCityMatrices(std::list<Edge*>& edgeList);

    void PrintEverythingToTerminal();

    void PrintCityGraphMatrix(bool print_connectivity_matrix);

    void DijkstrasAlgorithmImplementation();

    void PrimsMinimumSpanningTreeAlgorithmImplementation();

};

#endif // CITY_GRAPH_H_