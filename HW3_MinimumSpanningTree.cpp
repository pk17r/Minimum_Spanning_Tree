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
#include "GeneralPrintFunctions.h"
#include "CityGraph.h"

using namespace std;

int main()
{
    GeneralPrintFunctions::PrintBox("Avg Path Length Using Dijkstras Algorithm");

    //test dataset
    CityGraph city_graph_object;

    //print results
    string avg_dist_string(6, '\0');
    auto written = snprintf(&avg_dist_string[0], avg_dist_string.size(), "%.2f", city_graph_object.avg_dist_);
    avg_dist_string.resize(written);
    string result_content = "Using Dijkstra's average distance: " + avg_dist_string;
    GeneralPrintFunctions::PrintBox("RESULTS", result_content);
    
    return 0;
}
