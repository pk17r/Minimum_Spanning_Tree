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
#include <string>
#include "City_Graph.h"
#include "General_Print_Functions.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> contents
    {
        "- Pass a single argument 'test' to run test data",
        "Test data taken from www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5",
    };
    GeneralPrintFunctions::PrintBox("Graph Algorithms", &contents);

    bool run_test_data = false;
    if (argc == 2)
    {
        cout << "Argument passed: " << argv[1] << endl;
        if (string(argv[1]) == "test")
            run_test_data = true;
        else
            cout << "Unrecognized argument" << endl;
    }

    //CityGraph object calling explicitly defined constructor which runs all program steps
    CityGraph city_graph_object(run_test_data);

    //lambda function to print float as a formatted string
    auto float_to_formatted_string_lambda_fn = [](float avg_dist)
    {
        const int kMaxDigits = 10;

        char avg_dist_formatted_char_array[kMaxDigits]; //giving max value avg_dist_formatted_char_array can carry to be 999999.99\0, thereby assuming upper limit of avg_dist to be 999999.x
        
        int snprintf_ret_val = snprintf(avg_dist_formatted_char_array, kMaxDigits, "%.2f", avg_dist);
        
        if(snprintf_ret_val < 0 || snprintf_ret_val > kMaxDigits)
            GeneralPrintFunctions::PrintErrorBox("ERROR", "Could not convert float to char array");
        
        return string(avg_dist_formatted_char_array);
    };

    contents = vector<string>
    {
        "Prims's Minimum Spanning Tree Length: " + to_string(city_graph_object.total_dist_primsMst_),
        "Dijkstra's Algorithm Average Distance to Origin: " + float_to_formatted_string_lambda_fn(city_graph_object.avg_dist_dijkstras_),
        "",
        city_graph_object.file_read_time_str,
        city_graph_object.populate_matrices_and_clear_edgeList_time_str,
        city_graph_object.graph_algorithms_time_str,
        city_graph_object.print_to_terminal_time_str,
    };
    //print results
    GeneralPrintFunctions::PrintBox("RESULTS", &contents);
    
    return 0;
}
