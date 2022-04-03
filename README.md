<b>Graph implementations of 
Minimum Spanning Tree using Prim's Algorithm and
Dijkstra's Shortest Path Algorithm

Program made as part of
Coursera C++ for C Programmers Part 1 Course Homework</b>

Compile using
g++ -Wall -g *.cpp *.cc -o main

Arguments accepted:
test - to use test dataset.

Program output on Windows 10 machine:


******************************************************************************************
*                                                                                        *
*                Prim's MST and Dijkstra's Shortest Path Graph Algorithms                *
*                                                                                        *
*                    - Pass a single argument 'test' to run test data                    *
*                                                                                        *
*                             Program Author: Prashant Kumar                             *
*                                                                                        *
*                                                                                        *
*     While making this program I learned how to / use / implement / learned about:      *
*                                                                                        *
*      - usage of new and delete to allocate heap memory                                 *
*      - when a copy constructor is called                                               *
*      - implementing a priority queue                                                   *
*      - lambda function usage                                                           *
*      - usage of functions from algorithm header file like insert, erase, copy          *
*      - how to separate header and source files                                         *
*      - how to separate program into separate files for every class and structure       *
*      - use of static functions and variables. how to initialize static variables       *
*      - useing static variables to note times each constructor is being called          *
*      - learned about string class                                                      *
*      - overloading cout/ostream operator with class objects                            *
*      - usage of friend class                                                           *
*      - how to disable automatic cout flush to terminal                                 *
*      - calling by value and reference                                                  *
*      - mapping processing time taken using chrono::high_resolution_clock               *
*      - how to initialize a vector in multiple ways, vector insertion                   *
*      - how to use snprintf to format numbers                                           *
*      - smartly formatting thousand separators to number strings                        *
*      - smartly creating one resizable print box and calling it with multiple ways      *
*      - reading a data file using ifstream_iterator                                     *
*      - abstracting functions and classes                                               *
*      - overloading a function arg with template type - FormatSmallNumber function      *
*      - how to neatly print stuff to represent data in understandable way               *
*      - how to follow Google C++ Code Style for naming conventions on filenames,        *
*        variables, classes, structs, functions include statements, not having           *
*        namespace in header files, making header files self-sufficient                  *
*      - usage of pseudo code to code algorithms easily and correctly                    *
*      - encapsulation by making class and structure members public and private          *
*      - how to correctly compile multiple files using g++                               *
*      - difference in print time of printf and cout                                     *
*      - choosing unambigous variable, function and class, structure names               *
*                                                                                        *
*                                                                                        *
******************************************************************************************



********************************
*                              *
*     Read Data from File      *
*                              *
********************************

Reading file: cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt
Graph Size: 20
Size of edge_list: 344
First Edge: (0, 1, 17)
Last Edge: (19, 18, 11)
Data read from input file efficiently and heap allocated memory cleared without memory leaks


**********************************************
*                                            *
*     Connectivity and Distance Matrices     *
*                                            *
**********************************************

Connectivity Matrix:

Cities: |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |  10   |  11   |  12
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------
   0    |   -   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   1    |   E   |   -   |   E   |   E   |       |   E   |   E   |       |   E   |   E   |   E   |   E   |   E
   2    |   E   |   E   |   -   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   3    |   E   |   E   |   E   |   -   |   E   |       |   E   |   E   |   E   |   E   |       |   E   |   E
   4    |   E   |       |   E   |   E   |   -   |   E   |       |   E   |   E   |   E   |       |   E   |   E
   5    |   E   |   E   |   E   |       |   E   |   -   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   6    |   E   |   E   |   E   |   E   |       |   E   |   -   |       |   E   |   E   |       |   E   |   E
   7    |   E   |       |   E   |   E   |   E   |   E   |       |   -   |   E   |   E   |   E   |   E   |
   8    |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   -   |   E   |   E   |   E   |   E
   9    |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   -   |       |   E   |   E
   10   |   E   |   E   |   E   |       |       |   E   |       |   E   |   E   |       |   -   |       |   E
   11   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |       |   -   |   E
   12   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |       |   E   |   E   |   E   |   E   |   -
   13   |   E   |   E   |       |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |       |   E
   14   |   E   |       |   E   |       |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   15   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   16   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   17   |   E   |   E   |   E   |   E   |       |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   18   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   19   |   E   |   E   |   E   |   E   |   E   |   E   |       |   E   |       |   E   |   E   |   E   |   E

Cities: |  13   |  14   |  15   |  16   |  17   |  18   |  19
--------|-------|-------|-------|-------|-------|-------|-------
   0    |   E   |   E   |   E   |   E   |   E   |   E   |   E
   1    |   E   |       |   E   |   E   |   E   |   E   |   E
   2    |       |   E   |   E   |   E   |   E   |   E   |   E
   3    |   E   |       |   E   |   E   |   E   |   E   |   E
   4    |   E   |   E   |   E   |   E   |       |   E   |   E
   5    |   E   |   E   |   E   |   E   |   E   |   E   |   E
   6    |   E   |   E   |   E   |   E   |   E   |   E   |
   7    |   E   |   E   |   E   |   E   |   E   |   E   |   E
   8    |   E   |   E   |   E   |   E   |   E   |   E   |
   9    |   E   |   E   |   E   |   E   |   E   |   E   |   E
   10   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   11   |       |   E   |   E   |   E   |   E   |   E   |   E
   12   |   E   |   E   |   E   |   E   |   E   |   E   |   E
   13   |   -   |   E   |   E   |   E   |   E   |   E   |   E
   14   |   E   |   -   |   E   |   E   |   E   |   E   |   E
   15   |   E   |   E   |   -   |   E   |   E   |   E   |   E
   16   |   E   |   E   |   E   |   -   |   E   |   E   |   E
   17   |   E   |   E   |   E   |   E   |   -   |   E   |   E
   18   |   E   |   E   |   E   |   E   |   E   |   -   |   E
   19   |   E   |   E   |   E   |   E   |   E   |   E   |   -

Distance Matrix:

Cities: |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |  10   |  11   |  12
--------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------
   0    |   -   |  17   |   2   |   9   |  24   |  28   |  29   |  14   |  28   |  13   |  23   |  10   |  15
   1    |  17   |   -   |   9   |   3   |       |  14   |   1   |       |  27   |  20   |  16   |  24   |  29
   2    |   2   |   9   |   -   |  21   |  21   |  29   |  13   |  19   |  16   |   1   |  11   |   4   |  12
   3    |   9   |   3   |  21   |   -   |  11   |       |  22   |  22   |  12   |  16   |       |  22   |   1
   4    |  24   |       |  21   |  11   |   -   |  25   |       |   1   |   1   |   5   |       |  24   |  29
   5    |  28   |  14   |  29   |       |  25   |   -   |   1   |  17   |  22   |   7   |  20   |   7   |  22
   6    |  29   |   1   |  13   |  22   |       |   1   |   -   |       |  18   |   7   |       |   4   |  18
   7    |  14   |       |  19   |  22   |   1   |  17   |       |   -   |  27   |   7   |   2   |   5   |
   8    |  28   |  27   |  16   |  12   |   1   |  22   |  18   |  27   |   -   |   3   |   3   |  26   |   9
   9    |  13   |  20   |   1   |  16   |   5   |   7   |   7   |   7   |   3   |   -   |       |  23   |   3
   10   |  23   |  16   |  11   |       |       |  20   |       |   2   |   3   |       |   -   |       |  27
   11   |  10   |  24   |   4   |  22   |  24   |   7   |   4   |   5   |  26   |  23   |       |   -   |   1
   12   |  15   |  29   |  12   |   1   |  29   |  22   |  18   |       |   9   |   3   |  27   |   1   |   -
   13   |  23   |   6   |       |  12   |   9   |  16   |  11   |  29   |  25   |   3   |  13   |       |  23
   14   |  15   |       |  26   |       |   4   |  11   |  14   |  16   |  16   |  28   |  25   |   1   |   6
   15   |  18   |  15   |   5   |  14   |   2   |  22   |   5   |  25   |   7   |  24   |   2   |  20   |   9
   16   |  11   |  20   |  25   |  15   |   5   |   2   |  24   |   8   |   4   |  12   |   3   |  20   |  28
   17   |   4   |   1   |  12   |  23   |       |  23   |   5   |  19   |  23   |  20   |   4   |  22   |   1
   18   |  27   |  11   |   5   |  27   |  10   |   1   |  13   |  26   |   7   |  25   |   4   |  19   |   6
   19   |   5   |   9   |  24   |  28   |  10   |  20   |       |  23   |       |  25   |  15   |  28   |  13

Cities: |  13   |  14   |  15   |  16   |  17   |  18   |  19
--------|-------|-------|-------|-------|-------|-------|-------
   0    |  23   |  15   |  18   |  11   |   4   |  27   |   5
   1    |   6   |       |  15   |  20   |   1   |  11   |   9
   2    |       |  26   |   5   |  25   |  12   |   5   |  24
   3    |  12   |       |  14   |  15   |  23   |  27   |  28
   4    |   9   |   4   |   2   |   5   |       |  10   |  10
   5    |  16   |  11   |  22   |   2   |  23   |   1   |  20
   6    |  11   |  14   |   5   |  24   |   5   |  13   |
   7    |  29   |  16   |  25   |   8   |  19   |  26   |  23
   8    |  25   |  16   |   7   |   4   |  23   |   7   |
   9    |   3   |  28   |  24   |  12   |  20   |  25   |  25
   10   |  13   |  25   |   2   |   3   |   4   |   4   |  15
   11   |       |   1   |  20   |  20   |  22   |  19   |  28
   12   |  23   |   6   |   9   |  28   |   1   |   6   |  13
   13   |   -   |   5   |  19   |  18   |   4   |  16   |  12
   14   |   5   |   -   |   6   |  27   |  15   |   1   |  28
   15   |  19   |   6   |   -   |  23   |  21   |  28   |   2
   16   |  18   |  27   |  23   |   -   |   9   |  11   |  12
   17   |   4   |  15   |  21   |   9   |   -   |  20   |   9
   18   |  16   |   1   |  28   |  11   |  20   |   -   |  11
   19   |  12   |  28   |   2   |  12   |   9   |  11   |   -



**************************************************************************
*                                                                        *
*     Dijkstras Algorithm Nearest City Paths and Distance to Origin      *
*                                                                        *
**************************************************************************

##  ( City # | Shortest distance to origin city )  ->  Shortest Path to Origin City

 1  (origin)
 2  ( 2 | 2) -> (origin)
 3  ( 9 | 3) -> ( 2 | 2) -> (origin)
 4  (17 | 4) -> (origin)
 5  (19 | 5) -> (origin)
 6  ( 1 | 5) -> (17 | 4) -> (origin)
 7  (12 | 5) -> (17 | 4) -> (origin)
 8  (11 | 6) -> ( 2 | 2) -> (origin)
 9  ( 8 | 6) -> ( 9 | 3) -> ( 2 | 2) -> (origin)
10  (13 | 6) -> ( 9 | 3) -> ( 2 | 2) -> (origin)
11  ( 6 | 6) -> ( 1 | 5) -> (17 | 4) -> (origin)
12  ( 3 | 6) -> (12 | 5) -> (17 | 4) -> (origin)
13  (15 | 7) -> ( 2 | 2) -> (origin)
14  (18 | 7) -> ( 2 | 2) -> (origin)
15  (14 | 7) -> (11 | 6) -> ( 2 | 2) -> (origin)
16  ( 4 | 7) -> ( 8 | 6) -> ( 9 | 3) -> ( 2 | 2) -> (origin)
17  ( 5 | 7) -> ( 6 | 6) -> ( 1 | 5) -> (17 | 4) -> (origin)
18  (10 | 8) -> (17 | 4) -> (origin)
19  ( 7 | 8) -> ( 4 | 7) -> ( 8 | 6) -> ( 9 | 3) -> ( 2 | 2) -> (origin)
20  (16 | 9) -> ( 5 | 7) -> ( 6 | 6) -> ( 1 | 5) -> (17 | 4) -> (origin)

connected cities 20 | avg city distance to origin city 6.00



****************************************
*                                      *
*     Prim's Minimum Spanning Tree     *
*                                      *
****************************************

Branch # ( City # | Edge Lenth )  ->  MST Branch

 1  (16 | 2) -> ( 5 | 1) -> (18 | 1) -> (14 | 1) -> (11 | 1) -> (12 | 3) -> ( 9 | 1) -> ( 2 | 2) -> (origin)
 2  (10 | 2) -> ( 7 | 1) -> ( 4 | 1) -> ( 8 | 3) -> ( 9 )
 3  ( 6 | 1) -> ( 1 | 1) -> (17 | 1) -> (12 )
 4  (19 | 2) -> (15 | 2) -> ( 4 )
 5  ( 3 | 1) -> (12 )
 6  (13 | 3) -> ( 9 )

connected cities 20 | total mst length   30



********************************************************************************************
*                                                                                          *
*                                         RESULTS                                          *
*                                                                                          *
*       Input data file: cplusplus4c_homeworks_Homework3_SampleTestData_mst_data.txt       *
*                                                                                          *
*                         Prims's Minimum Spanning Tree Length: 30                         *
*                                                                                          *
*                  Dijkstra's Algorithm Average Distance to Origin: 6.00                   *
*                                                                                          *
*                                                                                          *
*                                                                                          *
*     Input file read time                              :         16,643 microseconds      *
*                                                                                          *
*     Graph Algorithms with My Priority Queue time      :          1,704 microseconds      *
*                                                                                          *
*     Print things to terminal time                     :         61,206 microseconds      *
*                                                                                          *
********************************************************************************************

~CityGraph()
Heap allocated memory of City Graph with graphSize 20 deleted.
