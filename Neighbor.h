#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_

struct Neighbor
{
    //Neighbor city indices will be whole numbers
    static const int kIndexNull = -1;

    int index = kIndexNull;
    
    int nearest_neighbor_index = kIndexNull;
    
    int distance = -1;

    //defining constructors here itself
    Neighbor(int index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = kIndexNull;
        this->distance = distance;
    }
    
    Neighbor(int index, int nearest_neighbor_index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = nearest_neighbor_index;
        this->distance = distance;
    }
};

#endif // !NEIGHBOR_H_