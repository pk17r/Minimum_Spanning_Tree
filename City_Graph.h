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
    CityGraph(std::string& data_file_name);

    //destructor
    ~CityGraph();

    int get_size_();

    void set_size_(int size);

    int GetNeighborDistance(int city_id, int neighbor_id);

    std::vector<Neighbor> GetNeighbors(int city_id);

private:
    bool** city_connectivity_matrix_;

    int** city_distance_matrix_;

    int size_ = -1;     //only set by set_size_() and called by get_size_()

    std::vector<Neighbor> closed_set_dijkstras;

    std::vector<Neighbor> closed_set_prims_mst;

    void InitializeCityMatrices();

    void PopulateCityMatrices(std::list<Edge*>& edgeList);

    void PrintEverythingToTerminal();

    void PrintCityGraphMatrix(bool print_connectivity_matrix);

    void DijkstrasAlgorithmImplementation();

    void PrimsMinimumSpanningTreeAlgorithmImplementation();

    //function to read Edge data from file
    int ReadData(std::string& data_file_name, std::list<Edge*>& edgeList);

    //function to erase read Edge data from memory
    void EraseReadData(std::list<Edge*>& edgeList);

};

#endif // CITY_GRAPH_H_