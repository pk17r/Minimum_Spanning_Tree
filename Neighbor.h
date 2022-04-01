#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_

#include <iostream>

struct Neighbor
{
    //Neighbor city indices will be whole numbers
    static const int kIndexNull = -1;

    static const int kOriginCityIndex = 0;

    int index = kIndexNull;         //origin city has index = 0
    
    int nearest_neighbor_index = kIndexNull;        //origin city has nearest_neighbor_index = kIndexNull
    
    int distance = -1;

    Neighbor(int index, int distance);
    
    Neighbor(int index, int nearest_neighbor_index, int distance);

    //friend allows the << operator to have access to information in the object so it can overload normal cout <<.
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend std::ostream& operator<<(std::ostream& os, const Neighbor& city);

};

#endif // !NEIGHBOR_H_