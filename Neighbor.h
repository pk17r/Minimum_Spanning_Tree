#ifndef NEIGHBOR_H_INCLUDED
#define NEIGHBOR_H_INCLUDED

struct Neighbor
{
    int index = -1;
    
    int nearest_neighbor_index = -1;
    
    int distance = -1;

    //defining constructors here itself

    Neighbor(int index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = -1;
        this->distance = distance;
    }
    
    Neighbor(int index, int nearest_neighbor_index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = nearest_neighbor_index;
        this->distance = distance;
    }
};

#endif // !NEIGHBOR_H_INCLUDED