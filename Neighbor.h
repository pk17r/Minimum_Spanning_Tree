#ifndef NEIGHBOR_H
#define NEIGHBOR_H

struct Neighbor
{
    int index = -1;
    int nearest_neighbor_index = -1;
    int distance = -1;
    //constructor
    Neighbor(int index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = -1;
        this->distance = distance;
    }
    //constructor
    Neighbor(int index, int nearest_neighbor_index, int distance)
    {
        this->index = index;
        this->nearest_neighbor_index = nearest_neighbor_index;
        this->distance = distance;
    }
};

#endif // !NEIGHBOR_H