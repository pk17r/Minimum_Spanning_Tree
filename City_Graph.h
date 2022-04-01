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
    float avg_dist_dijkstras_ = 0;

    int total_dist_primsMst_ = 0;

    //constructor
    CityGraph(const bool &kRunTestData);

    //destructor
    ~CityGraph();

    int get_size_();

    std::vector<Neighbor> GetNeighbors(int cityIndex);

    int GetNeighborDistance(int cityIndex, int neighborIndex);

    void DijkstrasAlgorithmImplementation();

    void PrimsMinimumSpanningTreeAlgorithmImplementation();

};

#endif // CITY_GRAPH_H_