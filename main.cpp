// 
// Minimum Spanning Tree using Prim's Algorithm and
// Dijkstra's Shortest Path Algorithm
// 
// C++ for C Programmers Part 1
// Week 4 Peer Graded Assignment
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

//function declerations
void print_program_greeting_box();

int main(int argc, char* argv[])
{
    //disable automatic cout flush to terminal
    ios::sync_with_stdio(false);
    setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);

    print_program_greeting_box();

    string data_file_name = "cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt";

    if (argc == 2)
    {
        cout << "Argument passed: " << argv[1] << '\n';
        if (string(argv[1]) == "test")
        {
            data_file_name = "testDataSet.txt";
            cout << "- Test data: https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/" << '\n';
        }
        else
            cout << "Unrecognized argument" << '\n';
    }
    cout << flush;

    //Initializing CityGraph class object, in whose constructor the program runs
    CityGraph city_graph_object(data_file_name);

    //print results of CityGraph

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
    
    vector<string> result_box_contents
    {
        "Input data file: " + data_file_name,
        "Prims's Minimum Spanning Tree Length: " + to_string(city_graph_object.total_dist_primsMst_),
        "Dijkstra's Algorithm Average Distance to Origin: " + float_to_formatted_string_lambda_fn(city_graph_object.avg_dist_dijkstras_),
        "",
    };
    result_box_contents.insert(result_box_contents.end(), city_graph_object.program_time_taken.begin(), city_graph_object.program_time_taken.end());

    //print results
    GeneralPrintFunctions::PrintBox("RESULTS", &result_box_contents);
    
    cout << flush;

    return 0;
}

void print_program_greeting_box()
{
    vector<string> contents
    {
        "- Pass a single argument 'test' to run test data",
        "",
        "Program Author: Prashant Kumar",
        "",
        "",
        "While making this program I learned how to / use / implement / learned about:",
        "",
        " - usage of new and delete to allocate heap memory",
        " - when a copy constructor is called",
        " - implementing a priority queue",
        " - lambda function usage",
        " - usage of functions from algorithm header file like insert, erase, copy",
        " - how to separate header and source files",
        " - how to separate program into separate files for every class and structure",
        " - use of static functions and variables. how to initialize static variables",
        " - useing static variables to note times each constructor is being called",
        " - learned about string class",
        " - overloading cout/ostream operator with class objects",
        " - usage of friend class",
        " - how to disable automatic cout flush to terminal",
        " - calling by value and reference",
        " - mapping processing time taken using chrono::high_resolution_clock",
        " - how to initialize a vector in multiple ways, vector insertion",
        " - how to use snprintf to format numbers",
        " - smartly formatting thousand separators to number strings",
        " - smartly creating one resizable print box and calling it with multiple ways",
        " - reading a data file using ifstream_iterator",
        " - abstracting functions and classes",
        " - overloading a function arg with template type - FormatSmallNumber function",
        " - how to neatly print stuff to represent data in understandable way",
        " - how to follow Google C++ Code Style for naming conventions on filenames,",
        "   variables, classes, structs, functions include statements, not having",
        "   namespace in header files, making header files self-sufficient",
        " - usage of pseudo code to code algorithms easily and correctly",
        " - encapsulation by making class and structure members public and private",
        " - how to correctly compile multiple files using g++",
        " - difference in print time of printf and cout",
        " - choosing unambigous variable, function and class, structure names",
        "",
        "",
    };

    //resizing every content string to largest string size to make print box look good
    int largest_string_size_in_contents = 0;
    for (int i = 0; i < static_cast<int>(contents.size()); i++)
        if (static_cast<int>(contents[i].size()) > largest_string_size_in_contents)
            largest_string_size_in_contents = static_cast<int>(contents[i].size());
    for (int i = 4; i < static_cast<int>(contents.size()); i++)
        contents[i].resize(largest_string_size_in_contents, ' ');

    GeneralPrintFunctions::PrintBox("Prim's MST and Dijkstra's Shortest Path Graph Algorithms", &contents, false, true);

}