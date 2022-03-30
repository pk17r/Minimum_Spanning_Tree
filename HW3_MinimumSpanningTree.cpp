// 
// C++ for C Programmers Part 1
// Week 4 Peer Graded Assignment Homework
//
// Minimum Spanning Tree Algorithm using Prim Algorithm
// 
//
// Prashant Kumar
// Mar 27th 2022
// 

#include <iostream>
#include <limits>
#include "GeneralPrintFunctions.h"
#include "CityGraph.h"

using namespace std;

int main()
{
    GeneralPrintFunctions::PrintBox("Avg Path Length Using Dijkstras Algorithm");

    //test dataset
    CityGraph city_graph_object;
    
    //print results
    auto float_to_formatted_string_lambda_fn = [=](float avg_dist)
    {
        char avg_dist_formatted_char_array[10]; //giving max value avg_dist_formatted_char_array can carry to be 999999.99\0, thereby assuming upper limit of avg_dist to be 999999.x
        if(sprintf_s(avg_dist_formatted_char_array, "%.2f", avg_dist) < 0)
            GeneralPrintFunctions::PrintErrorBox("ERROR", "Could not convert float to char array");
        return string(avg_dist_formatted_char_array);
    };
    GeneralPrintFunctions::PrintBox("RESULTS", "Using Dijkstra's average distance: " + string(float_to_formatted_string_lambda_fn(city_graph_object.avg_dist_)));
    
    return 0;
}
