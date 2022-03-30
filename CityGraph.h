#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <list>
#include <vector>
#include "Edge.h"
#include "Neighbor.h"

class CityGraph
{
    bool** city_connectivity_matrix_;

    int** city_distance_matrix_;

    int size_ = -1;

    const int kmax_print_columns_to_show_per_page_ = 13;

    void InitializeCityMatrices();

    void PopulateCityMatrices(list<Edge*>& edgeList);

public:
    float avg_dist_ = 0;

    //constructor
    CityGraph();

    //destructor
    ~CityGraph();

    int get_size_();

    vector<Neighbor> GetNeighbors(int cityIndex);

    int GetNeighborDistance(int cityIndex, int neighborIndex);

    void DijkstrasAlgorithmImplementation();

    //making GeneralPrintFunctions as a friend class so it can access private matrices of this class for printing them
    friend class GeneralPrintFunctions;
};

#endif // CITY_GRAPH_H