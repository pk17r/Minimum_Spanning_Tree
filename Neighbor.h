#ifndef NEIGHBOR_H_
#define NEIGHBOR_H_

#include <iostream>

struct Neighbor
{
    //Neighbor city indices will be whole numbers
    static const int kNullId = -1;

    static const int kOriginCityId = 0;

    int id = kNullId;         //origin city has id = 0
    
    int nearest_neighbor_id = kNullId;        //origin city has nearest_neighbor_id = kNullId
    
    int distance = -1;

    Neighbor(int id, int distance);
    
    Neighbor(int id, int nearest_neighbor_id, int distance);

    //friend allows the << operator to have access to information in the object so it can overload normal cout <<.
    //https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend std::ostream& operator<<(std::ostream& os, const Neighbor& city);

};

#endif // !NEIGHBOR_H_