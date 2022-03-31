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
#include <string>

using namespace std;

int main()
{
    GeneralPrintFunctions::PrintBox("Avg Path Length Using Dijkstras Algorithm");

    //test dataset
    CityGraph city_graph_object;
    
    //print results
    auto double_to_formatted_string_lambda_fn = [=](double double_value)
    {
        char double_value_formatted_char_array[10]; //giving max value double_value_formatted_char_array can carry to be 999999.99\0, thereby assuming upper limit of double_value to be 999999.x
        if(sprintf_s(double_value_formatted_char_array, "%.2f", double_value) < 0)
            GeneralPrintFunctions::PrintErrorBox("ERROR", "Could not convert float to char array");
        return string(double_value_formatted_char_array);
    };
    string avg_dist_string = double_to_formatted_string_lambda_fn(city_graph_object.total_dist_ / (city_graph_object.get_size_() - 1));
    string content_string = "Dijkstra's average double_value: " + avg_dist_string + " and total double_value: " + to_string(static_cast<int>(city_graph_object.total_dist_));
    GeneralPrintFunctions::PrintBox("RESULTS", content_string);
    
    return 0;
}
