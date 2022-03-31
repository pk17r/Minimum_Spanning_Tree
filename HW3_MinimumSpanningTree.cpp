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
//#include <stdio.h>
#include <limits>
#include "City_Graph.h"
#include "General_Print_Functions.h"
#include <string>

using namespace std;

int main()
{
    GeneralPrintFunctions::PrintBox("Graph Algorithms");

    const bool kRunTestData = false;

    //test dataset
    CityGraph city_graph_object(kRunTestData);
    
    //print results
    auto float_to_formatted_string_lambda_fn = [=](float avgDist)
    {
        const int kMaxDigits = 10;
        char avg_dist_formatted_char_array[kMaxDigits]; //giving max value avg_dist_formatted_char_array can carry to be 999999.99\0, thereby assuming upper limit of avgDist to be 999999.x
        int snprintf_ret_val = snprintf(avg_dist_formatted_char_array, kMaxDigits, "%.2f", avgDist);
        if(snprintf_ret_val < 0 || snprintf_ret_val > kMaxDigits)
            GeneralPrintFunctions::PrintErrorBox("ERROR", "Could not convert float to char array");
        return string(avg_dist_formatted_char_array);
    };
    string header = "Prims's Minimum Spanning Tree Length: " + to_string(city_graph_object.total_dist_primsMst_);
    string content = "Dijkstra's Algorithm Average Distance to Origin: " + float_to_formatted_string_lambda_fn(city_graph_object.avg_dist_dijkstras_);
    GeneralPrintFunctions::PrintBox(header, content);
    
    return 0;
}
