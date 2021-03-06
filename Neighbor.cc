#include"Neighbor.h"

using namespace std;

//defining constructors here itself
Neighbor::Neighbor(int id, int distance)
{
    this->id = id;
    this->nearest_neighbor_id = kNullId;
    this->distance = distance;
}

Neighbor::Neighbor(int id, int nearest_neighbor_id, int distance)
{
    this->id = id;
    this->nearest_neighbor_id = nearest_neighbor_id;
    this->distance = distance;
}

//friend allows the << operator to have access to information in the object so it can overload normal cout <<.
//https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
std::ostream& operator<<(std::ostream& os, const Neighbor& city)
{
    if (city.nearest_neighbor_id >= 0)
    {
        char formatted_char_array[9];
        snprintf(formatted_char_array, 9, "(%2d |%2d)", city.id, city.distance);
        os << formatted_char_array;
    }
    else
        os << "(origin)";
    return os;
}
