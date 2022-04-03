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
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "City_Graph.h"
#include "General_Print_Functions.h"

using namespace std;

int main(int argc, char* argv[])
{
    //disable automatic cout flush to terminal
    ios::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);

    vector<string> contents
    {
        "- Pass a single argument 'test' to run test data",
        "Test data taken from www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5",
    };
    GeneralPrintFunctions::PrintBox("Graph Algorithms", &contents);

    string data_file_name = "cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt";

    if (argc == 2)
    {
        cout << "Argument passed: " << argv[1] << '\n';
        if (string(argv[1]) == "test")
            data_file_name = "testDataSet.txt";
        else
            cout << "Unrecognized argument" << '\n';
    }

    cout << flush;
    
    CityGraph city_graph_object(data_file_name);        //CityGraph object calling constructor which runs all program steps

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
        "Input data file: " + data_file_name,
        "Prims's Minimum Spanning Tree Length: " + to_string(city_graph_object.total_dist_primsMst_),
        "Dijkstra's Algorithm Average Distance to Origin: " + float_to_formatted_string_lambda_fn(city_graph_object.avg_dist_dijkstras_),
        "",
    };
    contents.insert(contents.end(), city_graph_object.program_time_taken.begin(), city_graph_object.program_time_taken.end());

    //print results
    GeneralPrintFunctions::PrintBox("RESULTS", &contents);
    
    cout << flush;

    return 0;
}
